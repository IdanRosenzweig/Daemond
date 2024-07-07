#ifndef UNIT_DEPENDENCIES_H
#define UNIT_DEPENDENCIES_H

#include "dependency.h"
#include "conflict.h"

#include <vector>
using namespace std;

struct unit_dependencies {
    // represents units that *are required to run* before this unit runs
    vector<dependency> needed;
    // represents units that *cannot be run* when this unit runs
    vector<conflict> conf;
};
#endif //UNIT_DEPENDENCIES_H
