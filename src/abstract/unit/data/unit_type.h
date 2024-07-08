#ifndef UNIT_TYPE_H
#define UNIT_TYPE_H

enum unit_type {
    DAEMON, // long living daemon
    TASK, // one-time/temporary task
    ROUTINE // interval routine
};

#endif //UNIT_TYPE_H
