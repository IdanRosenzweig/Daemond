#ifndef LINUX_COMM_CENTER_H
#define LINUX_COMM_CENTER_H

#include "src/abstract/comms/comms_server.h"

#define SOCKET_SD_NONE (-1)
#define LINUX_COMM_CENTER_PATH "/run/daemond_comm_center"

class linux_comm_server : public comms_server {
private:
    int sd = SOCKET_SD_NONE;
    int alive = false;

public:
    void open_server() override;

    unique_ptr<comms_session> next_session() override;

    void close_server() override;

    bool is_server_open() override;
};



#endif //LINUX_COMM_CENTER_H
