#ifndef _IMAIL_H_
#define _IMAIL_H_

class Imail {
private:

public:
    /**
     * @brief Constructor
    */
    Imail();

    /**
     * @brief Shutdown Imail library 
     * 
     * @return 0 if successful, -1 if failed
    */
    int shutdown(void);

    /**
     * @brief Send a query command request to the server
     * 
     * @details This function will block until the query is sent and
     *          the response is received.
     * 
     * @return 0 if successful, -1 if failed
    */
    int query(void);

    /**
     * @brief Send a message or packet to another client
     * 
     * @details This function will block until the message or packet is sent.
     * 
     * @return 0 if successful, -1 if failed
    */
    int send(void);

    /**
     * @brief Receive a message or packet from another client.
     * 
     * @details This function will block until a message or packet is received.
     * 
     * @return 0 if successful, -1 if failed
    */
    int recv(void);

    /**
     * @brief Poll the server for new messages or packets
     * 
     * @return 0 if successful, -1 if failed
    */
    int poll(void);
};

#endif /* _IMAIL_H_ */