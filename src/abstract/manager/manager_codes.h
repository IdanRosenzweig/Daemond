#ifndef MANAGER_CODES_H
#define MANAGER_CODES_H

#include <cstdint>

enum manager_codes : uint8_t {
    LOAD_UNIT,
    UNLOAD_UNIT,
    START_UNIT,
    STOP_UNIT,
    TEST_UNIT_EXISTS,
    GET_UNIT_STATUS
};

#endif //MANAGER_CODES_H
