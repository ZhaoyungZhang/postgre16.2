// Author: Zhaoyang Zhang
// Date: 2024-05-12
// Description: 通过模拟学生数据的写入和读取，展示了LRU缓存和结构体读写文件的使用场景和效果。
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define STUDENT_NAME_LENGTH 50
#define PAGE_SIZE 100  // 每页100个学生记录
#define MAX_PAGES_IN_MEMORY 10  // 最多保存10页在内存中
#define FILE_SIZE_LIMIT 64 * 1024 * 1024  // 64 MB
#define STUDENTS_PER_WRITE PAGE_SIZE  // 每次写入PAGE_SIZE个学生，即一页
#define min(a, b) ((a) < (b) ? (a) : (b))


/* ---------- Student Implement ---------- */
// 定义学生信息结构体
typedef struct {
    char name[STUDENT_NAME_LENGTH];
    int age;
    float gpa;
} Student;

/* ---------- Student Utils ---------- */
void random_string(char *str, int length) {
    static const char alphabet[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < length - 1; i++) {
        int index = rand() % (sizeof(alphabet) - 1);
        str[i] = alphabet[index];
    }
    str[length - 1] = '\0';
}

void random_student(Student *student) {
    random_string(student->name, STUDENT_NAME_LENGTH);
    student->age = rand() % 10 + 18;  // 生成18到27岁之间的随机年龄
    student->gpa = (float)(rand() % 300 + 200) / 100;  // 生成2.00到5.00之间的随机GPA
}

void display_students(Student *students, int count) {
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Age: %d, GPA: %.2f\n", students[i].name, students[i].age, students[i].gpa);
    }
}

/* ---------- Page Implement ---------- */
// 分页结构体，包含固定数量的学生记录
typedef struct {
    int page_number;   // 页码
    int num_students;  // 当前页的学生数目
    Student students[PAGE_SIZE]; // 存储具体学生数据的数组
} Page;

/* ---------- LRU Cache Implement ---------- */

typedef struct LRUNode {
    Page *page;            // 指向页面数据
    struct LRUNode *prev; // 指向前一个节点
    struct LRUNode *next; // 指向后一个节点
} LRUNode;

// LRU缓存结构，管理页面
typedef struct {
    LRUNode *head;        // 指向链表头部
    LRUNode *tail;        // 指向链表尾部
    int num_pages;        // 当前内存中的页数
} LRUCache;

/* ---------- LRU Function Implement ---------- */
void move_to_head(LRUCache *cache, LRUNode *node) {
    if (cache->head == node) return;
    // 从链表中移除
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (cache->tail == node) cache->tail = node->prev;
    // 插入到头部
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head != NULL) cache->head->prev = node;
    cache->head = node;

    if (cache->tail == NULL) cache->tail = node;
}

LRUNode *evict_lru(LRUCache *cache) {
    LRUNode *to_evict = cache->tail;
    if (to_evict->prev) to_evict->prev->next = NULL;
    cache->tail = to_evict->prev;
    cache->num_pages--;
    return to_evict;
}

void add_page_to_cache(LRUCache *cache, LRUNode *node) {
    if (cache->num_pages >= MAX_PAGES_IN_MEMORY) {
        LRUNode *evicted = evict_lru(cache);
        if (evicted) {
            printf("Evicting page %d from cache.\n", evicted->page->page_number);
            free(evicted->page);
            free(evicted);
        }
    }

    // Insert the new node to the head of the cache
    node->next = cache->head;
    node->prev = NULL;
    if (cache->head != NULL) cache->head->prev = node;
    cache->head = node;
    if (cache->tail == NULL) cache->tail = node;
    cache->num_pages++;
}

/* ---------- Read and Write Implement ---------- */
void write_page(FILE *file, Page *page) {
    fwrite(&page->page_number, sizeof(int), 1, file);
    fwrite(&page->num_students, sizeof(int), 1, file);
    fwrite(page->students, sizeof(Student), page->num_students, file);
   // printf("Writing page size: %ld bytes\n", sizeof(Student)*page->num_students + sizeof(int)*2);
}

// 持续写入随机学生数据直到文件大小达到限制
void write_students(const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to open file for writing");
        return;
    }

    srand(time(NULL));  // 设置随机种子
    long total_size = 0;
    long total_students = 0;
    long pages_written = 0;
    Student students[STUDENTS_PER_WRITE];
    
    while (total_size < FILE_SIZE_LIMIT) {
        Page page;
        page.page_number = pages_written;
        for (int i = 0; i < STUDENTS_PER_WRITE; i++) {
            random_student(&students[i]);
        }
        memcpy(page.students, students, sizeof(students));
        page.num_students = STUDENTS_PER_WRITE;

        write_page(file, &page);
        total_students += page.num_students;
        pages_written++;
        total_size += sizeof(page);
    }

    fclose(file);
    printf("Written %ld bytes, %ld students, %ld pages to %s\n", total_size, total_students, pages_written, filename);
}

// 从文件中读取指定页码的页面数据
int read_page(FILE *file, int page_number, Page *page) {
    int offset = page_number * sizeof(Page);
    fseek(file, offset, SEEK_SET);

    // 读取页面元数据
    if (fread(&page->page_number, sizeof(int), 1, file) != 1) return -1;
    if (fread(&page->num_students, sizeof(int), 1, file) != 1) return -1;
    
    // 根据记录的学生数读取学生数据
    if (fread(page->students, sizeof(Student), page->num_students, file) != page->num_students) return -1;

    return 0;  // 读取成功
}

Page *load_page(const char *filename, int page_number, LRUCache *cache) {
    // Search for the page in the cache first
    LRUNode *current = cache->head;
    while (current) {
        if (current->page->page_number == page_number) {
            move_to_head(cache, current);  // Page hit, move to front of cache
            printf("Page %d hit and moved to the front of the cache.\n", page_number);
            return current->page;
        }
        current = current->next;
    }

    // Page miss, need to load from disk
    printf("Loading page %d from disk.\n", page_number);
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    LRUNode *new_node = malloc(sizeof(LRUNode));
    if (!new_node) {
        perror("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    new_node->page = malloc(sizeof(Page));
    if (!new_node->page) {
        perror("Memory allocation failed for page");
        free(new_node);
        fclose(file);
        return NULL;
    }

    if (read_page(file, page_number, new_node->page) != 0) {
        free(new_node->page);
        free(new_node);
        fclose(file);
        return NULL;
    }
    fclose(file);

    // Add the new page node to the cache
    add_page_to_cache(cache, new_node);
    printf("Page %d added to cache.\n", page_number);
    return new_node->page;
}

/* ---------- Simple Test Implement ---------- */
// Test 1: 读取所有学生数据
Student *read_all_students(const char *filename, LRUCache *cache) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file for reading");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fclose(file);

    int total_pages = file_size / sizeof(Page);
    int total_count = total_pages * PAGE_SIZE;

    Student *all_students = malloc(total_count * sizeof(Student));
    if (!all_students) {
        perror("Memory allocation failed");
        return NULL;
    }

    printf("Starting to load %d pages...\n", total_pages);
    int students_loaded = 0;

    for (int i = 0; i < total_pages; i++) {
        Page *page = load_page(filename, i, cache);
        if (page) {
            int num_students_to_copy = min(PAGE_SIZE, total_count - students_loaded);
            memcpy(all_students + students_loaded, page->students, num_students_to_copy * sizeof(Student));
            students_loaded += num_students_to_copy;
        }
    }

    printf("Total %ld bytes read, corresponding to %d pages and %d student records loaded.\n", file_size, total_pages, students_loaded);
    return all_students;
}

// Test 2: 模拟页面加载和替换
void simulate_page_loading_and_replacement(const char *filename, int total_pages) {
    LRUCache cache = {0};

    printf("Simulating page loading and replacement...\n");
    // 0-9 load
    for (int i = 0; i < total_pages / 3; i++) {
        load_page(filename, i % total_pages, &cache);
    }
    // 9-0 hit
    for (int i = total_pages / 3 - 1; i >= 0; i--) {
        load_page(filename, i % total_pages, &cache);
    }
    // 10-19 load and evict 0-9
    for (int i = total_pages / 3; i < 2*total_pages / 3; i++) {
        load_page(filename, i % total_pages, &cache);
    }
}

// Test 3: 读取并打印学生数据
void read_and_display_page(const char *filename) {
    // load data first
    LRUCache cache = {0};
    for (int i = 100; i < 110; i++) {
        load_page(filename, i, &cache);
    }

    // display data
    for (int i = 100; i < 110; i++) {
        Page *page = load_page(filename, i, &cache);
        if (page) {
            printf("Page %d:, number of student is: %d\n", page->page_number, page->num_students);
            if(page->page_number == 100)
                display_students(page->students, 20);
            else
                display_students(page->students, 1);
        }
    }
}

/* ---------- Main Implement ---------- */
int main() {
    const char *filename = "students.data";
    printf("Starting student data writing...\n");
    write_students(filename);  
    printf("Student data writing completed.\n");

    /*---TEST 1---*/
    // LRUCache cache = {0};
    // read_all_students(filename, &cache);  // 读取所有学生数据

    /*---TEST 2---*/
    // simulate_page_loading_and_replacement(filename, 30);

    /*---TEST 3---*/
    read_and_display_page(filename);  // 读取并打印指定页码的学生数据

    return 0;
}

