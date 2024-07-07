#include "unit_serialization.h"
#include "common.h"

#include <filesystem>
#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

void serialize_unit_data_to_file(const unit_data &data, const string &dest) {
    ofstream out(dest);
    boost::archive::text_oarchive ar(out);
    ar << data;
    out.close();
}

void serialize_unit_data_to_file(const string &source, const string &dest) {
#define PROJECT_DIR "/home/user/CLionProjects/daemond"
    string command = PROJECT_DIR "/scripts/serialize.sh unit ";
    command += source;
    system(command.c_str());

    string mv_comm = "mv serialized_unit.txt ";
    mv_comm += dest;
    system(mv_comm.c_str());
}

ustring serialize_unit_data(const unit_data &data) {
#define TEMP_FILE ".tempfile"

    serialize_unit_data_to_file(data, TEMP_FILE);

    ifstream in(TEMP_FILE);
    ustring res((istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>());
    in.close();

    filesystem::remove(TEMP_FILE);

    return res;
}

ustring serialize_unit_data(const string &source) {
#define TEMP_FILE ".tempfile"

    serialize_unit_data_to_file(source, TEMP_FILE);

    ifstream in(TEMP_FILE);
    ustring res((istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>());
    in.close();

    filesystem::remove(TEMP_FILE);

    return res;
}

ustring serialize_unit_id(const unit_id &id) {
#define TEMP_FILE ".tempfile"

    serialize_unit_id_to_file(id, TEMP_FILE);

    ifstream in(TEMP_FILE);
    ustring res((istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>());
    in.close();

    filesystem::remove(TEMP_FILE);

    return res;
}

ustring serialize_unit_id(const string &source) {
#define TEMP_FILE ".tempfile"

    serialize_unit_id_to_file(source, TEMP_FILE);

    ifstream in(TEMP_FILE);
    ustring res((istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>());
    in.close();

    filesystem::remove(TEMP_FILE);

    return res;
}

void serialize_unit_id_to_file(const unit_id &id, const string &dest) {
    ofstream out(dest);
    boost::archive::text_oarchive ar(out);
    ar << id;
    out.close();
}

void serialize_unit_id_to_file(const string &source, const string &dest) {
#define PROJECT_DIR "/home/user/CLionProjects/daemond"
    string command = PROJECT_DIR "/scripts/serialize.sh id ";
    command += source;
    system(command.c_str());

    string mv_comm = "mv serialized_unit_id.txt ";
    mv_comm += dest;
    system(mv_comm.c_str());
}
