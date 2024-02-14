#include "thread_pool.h"

/* Kill flag */
static bool shutdown_flag = false;

/**
 * @brief Execute a task
*/
void execute(job_function func, void* data)
{
    /* Check valid arguments */
    if (func == NULL)
        return;

    /* Execute the task */
    (*func)(data);
}

/* Worker thread in the thread pool */
static void* worker_thread(void* param)
{
    do {
        /* Blocking Dequeue */
        ThreadPool* obj = (ThreadPool*)param;
        task_t task = obj->dequeue();

        /* Execute the task */
        execute(task.func_, task.data_);
    } while (!shutdown_flag);

    pthread_exit(0);
}

/**
 * @brief Initializes the thread pool.
*/
ThreadPool::ThreadPool(int queue_size, int num_threads)
{
    /* Initialize private variables */
    this->queue_size_ = queue_size;
    this->num_threads_ = num_threads;
    sem_init(&this->sem_queue_, 0, 0);
    pthread_mutex_init(&this->mtx_queue_, NULL);

    /* Create all worker threads */
    thread_pool_.resize(this->num_threads_);
    for (int i = 0; i < this->num_threads_; i++) {
        pthread_create(&this->thread_pool_[i], NULL, worker_thread, this);
    }
}

/**
 * @brief Insert a task into the queue
 * 
 * @return returns 0 if successful or 1 otherwise,
*/
int ThreadPool::enqueue(task_t task) 
{
    /* Acquire Lock */
    pthread_mutex_lock(&this->mtx_queue_);

    /* Check Queue Full */
    if (this->work_queue_.size() == (unsigned long)this->queue_size_) {
        pthread_mutex_unlock(&this->mtx_queue_);
        return -1;
    }

    /* Enqueue */
    this->work_queue_.push_back(task);
    sem_post(&this->sem_queue_);

    /* Release Lock */
    pthread_mutex_unlock(&this->mtx_queue_);

    return 0;
}

/**
 * @brief Remove a task from the queue
*/
task_t ThreadPool::dequeue(void) 
{
    /* Block on Queue Empty */
    sem_wait(&this->sem_queue_);

    /* Shutdown Condition */
    if (shutdown_flag) {
        task_t task;
        task.func_ = NULL;
        return task;
    }

    /* Acquire Lock */
    pthread_mutex_lock(&this->mtx_queue_);

    /* Dequeue */
    task_t ret = this->work_queue_.front();
    this->work_queue_.pop_front();

    /* Release Lock */
    pthread_mutex_unlock(&this->mtx_queue_);

    return ret;
}

/**
 * @brief Submit a pointer to a function with a parameter
 *        to be exectued by a thread in the pool.
*/
int ThreadPool::submit(job_function func, void* data)
{
    /* Enqueue Task*/
    task_t task;
    task.func_ = func;
    task.data_ = data;

    return enqueue(task);
}

/**
 * @brief Shuts down the thread pool once all tasks complete.
*/
void ThreadPool::shutdown(void)
{
    /* Terminate all worker threads */
    shutdown_flag = true;

    for (int i = 0; i < this->num_threads_; i++) {
        pthread_cancel(this->thread_pool_[i]);
    }
    
    for (int i = 0; i < this->num_threads_; i++) {
        pthread_join(this->thread_pool_[i], NULL);
    }
}