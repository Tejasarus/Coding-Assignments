#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>

int nums[10] = {1,2,3,4,5,6,7,8,9,10};
int sum = 0;

void* array_sum(void* arg) 
{
    Sleep(1);
    int index = *(int*)arg;
    sum += nums[index];
    free(arg);
}

int main(int argc, char* argv[]) 
{
    pthread_t thread[10];
    for (int i = 0; i < 10; i++) 
    {
        int* a = malloc(sizeof(int));
        *a = i;
        pthread_create(&thread[i], NULL, &array_sum, a);
    }
    for (int i = 0; i < 10; i++) 
    {
        pthread_join(thread[i], NULL);
    }

    printf("%d ",sum);
    
    return 0;
}