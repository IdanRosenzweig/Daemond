#ifndef LINUX_LOADED_UNIT_H
#define LINUX_LOADED_UNIT_H

#include "../../abstract/manager/loaded_unit.h"

struct linux_loaded_unit : public loaded_unit {
    pid_t pid;
    // permissions...
};

#endif //LINUX_LOADED_UNIT_H
