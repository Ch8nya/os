//shows fork() exec() and wait() and getpid() and exit()

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        cerr << "Fork failed" << endl;
        return 1;
    }

    if (pid == 0) { // Child process
        cout << "Child process: " << getpid() << endl;
        char *args[] = {(char*)"/bin/ls", NULL}; // Command to execute
        execvp(args[0], args); // Execute the command
        exit(0); // Exit when done
    } else { // Parent process
        cout << "Parent process: " << getpid() << endl;
        wait(NULL); // Wait for child process to finish
        cout << "Child process finished" << endl;
    }

    return 0;
}

