#include "linux_comm_client.h"

#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>

#include "linux_comm_server.h"
#include "linux_comm_session.h"

unique_ptr<comms_session> linux_comm_client::conn_to_server() {
    int sd = socket(AF_UNIX, SOCK_STREAM, 0);
#define SOCK_OPEN_ERR (-1)
    if (sd == SOCK_OPEN_ERR) {
        perror("socket");
        return nullptr;
    }

    struct sockaddr_un address;
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, LINUX_COMM_CENTER_PATH, sizeof(address.sun_path) - 1);
#define CONNECT_ERR (-1)
    if (connect(sd, (const sockaddr *) &address, sizeof(address)) == CONNECT_ERR) {
        perror("connect");
        close(sd);
        return nullptr;
    }

    return make_unique<linux_comm_session>(sd);
}
