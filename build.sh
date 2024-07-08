#!/bin/bash

PROJECT_DIR=.
TARGET_BUILD_DIR=$PROJECT_DIR/build
CMAKE_BUILD_DIR=$PROJECT_DIR/cmake_build

if [ $# != 1 ]; then
  echo "usage: ./build.sh [daemond/daemon_ctl/clean]"
  exit 1
fi

TARGET=$1

if [[ "$TARGET" == "clean" ]]; then # clean existing build
  rm -rf $TARGET_BUILD_DIR
  rm -rf $CMAKE_BUILD_DIR
  exit 0
elif [[ "$TARGET" != "daemond" && "$TARGET" != "daemond_ctl" ]]; then # otherwise, ensure valid build target
  echo "invalid target"
  exit 1
fi

# build target
cmake -S $PROJECT_DIR -B $CMAKE_BUILD_DIR
cmake --build $CMAKE_BUILD_DIR --target $TARGET

# make build dir if not exists
if ! test -d $TARGET_BUILD_DIR; then
  mkdir -p $TARGET_BUILD_DIR
fi

# copy output to build dir
cp $CMAKE_BUILD_DIR/$TARGET $TARGET_BUILD_DIR/

exit 0