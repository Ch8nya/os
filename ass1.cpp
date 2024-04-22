#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void copyfile() {
    pid_t child_pid = fork();

    if (child_pid < 0) {
        printf("Fork Failed\n");
    } else if (child_pid == 0) {
        char *args[] = {"cp", "source.txt", "dest.txt", NULL};
        execvp("cp", args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("file copied successfully\n");
    }
}

void searchpattern() {
    char pattern[256];
    printf("enter the pattern to search :: ");
    scanf("%255s", pattern);

    pid_t child_pid = fork();
    if (child_pid < 0) {
        printf("Fork Failded\n");
    } else if (child_pid == 0) {
        char *args[] = {"grep", pattern, "source.txt", NULL};
        execvp("grep", args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        wait(NULL);
        printf("pattern search completed \n");
    }
}

int main() {
    int ch;
    printf("\n Choose option to execute : \n");
    printf("1. Copy file(cp command)\n");
    printf("2. search pattern(grep command)\n");
    printf("3. Display process ID (getpid)\n");
    printf("4. exit\n");
    scanf("%d", &ch);

    switch (ch) {
        case 1:
            copyfile();
            break;
        case 2:
            searchpattern();
            break;
        case 3:
            printf("Process ID is :: %d", getpid());
            break;
        case 4:
            printf("==exiting program==\n");
            exit(EXIT_SUCCESS);
        default:
            printf("invalid input");
    }

    return 0;
}
