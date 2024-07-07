#include "linux_comm_server.h"

#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>

#include "linux_comm_session.h"

void linux_comm_server::open_server() {
    if (is_server_open()) return;

    sd = socket(AF_UNIX, SOCK_STREAM, 0);
#define SOCK_OPEN_ERR (-1)
    if (sd == SOCK_OPEN_ERR) {
        perror("socket");
        return;
    }

    // prepare bind to file
    struct sockaddr_un address;
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, LINUX_COMM_CENTER_PATH, sizeof(address.sun_path) - 1);

    // bind to file
    unlink(LINUX_COMM_CENTER_PATH); // close previous file just in case
#define BIND_ERR (-1)
    if (bind(sd, (const sockaddr *) &address, sizeof(address)) == BIND_ERR) {
        perror("bind");
        close(sd);
        return;
    }

#define LISTEN_ERR (-1)
    if (listen(sd, 1) == LISTEN_ERR) {
        perror("listen");
        close(sd);
        return;
    }

    alive = true;
}

unique_ptr<comms_session> linux_comm_server::next_session() {
    if (!is_server_open()) return nullptr;

    int client_fd = accept(sd, nullptr, nullptr);
#define ACCEPT_ERR (-1)
    if (client_fd == ACCEPT_ERR) {
        perror("accept");
        return nullptr;
    }

    return make_unique<linux_comm_session>(client_fd);
}

void linux_comm_server::close_server() {
    if (!is_server_open()) return;

    if (sd != SOCKET_SD_NONE) {
        close(sd);
        sd = SOCKET_SD_NONE;
    }
    alive = false;
}

bool linux_comm_server::is_server_open() {
    return alive;
}
