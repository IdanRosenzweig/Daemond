#ifndef COMMS_SERVER_H
#define COMMS_SERVER_H

#include "comms_session.h"

#include <memory>
using namespace std;

class comms_server {
public:
    virtual void open_server() = 0;
    virtual unique_ptr<comms_session> next_session() = 0;
    virtual void close_server() = 0;
    virtual bool is_server_open() = 0;

    virtual ~comms_server() {}
};



#endif //COMMS_SERVER_H
