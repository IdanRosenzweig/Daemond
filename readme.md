# Daemond

## overview
Daemond is an infrastructure for managing daemons, services, and systems. It can be utilized for overseeing development environments, servers, cloud services, IoT devices, container orchestration, and more.

Daemond operates using the concept of units, representing any daemon, service, or system that it can control and manage, similar to systemctl units.

Supporting modern C++ for specifying units, Daemond offers greater flexibility and convenience compared to other popular daemon managers that rely on their own text file syntax.

Daemond is composed out of two components: the main `daemond` program, which internally manages units, and `daemond_ctl`, a companion program providing easy access and querying of the main `daemond` program. this combination is similar to the way `systemd` and `systemctl` interact. 

## usage
Daemond supports the following operations on units:
* load a unit (preparing it)
* start a loaded unit
* stop a loaded unit
* query the status of a unit
* unload a unit

all of these operations can be done using the `daemond_ctl` program while the `daemond` program runs in the background.

## unit specification
look at the struct under `src/abstract/unit/data/unit_data.h`. to specify a unit that can be manged by `daemond`, write any valid C++ source file that contain a `unit_data` struct named `unit`, with your own values in it.

you can look at sample units under `samples`.

## build
to build the daemond program, execute `./build.sh daemond`. the `daemond` program will be found under `build` directory.

to build the daemond_ctl side program, execute `./build.sh daemond_ctl`. the `daemond_ctl` program will be found under `build` directory.

to clean all builds, execute `./build.sh clean`.

## samples
the project contains sample units found under `samples`.

to start one of these units:
1. build `daemond` and `daemond_ctl`
2. execute `daemond` in the background
3. to load the unit, execute `daemond_ctl -c load -p samples/unit_name`
4. to start the unit, execute `daemond_ctl -c start -p samples/unit_name`

## dependencies
Daemond uses the `libboost` library for serialization of data and for command line parsing. make sure you have libboost when compiling the project.