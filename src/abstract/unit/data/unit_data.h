#ifndef UNIT_DATA_H
#define UNIT_DATA_H

#include "unit_id.h"
#include "unit_desc.h"
#include "unit_type.h"
#include "unit_priority.h"
#include "management/unit_management.h"
#include "unit_attr.h"
#include "dependencies/unit_dependencies.h"

struct unit_data {
    unit_id id;
    unit_desc desc;
    unit_type type;
    unit_priority prio;
    unit_management mng;
    unit_attr attr;
    unit_dependencies deps;
};

#endif //UNIT_DATA_H
