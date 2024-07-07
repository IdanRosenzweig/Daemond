#include "unit_serialization.h"
#include "common.h"
#include "cache/cache.h"
#include "config/conf.h"

#include <filesystem>
#include <fstream>
#include <iostream>

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
    string cache = source;
    replace(cache.begin(), cache.end(), '/', '.');
    cache = "unit_" + cache;

    create_cache_dir();
    if (!is_in_cache(cache)) {
        cout << "unit data not in cache, compiling unit..." << endl;
        string command = PROJECT_DIR "/scripts/serialize.sh unit ";
        command += source;
        system(command.c_str());

        store_in_cache(cache, "serialized_unit.txt");
    }

    string ser_data_file = get_cache_record(cache);

    // get from cache
    string cp_comm = "cp " + ser_data_file + " ./" + dest;
    system(cp_comm.c_str());
}

ustring serialize_unit_data(const unit_data &data) {
#define TEMP_FILE "tempfile"

    serialize_unit_data_to_file(data, TEMP_FILE);

    ifstream in(TEMP_FILE);
    ustring res((istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>());
    in.close();

    filesystem::remove(TEMP_FILE);

    return res;
}

ustring serialize_unit_data(const string &source) {
#define TEMP_FILE "tempfile"

    serialize_unit_data_to_file(source, TEMP_FILE);

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
    string cache = source;
    replace(cache.begin(), cache.end(), '/', '.');
    cache = "id_" + cache;

    create_cache_dir();
    if (!is_in_cache(cache)) {
        cout << "unit id is not in cache, compiling unit..." << endl;
        string command = PROJECT_DIR "/scripts/serialize.sh id ";
        command += source;
        system(command.c_str());

        store_in_cache(cache, "serialized_unit_id.txt");
    }

    string ser_data_file = get_cache_record(cache);

    // get from cache
    string cp_comm = "cp " + ser_data_file + " ./" + dest;
    system(cp_comm.c_str());
}

ustring serialize_unit_id(const unit_id &id) {
#define TEMP_FILE "tempfile"

    serialize_unit_id_to_file(id, TEMP_FILE);

    ifstream in(TEMP_FILE);
    ustring res((istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>());
    in.close();

    filesystem::remove(TEMP_FILE);

    return res;
}

ustring serialize_unit_id(const string &source) {
#define TEMP_FILE "tempfile"

    serialize_unit_id_to_file(source, TEMP_FILE);

    ifstream in(TEMP_FILE);
    ustring res((istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>());
    in.close();

    filesystem::remove(TEMP_FILE);

    return res;
}

void serialize_loaded_unit_to_file(const loaded_unit &unit, const string &dest) {
    ofstream out(dest);
    boost::archive::text_oarchive ar(out);
    ar << unit;
    out.close();
}

ustring serialize_loaded_unit(const loaded_unit &unit) {
#define TEMP_FILE "tempfile"

    serialize_loaded_unit_to_file(unit, TEMP_FILE);

    ifstream in(TEMP_FILE);
    ustring res((istreambuf_iterator<char>(in)),
                istreambuf_iterator<char>());
    in.close();

    filesystem::remove(TEMP_FILE);

    return res;
}
