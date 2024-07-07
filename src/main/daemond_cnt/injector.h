#ifndef INJECTOR_H
#define INJECTOR_H

#include "../../abstract/comms/comms_client.h"

// singleton pattern. allowing jsut one instance of a comms client
comms_client* get_comms_client();

#endif //INJECTOR_H
