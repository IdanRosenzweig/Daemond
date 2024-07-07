#ifndef RUNTIME_STATUS_H
#define RUNTIME_STATUS_H

#include <string>
using namespace std;

enum runtime_status {
    NOT_RUNNING, RUNNING
};

string to_string(const runtime_status& status);

#endif //RUNTIME_STATUS_H
