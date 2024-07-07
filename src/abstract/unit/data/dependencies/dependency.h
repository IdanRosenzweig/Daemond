#ifndef DEPENDENCY_H
#define DEPENDENCY_H

#include "../unit_id.h"

struct dependency {
    unit_id id;
    bool strict = true;
    bool bind = true;
};

#endif //DEPENDENCY_H
