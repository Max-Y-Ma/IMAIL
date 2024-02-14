#include <iostream>

#include "pthread.h"

/**
 * @brief Setup server threadpool
*/

/**
 * @brief Worker thread function
*/
void* worker_thread(void* arg) {

    pthread_exit(0);
}

/**
 * @brief Server thread function
*/
void *server_thread(void *arg) {
    std::cout << "Starting Imail Server..." << std::endl;

    void* arg_arg = arg;


    pthread_exit(0);
}

/**
 * @brief Initialize the server
 * 
 * @return 0 if successful, -1 if failed
*/
int server_init(void)
{
    /* Initialize Variables */
    
    /* Initialize Thread Pool */

    /* Start Server Thread */
    
    return 0;
}

/**
 * @brief Shutdown the server
 * 
 * @return 0 if successful, -1 if failed
*/
int server_shutdown(void)
{
    return 0;
}