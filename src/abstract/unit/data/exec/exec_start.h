#ifndef EXEC_START_H
#define EXEC_START_H

#include "command.h"

struct exec_start {
    command pre_start;
    command start;
    command post_start;
};

#endif //EXEC_START_H
