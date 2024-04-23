#include <stdio.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

sem_t mut,db;
pthread_t reader[100],writer[100];
int rc = 0;

void read1(void param){
    sem_wait(&mut);
    rc++;
    if(rc==1){
        sem_wait(&db);
    }
    sem_post(&mut);
    printf("Reader %d is inside\n",rc);
    sem_wait(&mut);
    rc--;
    if(rc==0){
        sem_post(&db);
    }
    sem_post(&mut);
    printf("Reader %d is leaving\n",rc+1);
    return NULL;
}

void write1(void param){
    printf("Writer is trying to enter\n");
    sem_wait(&db);
    usleep(10);
    printf("Writer has entered\n");
    sem_post(&db);
    printf("Writer is leaving\n");
    return NULL;
}

int main()
{
    int num;
    printf("Enter the number of readers: ");
    scanf("%d",&num);
    sem_init(&mut,0,1);
    sem_init(&db,0,1);
    for(int i=0;i<num;i++){
        pthread_create(&writer[i],NULL,write1,NULL);
        pthread_create(&reader[i],NULL,read1,NULL);
    }
    for(int i=0;i<num;i++){
        pthread_join(reader[i],NULL);
        pthread_join(writer[i],NULL);
    }
}
