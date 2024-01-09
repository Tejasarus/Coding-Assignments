#include <windows.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#define THREAD_NUM 3
sem_t semaphore;

void* player1(void* args) {
    sem_wait(&semaphore);
    Sleep(500);
    printf("Player %d", *(int*)args);
    printf(" throws the frisbee to Player %d\n", *(int*)args + 1);
    sem_post(&semaphore);
    free(args);
}
void* player2(void* args) {
    sem_wait(&semaphore);
    Sleep(500);
    printf("Player %d", *(int*)args);
    printf(" throws the frisbee to Player %d\n", *(int*)args + 1);
    sem_post(&semaphore);
    free(args);
}
void* player3(void* args) {
    sem_wait(&semaphore);
    Sleep(500);
    printf("Player %d", *(int*)args);
    printf(" throws the frisbee to Player %d\n", *(int*)args -2);
    sem_post(&semaphore);
    free(args);
}

int main(int argc, char *argv[]) 
{
    pthread_t thread[THREAD_NUM];
    sem_init(&semaphore,0,4);
    int i = 1;
    while(1)
    {
        int* a = malloc(sizeof(int));
        *a = i;
        pthread_create(&thread[i], NULL, &player1, a);
        pthread_join(thread[i], NULL);
        ++i;
        *a = i;
        pthread_create(&thread[i], NULL, &player2, a);
        pthread_join(thread[i], NULL);
        ++i;
        *a = i;
        pthread_create(&thread[i], NULL, &player3, a);
        pthread_join(thread[i], NULL);
        i = 1;
    }

    sem_destroy(&semaphore);
    return 0;
}