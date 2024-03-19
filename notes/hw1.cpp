#include <iostream>
#include <csignal>
#include <unistd.h> // For sleep()

using namespace std;

volatile int lives = 9; // 猫的生命值

// 信号处理函数
void signalHandler(int signum) {
    cout << "Caught signal " << signum << endl;
    lives--;
    if (lives > 0) {
        cout << "You've lost one of your nine lives. " << lives << " lives left." << endl;
        if (lives == 3) {
            cout << "Warning: Only 3 lives left!" << endl;
        }
    } else {
        cout << "All lives are lost. Exiting the program..." << endl;
        exit(signum);
    }
}

int main() {
    // 注册信号SIGINT和信号处理函数
    signal(SIGINT, signalHandler);

    while(lives > 0) {
        cout << "Playing... Press CTRL+C to interrupt." << endl;
        sleep(1);
    }

    return 0;
}
