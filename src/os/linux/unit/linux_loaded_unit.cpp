#include "linux_loaded_unit.h"

loaded_unit* factory_generate_unit() noexcept {
    return new linux_loaded_unit;
}