#ifndef UNIT_SER_COMMON_H
#define UNIT_SER_COMMON_H

#include "../unit/data/unit_data.h"

#include <stdint.h>
#include <string>
using namespace std;

using ustring = basic_string<uint8_t>;

#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>

namespace boost {
    namespace serialization {
        template<class Archive>
        void serialize(Archive &ar, unit_id &c, const unsigned int version) {
            ar & c.name;
        }

        template<class Archive>
        void serialize(Archive &ar, unit_desc &c, const unsigned int version) {
            ar & c.desc;
            ar & c.manual;
        }

        template<class Archive>
        void serialize(Archive &ar, unit_type &c, const unsigned int version) {
            ar & c;
        }

        template<class Archive>
        void serialize(Archive &ar, unit_priority &c, const unsigned int version) {
            ar & c.val;
        }

        template<class Archive>
        void serialize(Archive &ar, command &c, const unsigned int version) {
            ar & c.script;
        }

        template<class Archive>
        void serialize(Archive &ar, unit_management &c, const unsigned int version) {
            ar & c.start_unit.pre_start;
            ar & c.start_unit.start;
            ar & c.start_unit.post_start;
            ar & c.reload_unit.reload;
            ar & c.stop_unit.pre_stop;
            ar & c.stop_unit.stop;
            ar & c.stop_unit.post_stop;
        }

        template<class Archive>
        void serialize(Archive &ar, unit_attr &c, const unsigned int version) {
            ar & c.autostart_on_load;
            ar & c.auto_restart;
        }

        template<class Archive>
        void serialize(Archive &ar, dependency &c, const unsigned int version) {
            ar & c.id;
            ar & c.strict;
            ar & c.bind;
        }

        template<class Archive>
        void serialize(Archive &ar, conflict &c, const unsigned int version) {
            ar & c.id;
            ar & c.strict;
            ar & c.bind;
        }

        template<class Archive>
        void serialize(Archive &ar, unit_dependencies &c, const unsigned int version) {
            ar & c.needed;
            ar & c.conf;
        }

        template<class Archive>
        void serialize(Archive &ar, unit_data &c, const unsigned int version) {
            ar & c.id;
            ar & c.desc;
            ar & c.type;
            ar & c.prio;
            ar & c.mng;
            ar & c.attr;
            ar & c.deps;
        }
    }
}

#endif //UNIT_SER_COMMON_H
