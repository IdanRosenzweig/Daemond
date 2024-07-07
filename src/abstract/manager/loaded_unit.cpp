#include "loaded_unit.h"

void display_loaded_unit(const loaded_unit& unit) {
    puts("### unit data:");
    printf("id: %s\n", unit.data.id.name.c_str());
    printf("desc: %s, manual: %s\n", unit.data.desc.desc.c_str(), unit.data.desc.manual.c_str());
    printf("type: %d\n", unit.data.type);
    printf("priority: %d\n", unit.data.prio.val);
    // printf("code: %d\n", unit.data.prio.val);
    // printf("dependencies: %d\n", unit.data.prio.val);

    puts("### runtime data:");
    printf("status: %s\n", to_string(unit.runtime.status).c_str());


}