#include "injector.h"

#include "../../../config/conf.h"

#include "../../os/linux/comms/unix_sock/linux_comm_server.h"
#include "../../os/linux/manager/linux_manager.h"

manager * get_unit_manager() {
#ifdef CONF_OS_LINUX
    static linux_manager mnger;
    return (manager*) &mnger;
#endif
#ifdef CONF_OS_WINDOWS
    // ...
#endif
}

comms_server * get_comms_server() {
#ifdef CONF_OS_LINUX
    static linux_comm_server server;
    return (comms_server *) &server;
#endif
#ifdef CONF_OS_WINDOWS
    // ...
#endif
}

