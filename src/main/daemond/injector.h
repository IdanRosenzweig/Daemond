#ifndef INJECTOR_H
#define INJECTOR_H

#include "../../abstract/manager/manager.h"
#include "../../abstract/comms/comms_server.h"

// singleton pattern. allowing jsut one instance of a unit manager
manager* get_unit_manager();

// singleton pattern. allowing one instance of a comms server
comms_server* get_comms_server();

#endif //INJECTOR_H
