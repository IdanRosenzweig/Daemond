#include "linux_comm_session.h"

#include <unistd.h>
#include <sys/socket.h>

void linux_comm_session::test_socket() {
    char test;
    if (!alive || (sd == SOCKET_SD_NONE || recv(sd, &test, sizeof(test), MSG_PEEK) == 0)) {
        if (sd != SOCKET_SD_NONE) {
            close(sd);
            sd = SOCKET_SD_NONE;
        }
        alive = false;
    }
}

int linux_comm_session::send_data(void *buff, int cnt) {
    test_socket();
    if (alive) return send(sd, buff, cnt, 0);
    else return 0;
}

int linux_comm_session::recv_data(void *dest, int max_sz) {
    test_socket();
    if (alive) return recv(sd, dest, max_sz, 0);
    else return 0;
}

void linux_comm_session::terminate_session() {
    if (sd != SOCKET_SD_NONE) {
        close(sd);
        sd = SOCKET_SD_NONE;
    }
    alive = false;
}

bool linux_comm_session::is_session_alive() {
    test_socket();
    return alive;
}
