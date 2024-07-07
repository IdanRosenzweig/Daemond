#!/bin/bash

if test $# -ne 2; then
  echo "usage: ./serialize.sh [unit/id] [path to unit]"
  exit 1
fi

#serialization mode
MODE=$1
echo "mode is " $MODE
if [[ "$MODE" == "unit" ]]; then
  CODE_MODE=0
elif [[ "$MODE" == "id" ]]; then
  CODE_MODE=1
else
  echo "invalid serialization mode"
  exit 1
fi
echo "serialization code mode is " $CODE_MODE

# unit path
UNIT_PATH=$2

# subbuild dir
BUILD_DIR=./.serialize

# compile serializer
/opt/clion-2024.1.4/bin/cmake/linux/x64/bin/cmake -S ./ -B $BUILD_DIR -DUNIT_PATH=$UNIT_PATH -DSERIALIZE=$CODE_MODE
/opt/clion-2024.1.4/bin/cmake/linux/x64/bin/cmake --build $BUILD_DIR --target serializer -j 4

## compile serializer
#g++ src/main/serialize.cpp -DUNIT_PATH=$UNIT_PATH -DSERIALIZE=0 -c -o serializer.o
#g++ src/abstract/serialization/unit_serialization.cpp -c -o unit_serialization.o
#g++ -I /home/user/CLionProjects/daemond/ $UNIT_PATH -c -o unit_data.o
#g++ serializer.o unit_serialization.o unit_data.o -o $BUILD_DIR/serializer -L /usr/lib/x86_64-linux-gnu -l boost_serialization
#rm -f serializer.o unit_serialization.o unit_data.o

# run the serializer
$BUILD_DIR/serializer