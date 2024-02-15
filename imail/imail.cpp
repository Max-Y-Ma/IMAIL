#include "stdio.h"
#include "string.h"

#include "imail.h"
#include "server.h"

#define IMAIL_ACK_STRING "IMAIL ACK"
#define IMAIL_VERIFY(response_buf) strcmp(response_buf, IMAIL_ACK_STRING)

/**
 * @brief Constructor
*/
Imail::Imail()
{
    /* Initialize Server */
    server_init();
}

/**
 * @brief Shutdown Imail library 
 * 
 * @return 0 if successful, -1 if failed
*/
int Imail::shutdown(void)
{
    /* Shutdown Server */
    if (server_shutdown() != 0) {
        printf("Error: Failed to shutdown server\n");
        return -1;
    }

    return 0;
}

/**
 * @brief Send a query command request to the server
 * 
 * @details This function will block until the query is sent and
 *          the response is received.
 * 
 * @return 0 if successful, -1 if failed
*/
int Imail::query(int command)
{
    /* Format server message: "IMAIL COMMAND <command>" */
    char server_buf[MAX_MESSAGE_SIZE], response_buf[MAX_MESSAGE_SIZE];
    sprintf(server_buf, "IMAIL COMMAND %d", command);

    /* Send message to server */
    server_send(server_buf, response_buf);

    /* Verify Response */
    if (IMAIL_VERIFY(response_buf) != 0) {
        return -1;
    }

    return 0;
}

/**
 * @brief Send a message or packet to another client
 * 
 * @details This function will block until the message or packet is sent.
 * 
 * @return 0 if successful, -1 if failed
*/
int Imail::send(int uid, char* message)     
{
    /* Format server message: "IMAIL SEND <to> <message>" */
    char server_buf[MAX_MESSAGE_SIZE], response_buf[MAX_MESSAGE_SIZE];
    sprintf(server_buf, "IMAIL SEND %d %s", uid, message);

    /* Send message to server */
    server_send(server_buf, response_buf);

    /* Verify Response: "IMAIL ACK..." */
    if (IMAIL_VERIFY(response_buf) != 0) {
        return -1;
    }

    return 0;
}

/**
 * @brief Receive a message or packet from another client.
 * 
 * @details This function will block until a message or packet is received.
 * 
 * @return 0 if successful, -1 if failed
*/
int Imail::recv(char* message_buf)
{
    /* Format server message: "IMAIL RECV" */
    char server_buf[MAX_MESSAGE_SIZE];
    sprintf(server_buf, "IMAIL RECV");

    /* Send message to server */
    server_send(server_buf, message_buf);

    /* Verify Response: "IMAIL ACK..." */
    if (IMAIL_VERIFY(message_buf) != 0) {
        return -1;
    }

    return 0;
}
