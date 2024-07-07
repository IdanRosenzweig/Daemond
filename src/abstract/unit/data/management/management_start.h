#ifndef MANAGEMENT_START_H
#define MANAGEMENT_START_H

#include "command.h"

struct management_start {
    command pre_start;
    command start;
    command post_start;
};

#endif //MANAGEMENT_START_H
