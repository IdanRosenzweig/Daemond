#ifndef COMMAND_H
#define COMMAND_H

#include <string>
using namespace std;

struct command {
    string script;

    command() : script("") {
    }

    command(const string &script)
        : script(script) {
    }

    command(const command &other) : script(other.script) {
    }
};

// OS specific information regarding execution of a command (process data, shell info...)
struct command_exec_data;

// execute a command. if res is not nullptr, store the related information into it.
// if wait is true, then execute the command in place and wait for it to finish.
// otherwise, execute the command in the background and continue execution.
void execute(const command &command, bool wait, struct command_exec_data* res = nullptr); // implementation is OS specific

#define empty_command command("")

#endif //COMMAND_H
