#include "stdio.h" 
#include "netdb.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
#include "pthread.h"
#include "sys/types.h"
#include "arpa/inet.h"
#include "netinet/in.h"
#include "sys/socket.h"

#include "server.h"
#include "thread_pool.h"

/**
 * @brief Setup server threadpool
*/
static ThreadPool server_pool(QUEUE_SIZE, NUM_THREAD);
static pthread_t server_thread_id;

/**
 * @brief Worker thread function
*/
void* request_thread(void* arg) {
    /* Process client request */
    char* client_message = (char*)arg;
    printf("Msg from client: %s\n", client_message);

    /* Implement Function Handlers */
    // TODO

    return NULL;
}

/**
 * @brief Server thread function
*/
void *server_thread(void *arg) {
    int socket_fd, client_fd, len; 
    struct sockaddr_in server_addr, client_addr; 
    
    printf("Starting Imail Server...\n");
   
    /* Socket create and verification */
    socket_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (socket_fd == -1) { 
        perror("Socket creation failed...\n"); 
        pthread_exit(0);
    } 

    /* Set the SO_REUSEADDR option */
    int enable = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        pthread_exit(0);
    }

    /* Assign IP, PORT */
    bzero(&server_addr, sizeof(server_addr)); 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_port = htons(SERVER_PORT); 
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
   
    /* Binding newly created socket to given IP and verification */
    if ((bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))) != 0) { 
        perror("socket bind failed...\n"); 
        pthread_exit(0);
    } 
   
    /* Now server is ready to listen and verification */
    if ((listen(socket_fd, MAX_CONNECTION)) != 0) { 
        perror("Listen failed...\n"); 
        pthread_exit(0);
    } 

    /* Server Loop */
    char client_message[MAX_MESSAGE_SIZE];
    while(1) {
        /* Accept the data packet from client and verification */
        len = sizeof(client_addr); 
        client_fd = accept(socket_fd, (struct sockaddr*)&client_addr, (socklen_t*)&len); 
        if (client_fd < 0) { 
            perror("server accept failed...\n"); 
            pthread_exit(0); 
        } 
        
        /* Receive client's message */
        if (recv(client_fd, client_message, sizeof(client_message), 0) < 0)
            printf("Couldn't receive message\n");
        else
            printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        /* Launch worker thread to handle request */
        server_pool.submit(request_thread, client_message);

        close(client_fd);
    }

    /* Close the socket */
    close(socket_fd);
    pthread_exit(0);
}

/**
 * @brief Initialize the server
 * 
 * @return 0 if successful, -1 if failed
*/
int server_init(void)
{
    /* Start server thread */
    pthread_create(&server_thread_id, NULL, server_thread, NULL);

    /* Allow server thread to start */
    sleep(1);
    
    return 0;
}

/**
 * @brief Send formatted message to the server
 * 
 * @param send_message The message to send to server
 * @param resp_message The response message from server
 * @param length The length of the message
 * 
 * @return 0 if successful, -1 if failed
*/
int server_send(char* send_message, char* resp_message)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    
    /* Create socket */
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0){
        printf("Unable to create socket\n");
        return -1;
    }
    
    /* Set port and IP the same as server-side */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    
    /* Send connection request to server */
    if (connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Unable to connect\n");
        return -1;
    }
    
    /* Send the message to server */
    if (send(socket_desc, send_message, strlen(send_message) + 1, 0) < 0){
        printf("Unable to send message\n");
        return -1;
    }
    
    /* Receive the server's response */
    if (recv(socket_desc, resp_message, MAX_MESSAGE_SIZE, 0) < 0){
        printf("Error while receiving server's msg\n");
        return -1;
    }
    
    /* Close the socket */
    close(socket_desc);
    
    return 0;
}

/**
 * @brief Shutdown the server
 * 
 * @return 0 if successful, -1 if failed
*/
int server_shutdown(void)
{
    /* Stop server thread */
    pthread_cancel(server_thread_id);

    /* Shutdown thread pool*/
    server_pool.shutdown();

    return 0;
}