#include "injector.h"

#include "../../../config/conf.h"

#include "src/os/linux/comms/unix_sock/linux_comm_client.h"

comms_client * get_comms_client() {
#ifdef CONF_OS_LINUX
    static linux_comm_client client;
    return (comms_client*) &client;
#endif
#ifdef CONF_OS_WINDOWS
    // ...
#endif
}
