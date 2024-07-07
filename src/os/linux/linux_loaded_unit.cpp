#include "linux_loaded_unit.h"

loaded_unit* factory_generate_unit() {
    return new linux_loaded_unit;
}