#include "src/abstract/unit/data/unit_data.h"

struct unit_data unit {
    .id = "sshd0",
    .desc = {"sample unit for ssh daemon", ""},
    .type = DAEMON,
    .prio = 0,
    .mng = {
        .start_unit = {
            {"mkdir -p /run/sshd"},
            {"/usr/sbin/sshd"},
            empty_command
        },
        .reload_unit = {empty_command},
        .stop_unit = {
            empty_command,
            {"kill $(pidof sshd)"},
            {"rm -rf /run/sshd"}
        },
    },
    .attr = {
        false,
        false
    },
    .deps = {
        .needed = {
            {"other_unit"},
            {"other_unit2"}
        },
        .conf = {
            {"conf_unit1"},
            {"conf_unit2"}
        }
    }
};