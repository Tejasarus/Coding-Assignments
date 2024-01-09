#include <windows.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#define THREAD_NUM 4
sem_t semaphore;

void* person1(void* args) {
    sem_wait(&semaphore);
    Sleep(500);
    printf("Person %d", *(int*)args);
    printf(" arrives.\n");
    sem_post(&semaphore);
    free(args);
}
int main(int argc, char *argv[]) 
{
    pthread_t thread[THREAD_NUM];
    sem_init(&semaphore, 0, 4);
    int i;
    for (i = 1; i < THREAD_NUM; i++) 
    {
        int* a = malloc(sizeof(int));
        *a = i;
        pthread_create(&thread[i], NULL, &person1, a);
    }
    for (i = 1; i < THREAD_NUM; i++) 
    {
        pthread_join(thread[i], NULL);
    }
    sem_destroy(&semaphore);
    //eat function would go here
    return 0;
}