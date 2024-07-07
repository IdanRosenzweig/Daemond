#!/bin/bash

if test $# -ne 2; then
  echo "usage: ./serialize.sh [unit/id] [path to unit]"
  exit 1
fi

# serialization mode
MODE=$1
if [[ "$MODE" == "unit" ]]; then
  CODE_MODE=0
elif [[ "$MODE" == "id" ]]; then
  CODE_MODE=1
else
  echo "invalid serialization mode"
  exit 1
fi

# unit path
UNIT_PATH=$2

# build dir
BUILD_DIR=./.serialize

# compile serializer
echo compiling serializer
cmake -S $(dirname $0)/../ -B $BUILD_DIR -DUNIT_PATH=$UNIT_PATH -DSERIALIZE=$CODE_MODE
cmake --build $BUILD_DIR --target serializer -j 4

# run the serializer
echo running serializer
$BUILD_DIR/serializer