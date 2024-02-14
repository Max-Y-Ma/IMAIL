#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_

#include <deque>
#include <vector>

#include "pthread.h"
#include "semaphore.h"

/* Thread Work Struct */
typedef void *(*job_function)(void *param);
typedef struct {
    job_function func_;
    void *data_;
} task_t;

class ThreadPool {
private:
    /* Work Queue */
    int queue_size_;
    std::deque<task_t> work_queue_;
    sem_t sem_queue_;
    pthread_mutex_t mtx_queue_;

    /* Thread Vector */
    int num_threads_;
    std::vector<pthread_t> thread_pool_;

public:
    /**
     * @brief Initializes the thread pool.
    */
    ThreadPool(int queue_size, int num_threads);

    /**
     * @brief Insert a task into the queue
     * 
     * @return returns 0 if successful or 1 otherwise,
    */
    int enqueue(task_t task);

    /**
     * @brief Remove a task from the queue
    */
    task_t dequeue(void);

    /**
     * @brief Submit a pointer to a function with a parameter
     *        to be exectued by a thread in the pool.
    */
    int submit(job_function func, void *data);

    /**
     * @brief Shuts down the thread pool once all tasks complete.
    */
    void shutdown(void);
};

#endif /* _THREAD_POOL_H_ */