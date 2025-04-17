#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10
#define INCREMENTS_PER_THREAD 100000

int counter = 0;  // Shared variable

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
void *increment(void *arg)
{
    for (int i = 0; i < INCREMENTS_PER_THREAD; i++)
    {
        pthread_mutex_lock(&lock);
        counter++;  // Not protected — race condition!
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, increment, NULL);
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("Final counter value: %d\n", counter);
    return 0;
}
