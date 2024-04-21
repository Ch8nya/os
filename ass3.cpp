#include<stdio.h>
#include<unistd.h>

int main() {
   int pipe1[2], pipe2[2];
   int status1, status2;
   int pid;
   char pipe1msg[20];
   char pipe2msg[20];
   char readmessage[20];

   status1 = pipe(pipe1);
   if (status1 == -1) {
       printf("Pipe 1 not created \n");
       return 1;
   }

   status2 = pipe(pipe2);
   if (status2 == -1) {
       printf("Pipe 2 not created \n");
       return 1;
   }

   pid = fork();
   if (pid != 0) {
       //0 reading
       //1 writing
       close(pipe1[0]);
       close(pipe2[1]);
       printf("Enter Parent msg to Child: ");
       scanf("%s", pipe1msg);
       printf("In Parent: Writing to pipe 1 – Message is %s\n", pipe1msg);
       write(pipe1[1], pipe1msg, sizeof(pipe1msg));
       read(pipe2[0], readmessage, sizeof(readmessage));
       printf("In Parent: Reading from pipe 2 – Message is %s\n", readmessage);
   } else {
       close(pipe1[1]);
       close(pipe2[0]);
       read(pipe1[0], readmessage, sizeof(readmessage));
       printf("In Child: Reading from pipe 1 – Message is %s\n", readmessage);
       printf("Enter Child msg to Parent: ");
       scanf("%s", pipe2msg);
       printf("In Child: Writing to pipe 2 – Message is %s\n", pipe2msg);
       write(pipe2[1], pipe2msg, sizeof(pipe2msg));
   }

   return 0;
}