#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


void    *routine(void *argim)
{
    int id;

    id = *(int *)argim;
    
    printf("thread id %d is working!\n", id);
    return (NULL);
}
void    *routine2(void *argim)
{
    int id;

    sleep(3);
    id = *(int *)argim;
    sleep(3);
    printf("thread id %d is working!\n", id);
    return (NULL);
}

int main ()
{
    pthread_t   t1;
    pthread_t   t2;
    int id1, id2;
    id1 = 1;
    id2 = 2;
    pthread_create(&t1, NULL, &routine, &id1);
    pthread_create(&t2, NULL, &routine2, &id2);
    pthread_join(t1, NULL);
    printf("main done execution");
}