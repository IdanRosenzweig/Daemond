#include "src/abstract/unit/data/unit_data.h"

// this source C++ file is the bare minimum for specifying a unit. no STL function are used here, just one instantiation for the unit struct.

struct unit_data unit {
    .id = "sshd0",
    .desc = {"sample unit for ssh daemon", ""},
    .type = DAEMON,
    .prio = 0,
    .exec = {
        {"mkdir -p /run/sshd"},
        {"/usr/sbin/sshd"},
        empty_command,
        empty_command,
        empty_command,
        {"kill $(pidof sshd)"},
        {"rm -rf /run/sshd"}
    },
    .attr = {
        false,
        false
    },
};