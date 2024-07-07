#ifndef UNIT_SERIALIZATION_H
#define UNIT_SERIALIZATION_H

#include "common.h"
#include "../unit/data/unit_data.h"

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

#endif //UNIT_SERIALIZATION_H
