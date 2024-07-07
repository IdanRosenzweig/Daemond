#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include "../../abstract/serialization/unit_serialization.h"

#include "../../abstract/manager/manager_codes.h"
#include "../../os/linux/linux_comm_center.h"

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

    // connect to daemond
    int sd = socket(AF_UNIX, SOCK_STREAM, 0);
#define SOCK_OPEN_ERR (-1)
    if (sd == SOCK_OPEN_ERR) perror("socket");

    struct sockaddr_un address;
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, LINUX_COMM_CENTER_PATH, sizeof(address.sun_path) - 1);
#define CONNECT_ERR (-1)
    if (connect(sd, (const sockaddr *) &address, sizeof(address)) == CONNECT_ERR) perror("connect");

    // send msg
#define SEND_ERR (-1)
    if (send(sd, buff, curr_ptr - buff, 0) == SEND_ERR) perror("send");

    cout << "message send" << endl;

    close(sd);
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

    // connect to daemond
    int sd = socket(AF_UNIX, SOCK_STREAM, 0);
#define SOCK_OPEN_ERR (-1)
    if (sd == SOCK_OPEN_ERR) perror("socket");

    struct sockaddr_un address;
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, LINUX_COMM_CENTER_PATH, sizeof(address.sun_path) - 1);
#define CONNECT_ERR (-1)
    if (connect(sd, (const sockaddr *) &address, sizeof(address)) == CONNECT_ERR) perror("connect");

    // send msg
#define SEND_ERR (-1)
    if (send(sd, buff, curr_ptr - buff, 0) == SEND_ERR) perror("send");

    cout << "message send" << endl;

    close(sd);
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

    // connect to daemond
    int sd = socket(AF_UNIX, SOCK_STREAM, 0);
#define SOCK_OPEN_ERR (-1)
    if (sd == SOCK_OPEN_ERR) perror("socket");

    struct sockaddr_un address;
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, LINUX_COMM_CENTER_PATH, sizeof(address.sun_path) - 1);
#define CONNECT_ERR (-1)
    if (connect(sd, (const sockaddr *) &address, sizeof(address)) == CONNECT_ERR) perror("connect");

    // send msg
#define SEND_ERR (-1)
    if (send(sd, buff, curr_ptr - buff, 0) == SEND_ERR) perror("send");

    cout << "message send" << endl;

    close(sd);
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

    // connect to daemond
    int sd = socket(AF_UNIX, SOCK_STREAM, 0);
#define SOCK_OPEN_ERR (-1)
    if (sd == SOCK_OPEN_ERR) perror("socket");

    struct sockaddr_un address;
    memset(&address, 0, sizeof(address));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path, LINUX_COMM_CENTER_PATH, sizeof(address.sun_path) - 1);
#define CONNECT_ERR (-1)
    if (connect(sd, (const sockaddr *) &address, sizeof(address)) == CONNECT_ERR) perror("connect");

    // send msg
#define SEND_ERR (-1)
    if (send(sd, buff, curr_ptr - buff, 0) == SEND_ERR) perror("send");

    cout << "message send" << endl;

    close(sd);
}

int main(int argc, char **argv) {
    // Define command line options
    po::options_description opts("daemond-ctl options");
    opts.add_options()
            ("help,h", "show options")
            ("command", po::value<std::string>(), "command to execute, one of the following: load, unload, start, stop")
            ("path", po::value<std::string>(), "path to the unit data");

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
    } else if (command == "unload") {
        unload(path);
    } else if (command == "start") {
        start(path);
    } else if (command == "stop") {
        stop(path);
    } else {
        cerr << "Invalid command. Use start, stop, restart, or status" << endl;
    }
}
