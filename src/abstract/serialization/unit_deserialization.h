#ifndef UNIT_DESERIALIZATION_H
#define UNIT_DESERIALIZATION_H

#include "common.h"
#include "../unit/data/unit_data.h"
#include "src/abstract/manager/loaded_unit.h"

/** unit data deserialization */
// deserialize a unit data (from either a ustring or a source text file)
struct unit_data deserialize_unit_data(const ustring &serialization);

struct unit_data deserialize_unit_data(const string &source);

/** unit id deserialization */
// deserialize a unit id (from either a ustring or a source text file)
struct unit_id deserialize_unit_id(const ustring &serialization);

struct unit_id deserialize_unit_id(const string &source);

/** loaded unit deserialization */
// deserialize a loaded unit (from either a ustring or a source text file)
struct loaded_unit deserialize_loaded_unit(const ustring &serialization);

struct loaded_unit deserialize_loaded_unit(const string &source);

#endif //UNIT_DESERIALIZATION_H
