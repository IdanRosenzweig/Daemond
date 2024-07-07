#include "unit_deserialization.h"
#include "common.h"

#include <fstream>
#include <filesystem>

#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

struct unit_data deserialize_unit_data(const ustring &serialization) {
#define TEMP_FILE "tempfile"
    ofstream out(TEMP_FILE);
    out.write((char *) serialization.c_str(), serialization.size());
    out.close();

    struct unit_data res = deserialize_unit_data(TEMP_FILE);

    filesystem::remove(TEMP_FILE);

    return res;
}

struct unit_data deserialize_unit_data(const string &source) {
    ifstream file(source);
    boost::archive::text_iarchive archive(file);

    unit_data res;
    archive >> res;

    return res;
}

struct unit_id deserialize_unit_id(const ustring &serialization) {
#define TEMP_FILE "tempfile"
    ofstream out(TEMP_FILE);
    out.write((char *) serialization.c_str(), serialization.size());
    out.close();

    struct unit_id res = deserialize_unit_id(TEMP_FILE);

    filesystem::remove(TEMP_FILE);

    return res;
}

struct unit_id deserialize_unit_id(const string &source) {
    ifstream file(source);
    boost::archive::text_iarchive archive(file);

    unit_id res;
    archive >> res;

    return res;
}

struct loaded_unit deserialize_loaded_unit(const ustring &serialization) {
#define TEMP_FILE "tempfile"
    ofstream out(TEMP_FILE);
    out.write((char *) serialization.c_str(), serialization.size());
    out.close();

    struct loaded_unit res = deserialize_loaded_unit(TEMP_FILE);

    filesystem::remove(TEMP_FILE);

    return res;
}

struct loaded_unit deserialize_loaded_unit(const string &source) {
    ifstream file(source);
    boost::archive::text_iarchive archive(file);

    struct loaded_unit res;
    archive >> res;

    return res;
}