cmake_minimum_required(VERSION 3.28)
project(daemond)

set(CMAKE_CXX_STANDARD 20)

# find libboost
find_package(Boost REQUIRED COMPONENTS serialization)
find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
message("boost include is ${Boost_INCLUDE_DIRS}")
# include project root directory
include_directories(/home/user/CLionProjects/daemond)

set(ABSTRACT_SRC
        src/abstract/unit/data/unit_id.h

        src/abstract/unit/data/unit_attr.h

        src/abstract/unit/data/unit_desc.h

        src/abstract/unit/data/unit_type.h

        src/abstract/unit/data/unit_priority.h

        src/abstract/unit/data/management/command.h
        src/abstract/unit/data/management/management_start.h
        src/abstract/unit/data/management/unit_management.h

        src/abstract/unit/data/dependencies/dependency.h
        src/abstract/unit/data/dependencies/conflict.h
        src/abstract/unit/data/dependencies/unit_dependencies.h

        src/abstract/unit/data/unit_data.h

        src/abstract/unit/runtime/runtime_data.h
        src/abstract/unit/runtime/runtime_status.h
        src/abstract/unit/runtime/runtime_status.cpp

        src/abstract/manager/manager.cpp
        src/abstract/manager/manager.h
        src/abstract/manager/manager_codes.h
        src/abstract/manager/loaded_unit.h
        src/abstract/manager/loaded_unit.cpp

        src/abstract/comms/comms_server.h
        src/abstract/comms/comms_session.h
        src/abstract/comms/comms_client.h
)

set(LIBC_SRC
        lib/trie.h
)

set(SERIALIZATION_SRC
        src/abstract/serialization/common.h
        src/abstract/serialization/unit_serialization.cpp
)

set(DESERIALIZATION_SRC
        src/abstract/serialization/common.h
        src/abstract/serialization/unit_deserialization.cpp
)

set(CACHE_SRC
        src/abstract/serialization/cache/cache.h
)

set(LINUX_SRC
        src/os/linux/linux_loaded_unit.h
        src/os/linux/linux_loaded_unit.cpp

        src/os/linux/linux_manager.h
        src/os/linux/linux_manager.cpp

        src/os/linux/linux_command.h
        src/os/linux/linux_command.cpp

        src/os/linux/comms/unix_sock/linux_comm_center.cpp
        src/os/linux/comms/unix_sock/linux_comm_center.h

        src/os/linux/comms/unix_sock/linux_comm_session.cpp
        src/os/linux/comms/unix_sock/linux_comm_session.h

        src/os/linux/comms/unix_sock/linux_comm_client.cpp
        src/os/linux/comms/unix_sock/linux_comm_client.h

        src/os/linux/cache.cpp
)

add_executable(daemond
        ${ABSTRACT_SRC}
        ${LIBC_SRC}
        ${SERIALIZATION_SRC}
        ${DESERIALIZATION_SRC}
        ${CACHE_SRC}
        ${LINUX_SRC}

        src/main/linux/daemond.cpp
)
target_link_libraries(daemond PRIVATE Boost::serialization)
target_link_libraries(daemond PRIVATE Boost::program_options)

add_executable(daemond_ctl
        ${ABSTRACT_SRC}
        ${LIBC_SRC}
        ${SERIALIZATION_SRC}
        ${DESERIALIZATION_SRC}
        ${CACHE_SRC}
        ${LINUX_SRC}

        src/main/linux/daemond_ctl.cpp
)
target_link_libraries(daemond_ctl PRIVATE Boost::serialization)
target_link_libraries(daemond_ctl PRIVATE Boost::program_options)

add_executable(serializer
        ${SERIALIZATION_SRC}
        ${CACHE_SRC}
        ${LINUX_SRC}

        src/main/serialize.cpp
)
target_link_libraries(serializer PRIVATE Boost::serialization)
# add the unit struct
set_source_files_properties(${UNIT_PATH} PROPERTIES LANGUAGE CXX)
target_sources(serializer PRIVATE ${UNIT_PATH})
# add serialization choice
target_compile_definitions(serializer PRIVATE SERIALIZE=${SERIALIZE})
