#include "loaded_unit.h"

void display_loaded_unit(const loaded_unit& unit) {
    puts("### unit data ###");
    printf("%14s: %s\n", "id", unit.data.id.name.c_str());
    printf("%14s: %s, %s: %s\n", "desc", unit.data.desc.desc.c_str(), "manual", unit.data.desc.manual.c_str());
    printf("%14s: %d\n", "type", unit.data.type);
    printf("%14s: %d\n", "priority", unit.data.prio.val);
    printf("%14s:\n", "exec");
    printf("%18s: %s\n", "pre_start", unit.data.exec.pre_start.script.c_str());
    printf("%18s: %s\n", "start", unit.data.exec.start.script.c_str());
    printf("%18s: %s\n", "post_start", unit.data.exec.post_start.script.c_str());
    printf("%18s: %s\n", "pre_stop", unit.data.exec.pre_stop.script.c_str());
    printf("%18s: %s\n", "stop", unit.data.exec.stop.script.c_str());
    printf("%18s: %s\n", "post_stop", unit.data.exec.post_stop.script.c_str());
    // dependencies

    puts("### runtime data ###");
    printf("%14s: %s\n", "status", to_string(unit.runtime.status).c_str());


}