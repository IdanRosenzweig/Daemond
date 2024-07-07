#ifndef EXEC_STOP_H
#define EXEC_STOP_H

#include "command.h"

struct exec_stop {
    command pre_stop;
    command stop;
    command post_stop;
};

#endif //EXEC_STOP_H
