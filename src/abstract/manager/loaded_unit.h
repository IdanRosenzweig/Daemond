#ifndef LOADED_UNIT_H
#define LOADED_UNIT_H

#include "../unit/data/unit_data.h"
#include "../unit/runtime/runtime_data.h"

struct loaded_unit {
    unit_data data;
    runtime_data runtime;
};

loaded_unit* factory_generate_unit(); // implementation is OS specific

#endif //LOADED_UNIT_H
