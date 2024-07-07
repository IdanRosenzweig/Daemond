#include <cstring>
#include <fstream>
#include <iostream>

#include "injector.h"

#include "src/abstract/serialization/common.h"
#include "src/abstract/serialization/unit_serialization.h"
#include "src/abstract/serialization/unit_deserialization.h"

#include "src/abstract/manager/manager_codes.h"

#include <boost/program_options.hpp>

namespace po = boost::program_options;

void load(const string &path) {
    // prepare message
#define BUFF_SZ 60000
    uint8_t buff[BUFF_SZ];
    memset(buff, 0, BUFF_SZ);

    uint8_t *curr_ptr = buff;

    *(manager_codes *) curr_ptr = LOAD_UNIT;
    curr_ptr += sizeof(manager_codes);

    ustring serialized = serialize_unit_data(path);

    memcpy(curr_ptr, serialized.data(), serialized.size());
    curr_ptr += serialized.size();

    // connect to server
    get_comms_client()->open_client();
    auto sess = std::move(get_comms_client()->conn_to_server());

    // send message
    int cnt = curr_ptr - buff;
    if (sess->send_data(buff, cnt) != cnt) {
        cerr << "couldn't send whole message" << endl;
        sess->terminate_session();
        return;
    }

    sess->terminate_session();
}

void unload(const string &path) {
    // prepare message
#define BUFF_SZ 60000
    uint8_t buff[BUFF_SZ];
    memset(buff, 0, BUFF_SZ);

    uint8_t *curr_ptr = buff;

    *(manager_codes *) curr_ptr = UNLOAD_UNIT;
    curr_ptr += sizeof(manager_codes);

    ustring serialized_id = serialize_unit_id(path);

    memcpy(curr_ptr, serialized_id.data(), serialized_id.size());
    curr_ptr += serialized_id.size();

    // connect to server
    get_comms_client()->open_client();
    auto sess = std::move(get_comms_client()->conn_to_server());

    // send message
    int cnt = curr_ptr - buff;
    if (sess->send_data(buff, cnt) != cnt) {
        cerr << "couldn't send whole message" << endl;
        sess->terminate_session();
        return;
    }

    sess->terminate_session();
}

void start(const string &path) {
    // prepare message
#define BUFF_SZ 60000
    uint8_t buff[BUFF_SZ];
    memset(buff, 0, BUFF_SZ);

    uint8_t *curr_ptr = buff;

    *(manager_codes *) curr_ptr = START_UNIT;
    curr_ptr += sizeof(manager_codes);

    ustring serialized_id = serialize_unit_id(path);

    memcpy(curr_ptr, serialized_id.data(), serialized_id.size());
    curr_ptr += serialized_id.size();

    // connect to server
    get_comms_client()->open_client();
    auto sess = std::move(get_comms_client()->conn_to_server());

    // send message
    int cnt = curr_ptr - buff;
    if (sess->send_data(buff, cnt) != cnt) {
        cerr << "couldn't send whole message" << endl;
        sess->terminate_session();
        return;
    }

    sess->terminate_session();
}

void stop(const string &path) {
    // prepare message
#define BUFF_SZ 60000
    uint8_t buff[BUFF_SZ];
    memset(buff, 0, BUFF_SZ);

    uint8_t *curr_ptr = buff;

    *(manager_codes *) curr_ptr = STOP_UNIT;
    curr_ptr += sizeof(manager_codes);

    ustring serialized_id = serialize_unit_id(path);

    memcpy(curr_ptr, serialized_id.data(), serialized_id.size());
    curr_ptr += serialized_id.size();

    // connect to server
    get_comms_client()->open_client();
    auto sess = std::move(get_comms_client()->conn_to_server());

    // send message
    int cnt = curr_ptr - buff;
    if (sess->send_data(buff, cnt) != cnt) {
        cerr << "couldn't send whole message" << endl;
        sess->terminate_session();
        return;
    }

    sess->terminate_session();
}

bool exists(const string &path) {
    // prepare message
#define BUFF_SZ 60000
    uint8_t buff[BUFF_SZ];
    memset(buff, 0, BUFF_SZ);

    uint8_t *curr_ptr = buff;

    *(manager_codes *) curr_ptr = TEST_UNIT_EXISTS;
    curr_ptr += sizeof(manager_codes);

    ustring serialized_id = serialize_unit_id(path);

    memcpy(curr_ptr, serialized_id.data(), serialized_id.size());
    curr_ptr += serialized_id.size();

    // connect to server
    get_comms_client()->open_client();
    auto sess = std::move(get_comms_client()->conn_to_server());

    // send message
    int cnt = curr_ptr - buff;
    if (sess->send_data(buff, cnt) != cnt) {
        cerr << "couldn't send whole message" << endl;
        sess->terminate_session();
        throw;
    }

    // receive back
    memset(buff, 0, BUFF_SZ);
    if (sess->recv_data(buff, BUFF_SZ) == 0) {
        cerr << "couldn't receive data" << endl;
        sess->terminate_session();
        throw;
    }

    bool exists = buff[0] == 1;
    sess->terminate_session();
    return exists;
}

loaded_unit status(const string &path) {
    // prepare message
#define BUFF_SZ 60000
    uint8_t buff[BUFF_SZ];
    memset(buff, 0, BUFF_SZ);

    uint8_t *curr_ptr = buff;

    *(manager_codes *) curr_ptr = GET_UNIT_STATUS;
    curr_ptr += sizeof(manager_codes);

    ustring serialized_id = serialize_unit_id(path);

    memcpy(curr_ptr, serialized_id.data(), serialized_id.size());
    curr_ptr += serialized_id.size();

    // connect to server
    get_comms_client()->open_client();
    auto sess = std::move(get_comms_client()->conn_to_server());

    // send message
    int cnt = curr_ptr - buff;
    if (sess->send_data(buff, cnt) != cnt) {
        cerr << "couldn't send whole message" << endl;
        sess->terminate_session();
        throw;
    }

    // receive bac,
    memset(buff, 0, BUFF_SZ);
    cnt =sess->recv_data(buff, BUFF_SZ);
    if (cnt == 0) {
        cerr << "couldn't receive data" << endl;
        sess->terminate_session();
        throw;
    }

    loaded_unit unit = deserialize_loaded_unit(ustring(buff, cnt));
    sess->terminate_session();
    return unit;
}

int main(int argc, char **argv) {
    // Define command line options
    po::options_description opts("daemond-ctl options");
    opts.add_options()
            ("help,h", "show options")
            ("command,c", po::value<std::string>(), "command to execute, one of the following: load, unload, start, stop, exists, status")
            ("path,p", po::value<std::string>(), "path to the unit data");

    // Define positional options
    po::positional_options_description pos_desc;
    pos_desc.add("command", 1).add("service", 2);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(opts).positional(pos_desc).run(), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << opts;
        return 1;
    }

    if (!vm.count("command")) {
        cout << opts;
        return 1;
    }
    string command = vm["command"].as<std::string>();

    if (!vm.count("path")) {
        cout << opts;
        return 1;
    }
    string path = vm["path"].as<std::string>();

    // Handle commands
    if (command == "load") {
        load(path);
        cout << "loaded unit" << endl;
    } else if (command == "unload") {
        unload(path);
        cout << "unloaded unit" << endl;
    } else if (command == "start") {
        start(path);
        cout << "started unit" << endl;
    } else if (command == "stop") {
        stop(path);
        cout << "stopped unit" << endl;
    } else if (command == "exists") {
        if (exists(path)) {
            cout << "unit exists";
        } else {
            cout << "unit doesn't exists";
        }
    } else if (command == "status") {
        loaded_unit unit = status(path);
        display_loaded_unit(unit);
    } else {
        cout << opts;
        return 1;
    }

    return 0;
}
