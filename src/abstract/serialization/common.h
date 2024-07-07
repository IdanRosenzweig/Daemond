#ifndef UNIT_SER_COMMON_H
#define UNIT_SER_COMMON_H

#include "src/abstract/unit/data/unit_data.h"
#include "src/abstract/unit/loaded_unit.h"

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
        void serialize(Archive &ar, unit_exec &c, const unsigned int version) {
            ar & c.start.pre_start;
            ar & c.start.start;
            ar & c.start.post_start;
            ar & c.reload.reload;
            ar & c.stop.pre_stop;
            ar & c.stop.stop;
            ar & c.stop.post_stop;
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
            ar & c.exec;
            ar & c.attr;
            ar & c.deps;
        }

        template<class Archive>
        void serialize(Archive &ar, runtime_data &c, const unsigned int version) {
            ar & c.status;
        }

        template<class Archive>
        void serialize(Archive &ar, loaded_unit &c, const unsigned int version) {
            ar & c.data;
            ar & c.runtime;
        }
    }
}

#endif //UNIT_SER_COMMON_H
