#ifndef UNIT_EXEC_H
#define UNIT_EXEC_H

#include "command.h"

struct unit_exec {
    command pre_start = empty_command;
    command start = empty_command;
    command post_start = empty_command;
    command reload = empty_command;
    command pre_stop = empty_command;
    command stop = empty_command;
    command post_stop = empty_command;
};

#endif //UNIT_EXEC_H
