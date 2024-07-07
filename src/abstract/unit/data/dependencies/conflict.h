#ifndef CONFLICT_H
#define CONFLICT_H

#include "../unit_id.h"

struct conflict {
    unit_id id;
    bool strict = true;
    bool bind = true;
};
#endif //CONFLICT_H