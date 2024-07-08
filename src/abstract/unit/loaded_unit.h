#ifndef LOADED_UNIT_H
#define LOADED_UNIT_H

#include "data/unit_data.h"
#include "runtime/runtime_data.h"

struct loaded_unit {
    unit_data data;
    runtime_data runtime;
};

void display_loaded_unit(const loaded_unit& unit);

loaded_unit* factory_generate_unit() noexcept; // implementation is OS specific

#endif //LOADED_UNIT_H
