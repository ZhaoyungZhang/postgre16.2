#include <stdio.h>
#include <string.h>

typedef struct State{
    unsigned StateType:1,
             StateFlags:32,
             StateLength:10;
} State;

int main(){
    State s;
    memset(&s, 0, sizeof(State));
    s.StateType = 1;
    s.StateFlags = 2;
    // s.StateLength = 1023;
    s.StateLength = 1024;
    printf("StateType: %d\n", s.StateType);
    printf("StateFlags: %d\n", s.StateFlags);
    printf("StateLength: %d\n", s.StateLength);
    // print size
    printf("Size of State: %lu\n", sizeof(State));
    return 0;
}