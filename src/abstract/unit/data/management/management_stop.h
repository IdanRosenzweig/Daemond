#ifndef MANAGEMENT_STOP_H
#define MANAGEMENT_STOP_H

#include "command.h"

struct management_stop {
    command pre_stop;
    command stop;
    command post_stop;
};

#endif //MANAGEMENT_STOP_H
