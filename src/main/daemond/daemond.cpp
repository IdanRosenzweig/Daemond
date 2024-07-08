#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <boost/archive/archive_exception.hpp>

#include "injector.h"

#include "src/abstract/serialization/cache/cache.h"
#include "src/abstract/serialization/unit_serialization.h"
#include "src/abstract/serialization/unit_deserialization.h"

#include "src/abstract/manager/manager_codes.h"

int main() {
    cout << "reseting cache" << endl;
    reset_cache();

    cout << "starting units manager" << endl;

    cout << "starting communication center" << endl;
    get_comms_server()->open_server();

    // general buffer for receving messages
#define BUFF_SZ 60000
    uint8_t buff[BUFF_SZ];

    while (true) {
        auto sess = std::move(get_comms_server()->next_session());

        memset(buff, 0, BUFF_SZ);
        int no_bytes_read = sess->recv_data((char *) buff, BUFF_SZ);
        if (no_bytes_read == 0) {
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
                unit_data static_data;
                try {
                    static_data = deserialize_unit_data(ustring{curr_ptr, curr_sz});
                } catch (...) {
                    cerr << "caught exception while deserializing unit" << endl;
                    break;
                }

                cout << "loading unit with id: " << static_data.id.name << endl;
                get_unit_manager()->load_unit(static_data);
                break;
            }
            case UNLOAD_UNIT: {
                unit_id id;
                try {
                    id = deserialize_unit_id(ustring{curr_ptr, curr_sz});
                } catch (...) {
                    cerr << "caught exception while deserializing unit id" << endl;
                    break;
                }

                cout << "unloading unit with id: " << id.name << endl;
                get_unit_manager()->unload_unit(id);
                break;
            }
            case START_UNIT: {
                unit_id id;
                try {
                    id = deserialize_unit_id(ustring{curr_ptr, curr_sz});
                } catch (...) {
                    cerr << "caught exception while deserializing unit id" << endl;
                    break;
                }

                cout << "starting unit with id: " << id.name << endl;
                get_unit_manager()->start_unit(id);
                break;
            }
            case STOP_UNIT: {
                unit_id id;
                try {
                    id = deserialize_unit_id(ustring{curr_ptr, curr_sz});
                } catch (...) {
                    cerr << "caught exception while deserializing unit id" << endl;
                    break;
                }

                cout << "stopping unit with id: " << id.name << endl;
                get_unit_manager()->stop_unit(id);
                break;
            }
            case TEST_UNIT_EXISTS: {
                unit_id id;
                try {
                    id = deserialize_unit_id(ustring{curr_ptr, curr_sz});
                } catch (...) {
                    cerr << "caught exception while deserializing unit id" << endl;
                    break;
                }

                bool exists = get_unit_manager()->unit_exists(id);
                if (sess->send_data(&exists, sizeof(exists)) != sizeof(exists)) cerr << "couldn't send whole data" << endl;

                break;
            }
            case GET_UNIT_STATUS: {
                unit_id id;
                try {
                    id = deserialize_unit_id(ustring{curr_ptr, curr_sz});
                } catch (...) {
                    cerr << "caught exception while deserializing unit id" << endl;
                    break;
                }

                if (!get_unit_manager()->unit_exists(id)) {
                    cerr << "not such unit" << endl;
                    break;
                }

                const loaded_unit& unit = get_unit_manager()->search_unit(id);
                ustring serialized = serialize_loaded_unit(unit);
                if (sess->send_data(serialized.c_str(), serialized.size()) != serialized.size()) cerr << "couldn't send whole data" << endl;

                break;
            }
        }

        sess->terminate_session();
    }
}
