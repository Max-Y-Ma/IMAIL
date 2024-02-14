#ifndef _SERVER_H_
#define _SERVER_H_

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