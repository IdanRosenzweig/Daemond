#ifndef LINUX_COMM_CENTER_H
#define LINUX_COMM_CENTER_H

#include "../../abstract/comm/comm_center.h"

#define SOCKET_SD_NONE (-1)
#define LINUX_COMM_CENTER_PATH "/run/daemond_comm_center"

class linux_comm_center : public comm_center {
private:
    int sd = SOCKET_SD_NONE;
    int alive = false;

public:
    void open_center() override;

    unique_ptr<comm_session> next_session() override;

    void close_center() override;

    bool is_center_open() override;
};



#endif //LINUX_COMM_CENTER_H