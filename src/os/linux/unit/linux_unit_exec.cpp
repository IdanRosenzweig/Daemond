#include "linux_unit_exec.h"

#include <sys/wait.h>

void execute(const command& command, bool wait, struct command_exec_data* res) {
    pid_t child_pid = fork();
    if (child_pid == 0) {
        // this is the child process
        execl("/bin/sh", "sh", "-c", command.script.c_str(), nullptr);
        // shouldn't reach here anyway, but just in case
        exit(1);
    }
    if (wait) // wait for the child to finish execution
        waitpid(child_pid, nullptr, 0);

    if (res != nullptr)
        res->process_pid = child_pid;
}