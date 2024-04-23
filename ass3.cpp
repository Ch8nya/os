#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

int main() {
    int pipefd[2]; // File descriptors for the pipe
    pid_t pid;
    char message[] = "Hello, child process!";

    // Create pipe
    if (pipe(pipefd) == -1) {
        cerr << "Pipe failed\n";
        return 1;
    }

    // Fork child process
    pid = fork();

    if (pid < 0) {
        cerr << "Fork failed\n";
        return 1;
    } 
    else if (pid == 0) { // Child process
        close(pipefd[1]); // Close the write end of the pipe

        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer)); // Read message from parent process
        cout << "Child process received message: " << buffer << endl;
        close(pipefd[0]); // Close the read end of the pipe
    } 
    else { // Parent process
        close(pipefd[0]); // Close the read end of the pipe

        cout << "Parent process sending message: " << message << endl;
        write(pipefd[1], message, strlen(message) + 1); // Write message to the pipe
        close(pipefd[1]); // Close the write end of the pipe

        wait(NULL); // Wait for child process to finish
    }

    return 0;
}
