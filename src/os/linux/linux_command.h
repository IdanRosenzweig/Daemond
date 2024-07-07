#ifndef LINUX_COMMAND_H
#define LINUX_COMMAND_H

#include "../../abstract/unit/data/management/command.h"
#include <sys/types.h>

struct command_exec_data {
    pid_t process_pid;
};

#endif //LINUX_COMMAND_H
