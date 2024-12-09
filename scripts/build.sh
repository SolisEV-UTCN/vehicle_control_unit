#!/bin/bash
case "${1,,}" in
 "release" )
    BUILD_TYPE=Release
    ;;
 "debug" )
    BUILD_TYPE=Debug
    ;;
 "minsizerel" )
    BUILD_TYPE=MinSizeRel
    ;;
 "relwithdebinfo" )
    BUILD_TYPE=RelWithDebInfo
    ;;
 * )
    echo "No valid build type provided. Using default 'Release' build type."
    BUILD_TYPE="Release"
    ;;
esac

source ./.venv/bin/activate

conan install . -pr dev/gcc-target.txt --build=missing -s build_type=$BUILD_TYPE

cd build/$BUILD_TYPE

cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../..

cmake --build . --clean-first

cd ../..

deactivate
