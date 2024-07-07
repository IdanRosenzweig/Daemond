#ifndef LINUX_COMM_SESSION_H
#define LINUX_COMM_SESSION_H

#include "../../abstract/comm/comm_session.h"

#define SOCKET_SD_NONE (-1)
struct linux_comm_session : public comm_session {
private:
    int sd = SOCKET_SD_NONE;
    bool alive = false;

    void test_socket();

public:
    linux_comm_session() = delete;
    explicit linux_comm_session(int sd)
        : sd(sd),alive(true) {
    }

    int send_data(void *buff, int cnt) override;

    int recv_data(void *dest, int max_sz) override;

    void terminate_session() override;

    bool is_session_alive() override;
};



#endif //LINUX_COMM_SESSION_H
