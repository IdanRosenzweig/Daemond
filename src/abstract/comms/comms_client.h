#ifndef COMMS_CLIENT_H
#define COMMS_CLIENT_H

#include "comms_session.h"
#include <memory>
using namespace std;

struct comms_client {
    virtual void open_client() = 0;
    virtual unique_ptr<comms_session> conn_to_server() = 0;
    virtual void close_client() = 0;

    virtual ~comms_client() {
    }
};
#endif //COMMS_CLIENT_H
