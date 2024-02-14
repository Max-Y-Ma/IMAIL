#include "imail.h"

/**
 * @brief Constructor
*/
Imail::Imail()
{
    
}

/**
 * @brief Shutdown Imail library 
 * 
 * @return 0 if successful, -1 if failed
*/
int Imail::shutdown(void)
{
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
int Imail::query(void)
{
    return 0;
}

/**
 * @brief Send a message or packet to another client
 * 
 * @details This function will block until the message or packet is sent.
 * 
 * @return 0 if successful, -1 if failed
*/
int Imail::send(void)
{
    return 0;
}

/**
 * @brief Receive a message or packet from another client.
 * 
 * @details This function will block until a message or packet is received.
 * 
 * @return 0 if successful, -1 if failed
*/
int Imail::recv(void)
{
    return 0;
}

/**
 * @brief Poll the server for new messages or packets
 * 
 * @return 0 if successful, -1 if failed
*/
int Imail::poll(void)
{
    return 0;
}