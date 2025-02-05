#include "src/abstract/unit/data/unit_data.h"
#include "src/abstract/serialization/unit_serialization.h"

#include <iostream>
using namespace std;

extern struct unit_data unit; // to be compiled with

int main() {
#ifndef SERIALIZE
#error define a choice for serialization
#endif

#if SERIALIZE == 0 // serialize all data unit data
    cout << "serializing unit data" << endl;
    serialize_unit_data_to_file(unit, "serialized_unit.txt");
    cout << "serialize finished" << endl;
#elif SERIALIZE == 1 // serialize only the unit id
    cout << "serializing unit id" << endl;
    serialize_unit_id_to_file(unit.id, "serialized_unit_id.txt");
    cout << "serialize finished" << endl;
#else
#error invalid choice for serialization
#endif
    // if (SERIALIZE == 0)
    //     serialize_unit_data_to_file(unit, "serialized_unit.txt");
    // else if (SERIALIZE == 1)
    //     serialize_unit_id_to_file(unit.id, "serialized_unit_id.txt");
}
