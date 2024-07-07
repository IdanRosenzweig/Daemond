#ifndef UNIT_MANAGEMENT_H
#define UNIT_MANAGEMENT_H

#include "management_start.h"
#include "management_reload.h"
#include "management_stop.h"

struct unit_management {
    management_start start_unit;
    management_reload reload_unit;
    management_stop stop_unit;
//    management_test test_unit;
};

#endif //UNIT_MANAGEMENT_H
