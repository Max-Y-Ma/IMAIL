/**
 * Example client program that uses thread pool.
 */

#include <stdio.h>
#include <unistd.h>
#include "thread_pool.h"

struct data {
    int a;
    int b;
};

void* add(void *param)
{
    struct data *temp;
    temp = (struct data*)param;

    printf("I add two values %d and %d result = %d\n",temp->a, temp->b, temp->a + temp->b);

    return NULL;
}

int main(void)
{
    /* Create some work to do */
    struct data work;
    work.a = 5;
    work.b = 10;

    /* Initialize the thread pool */
    ThreadPool thread_pool(10, 3);

    /* Submit the work to the queue */
    for (int i = 0; i < 10; i++) {
        thread_pool.submit((job_function)&add, &work);
    }

    sleep(3);

    /* Terminate */
    thread_pool.shutdown();

    return 0;
}