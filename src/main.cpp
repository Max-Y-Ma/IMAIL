#include <iostream>

#include "imail.h"

int main() {
    /* Create Object */
    Imail imail;

    /* Test Query Commands */
    imail.query(1);

    /* Test Send */
    char send_buf[1024] = "Hello, World!";
    imail.send(1, send_buf);

    /* Test Recv */
    char message_buf[1024];
    imail.recv(message_buf);

    /* Shutdown */
    imail.shutdown();

    return 0;
}