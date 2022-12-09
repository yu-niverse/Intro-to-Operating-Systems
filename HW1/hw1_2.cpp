#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

int main() {

    cout << "Main Process ID : "<< getpid() << "\n";
    if (!fork()) { // child process
        cout << "Fork 1. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
        if (!fork()) {
            cout << "Fork 2. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
            if (!fork()) {
                cout << "Fork 3. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
            } else wait(NULL);
        } else wait(NULL);
    } else { // parent process
        wait(NULL);
        if (!fork()) {
            cout << "Fork 4. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
        } else {
            wait(NULL);
            if (!fork()) {
                cout << "Fork 6. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
            } else wait(NULL);
        }
        if (!fork()) {
            cout << "Fork 5. I'm the child " << getpid() << ", my parent is " << getppid() << ".\n";
        } else wait(NULL);
    }

    return 0;
}


