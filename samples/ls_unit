#include "src/abstract/unit/data/unit_data.h"

// this source C++ file is the bare minimum for specifying a unit. no STL function are used here, just one instantiation for the unit struct.

struct unit_data unit {
    .id = "ls",
    .desc = {"sample unit for ls task", ""},
    .type = TASK,
    .prio = 0,
    .exec = {
        .start = {"/usr/bin/ls"}
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