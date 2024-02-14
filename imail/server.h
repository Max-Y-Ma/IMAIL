#ifndef _SERVER_H_
#define _SERVER_H_

#define QUEUE_SIZE 10
#define NUM_THREAD 3

#define SERVER_PORT 18000
#define MAX_CONNECTION 10

#define MAX_MESSAGE_SIZE 1024

/**
 * @brief Initialize the server
 * 
 * @return 0 if successful, -1 if failed
*/
int server_init(void);

/**
 * @brief Shutdown the server
 * 
 * @return 0 if successful, -1 if failed
*/
int server_shutdown(void);

#endif /* _SERVER_H_ */