#include "../../abstract/serialization/cache/cache.h"

#include <fcntl.h>
#include <filesystem>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>

#define CACHE_DIR "/run/daemond/cache"

void reset_cache() {
    system("rm -rf " CACHE_DIR);
}

void create_cache_dir() {
    system("mkdir -p " CACHE_DIR);
}

string convert_record_to_cache_file(const string &record_name) {
    return CACHE_DIR "/cached_" + record_name;
}

bool is_in_cache(const string &record) {
    struct stat sb;
#define STAT_ERR (-1)
    if (stat(convert_record_to_cache_file(record).c_str(), &sb) != STAT_ERR && S_ISREG(sb.st_mode)) // file exists
        return true;

    return false;
}

string get_cache_record(const string &record) {
    return convert_record_to_cache_file(record);
//
//     struct stat sb;
// #define STAT_ERR (-1)
//     if (stat(cache_file.c_str(), &sb) == STAT_ERR) {
//         cerr << "can't stat file" << endl;
//         throw;
//     }
//
//     int file_sz = sb.st_size;
//     string data(file_sz, 0);
//
//     int fd = open(cache_file.c_str(), O_RDONLY);
// #define OPEN_ERR (-1)
//     if (fd == OPEN_ERR) {
//         cerr << "can't open file" << endl;
//         throw;
//     }
//
//     if (read(fd, data.data(), file_sz) != sb.st_size) {
//         cerr << "can't read whole file" << endl;
//         close(fd);
//         throw;
//     }
//
//     close(fd);
//
//     return data;
}

void store_in_cache(const string &record_name, const string &source) {
    string mv_comm = "mv " + source + " ";
    mv_comm += convert_record_to_cache_file(record_name);
    system(mv_comm.c_str());
}
