#ifndef COMM_CENTER_H
#define COMM_CENTER_H

#include "comm_session.h"

#include <memory>
using namespace std;

class comm_center {
public:
    virtual void open_center() = 0;
    virtual unique_ptr<comm_session> next_session() = 0;
    virtual void close_center() = 0;
    virtual bool is_center_open() = 0;

    virtual ~comm_center() {}
};



#endif //COMM_CENTER_H
