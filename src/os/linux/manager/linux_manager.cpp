#include "linux_manager.h"
#include "src/os/linux/unit/linux_unit_exec.h"

#include <filesystem>
#include <iostream>
#include <signal.h>

#include "src/os/linux/unit/linux_loaded_unit.h"

void linux_manager::_start_unit_at_index(size_t in) {
    execute(units[in]->data.exec.pre_start, true);
    command_exec_data res{};
    execute(units[in]->data.exec.start, false, &res);
    execute(units[in]->data.exec.pre_start, true);

    ((linux_loaded_unit *) units[in].get())->pid = res.process_pid;
    units[in]->runtime.status = RUNNING;
}

void linux_manager::_stop_unit_at_index(size_t in) {
    execute(units[in]->data.exec.pre_stop, false);
    execute(units[in]->data.exec.stop, false);
    execute(units[in]->data.exec.post_stop, false);

    // kill the child process, just in case...
    pid_t proc_pid = ((linux_loaded_unit *) units[in].get())->pid;
#define KILL_ERR (-1)
    if (kill(proc_pid, SIGTERM) == KILL_ERR) {
        cerr << "can't kill child process (was already killed?)" << endl;
    }

    units[in]->runtime.status = NOT_RUNNING;
}
