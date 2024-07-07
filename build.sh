#!/bin/bash

if [ $# != 1 ]; then
  echo "usage: ./build.sh [daemond/daemon_ctl]"
  exit -1
fi

TARGET=$1
if [[ "$TARGET" != "daemond" && "$TARGET" != "daemond_ctl" ]]; then
  echo "invalid target"
  exit -1
fi

PROJECT_DIR=.
TARGET_BUILD_DIR=$PROJECT_DIR/build
CMAKE_BUILD_DIR=$PROJECT_DIR/cmake_build

# build daemond
cmake -S $PROJECT_DIR -B $CMAKE_BUILD_DIR
cmake --build $CMAKE_BUILD_DIR --target $TARGET

# make build dir if not exists
if ! test -d $TARGET_BUILD_DIR; then
  mkdir -p $TARGET_BUILD_DIR
fi

# copy output to build dir
cp $CMAKE_BUILD_DIR/$TARGET $TARGET_BUILD_DIR/

