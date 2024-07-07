#include "runtime_status.h"

string to_string(const runtime_status& status) {
    switch (status) {
        case NOT_RUNNING: return "not running";
        case RUNNING: return "running";
    }
    return "bogus";
}