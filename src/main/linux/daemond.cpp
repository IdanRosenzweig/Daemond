#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>

#include <mqueue.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "../../abstract/unit/data/unit_data.h"
#include "../../abstract/serialization/unit_deserialization.h"

#include "../../abstract/manager/manager_codes.h"
#include "../../os/linux/linux_manager.h"
#include "src/os/linux/linux_comm_center.h"

int main() {
    cout << "starting units manager" << endl;
    linux_manager unit_manager;

    //     // writing identification file
    //     {
    //         cout << "writing identification file" << endl;
    // #define PROC_PID_FILE "/etc/daemond/proc_pid"
    //         // clear previous value (if exists)
    //         unlink(PROC_PID_FILE);
    //         // write current value
    //         FILE *file = fopen(PROC_PID_FILE, "w");
    //         string pid = to_string(getpid());
    //         fwrite(pid.c_str(), 1, pid.size(), file);
    //     }

    //     // opening message queu
    //     mqd_t mq;
    //     {
    //         cout << "opening message queue" << endl;
    // #define MSG_QUEUE_PATH "/home/user/msg_q"
    //         mq = mq_open(MSG_QUEUE_PATH, 0644);
    // #define MQ_OPEN_ERR (-1)
    //         if (mq == MQ_OPEN_ERR) perror("mq_open");
    //     }

    cout << "starting communication center" << endl;
    linux_comm_center comm_server;
    comm_server.open_center();

    // general buffer for receving messages
#define BUFF_SZ 60000
    uint8_t buff[BUFF_SZ];

    while (true) {
        auto sess = std::move(comm_server.next_session());

        memset(buff, 0, BUFF_SZ);
        int no_bytes_read = sess->recv_data((char *) buff, BUFF_SZ);
#define RECV_ERR (-1)
        if (no_bytes_read == RECV_ERR) {
            cerr << "couldn't read from client" << endl;
            sess->terminate_session();
            continue;
        }

        // parse
        uint8_t *curr_ptr = buff;
        size_t curr_sz = no_bytes_read;

        manager_codes code = *(manager_codes *) curr_ptr;
        curr_ptr += sizeof(manager_codes);
        curr_sz -= sizeof(manager_codes);

        switch (code) {
            case LOAD_UNIT: {
                unit_data static_data = deserialize_unit_data(ustring{curr_ptr, curr_sz});

                cout << "loading unit with id: " << static_data.id.name << endl;
                unit_manager.load_unit(static_data);

                break;
            }
            case UNLOAD_UNIT: {
                unit_id id = deserialize_unit_id(ustring{curr_ptr, curr_sz});

                cout << "unloading unit with id: " << id.name << endl;
                unit_manager.unload_unit(id);
                break;
            }
            case START_UNIT: {
                unit_id id = deserialize_unit_id(ustring{curr_ptr, curr_sz});

                cout << "starting unit with id: " << id.name << endl;
                unit_manager.start_unit(id);
                break;
            }
            case STOP_UNIT: {
                unit_id id = deserialize_unit_id(ustring{curr_ptr, curr_sz});

                cout << "stopping unit with id: " << id.name << endl;
                unit_manager.stop_unit(id);
                break;
            }
            case TEST_UNIT_EXISTS: {
                unit_id id = deserialize_unit_id(ustring{curr_ptr, curr_sz});

                bool exists = unit_manager.unit_exists(id);
#define SEND_ERR (-1)
                if (sess->send_data(&exists, sizeof(exists)) == SEND_ERR) cerr << "couldn't send data" << endl;

                break;
            }
        }

        sess->terminate_session();
    }
}


