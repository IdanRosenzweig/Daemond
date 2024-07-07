#ifndef LINUX_COMM_CLIENT_H
#define LINUX_COMM_CLIENT_H

#include "src/abstract/comms/comms_client.h"

struct linux_comm_client : public comms_client {
    void open_client() override {}

    unique_ptr<comms_session> conn_to_server() override;

    void close_client() override {}
};



#endif //LINUX_COMM_CLIENT_H
