#ifndef UNIT_SERIALIZATION_H
#define UNIT_SERIALIZATION_H

#include "common.h"
#include "../unit/data/unit_data.h"
#include "src/abstract/manager/loaded_unit.h"

#define PROJECT_DIR "/home/user/CLionProjects/daemond"

/** unit data serialization */
// take a unit data (from either a struct or a text file) and serialize it into a destination file
void serialize_unit_data_to_file(const unit_data &data, const string &dest);

void serialize_unit_data_to_file(const string &source, const string &dest);

// take a unit data (from either a struct or a text file) and serialize it into ustring
ustring serialize_unit_data(const unit_data &data);

ustring serialize_unit_data(const string &source);

/** unit id serialization */
// take a unit id (from either a struct or a text file) and serialize its id into a destination file
void serialize_unit_id_to_file(const unit_id &id, const string &dest);

void serialize_unit_id_to_file(const string &source, const string &dest);

// take a unit id (from either a struct or a text file) and serialize its id into a destination file
ustring serialize_unit_id(const unit_id &id);

ustring serialize_unit_id(const string &source);

/** loaded unit serialization */
// take a loaded unit (from either a struct or a text file) and serialize it into a destination file
void serialize_loaded_unit_to_file(const loaded_unit &unit, const string &dest);

// take a loaded unit (from either a struct or a text file) and serialize it into ustring
ustring serialize_loaded_unit(const loaded_unit &unit);

#endif //UNIT_SERIALIZATION_H
