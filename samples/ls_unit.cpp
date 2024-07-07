#include "src/abstract/unit/data/unit_data.h"

struct unit_data unit {
    .id = {"ls unit"},
    .desc = {"sample unit test for /bin/ls", ""},
    .type = DAEMON,
    .priority = 0,
    .commands = {
        empty_command,
        {"/bin/ls", {}},
        empty_command,
        empty_command,
        {"/bin/ls", {}},
        empty_command,
    },
    .management = {
        true,
        true
    }
};