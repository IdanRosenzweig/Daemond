#ifndef UNIT_EXEC_H
#define UNIT_EXEC_H

#include "command.h"
#include "exec_start.h"
#include "exec_reload.h"
#include "exec_stop.h"

struct unit_exec {
    exec_start start;
    exec_reload reload;
    exec_stop stop;
};

#endif //UNIT_EXEC_H
