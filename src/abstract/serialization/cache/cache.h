#ifndef CACHE_H
#define CACHE_H

#include <string>
using namespace std;

// implementation is OS specific
void reset_cache(); // reset all curretnly stored in the cache
void create_cache_dir(); // create cache directory if doesn't exists
bool is_in_cache(const string& record); // seach if the required record is in the cache
string get_cache_record(const string& record); // get path to a file containing the cached data for the record
void store_in_cache(const string& record_name, const string& source); // store the data in the source file under the record "record_name"

#endif //CACHE_H
