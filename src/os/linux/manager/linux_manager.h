#ifndef LINUX_MANAGER_H
#define LINUX_MANAGER_H

#include "src/abstract/manager/manager.h"

class linux_manager : public manager {
protected:
    void _start_unit_at_index(size_t in) override;

    void _stop_unit_at_index(size_t in) override;
};

#endif //LINUX_MANAGER_H
