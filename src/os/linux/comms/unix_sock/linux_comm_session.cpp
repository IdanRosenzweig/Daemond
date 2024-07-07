#include "linux_comm_session.h"

#include <unistd.h>
#include <sys/socket.h>

#include <iostream>
using namespace std;

int linux_comm_session::send_data(const void *buff, int cnt) {
    if (!is_session_alive()) return 0;

    int res = send(sd, buff, cnt, 0);
#define SEND_ERR (-1)
#define SEND_SOCK_CLOSE (0)
    if (res == SEND_ERR) {
        // terminate_session();
        return 0;
    } else if (res == SEND_SOCK_CLOSE) {
        terminate_session();
        return 0;
    } else return res;
}

int linux_comm_session::recv_data(void *dest, int max_sz) {
    if (!is_session_alive()) return 0;

    int res = recv(sd, dest, max_sz, 0);;
#define RECV_ERR (-1)
#define RECV_SOCK_CLOSE (0)
    if (res == RECV_ERR) {
        // terminate_session();
        return 0;
    } else if (res == RECV_SOCK_CLOSE) {
        terminate_session();
        return 0;
    } else return res;
}

void linux_comm_session::terminate_session() {
    if (sd != SOCKET_SD_NONE) {
        close(sd);
        sd = SOCKET_SD_NONE;
    }
    alive = false;
}

bool linux_comm_session::is_session_alive() {
    return alive;
}
