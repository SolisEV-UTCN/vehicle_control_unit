#!/bin/bash

# Default values
if [ -z "$BUILD_TYPE" ]; then
   BUILD_TYPE=Release
fi
if [ -z "$TARGET" ]; then
   TARGET=stm32f303cb
fi

# Valid values
VALID_BUILD_TYPES=("Release" "Debug" "RelWithDebInfo" "MinSizeRel")
VALID_TARGETS=("stm32f103rb" "stm32f303cb")

# Print help
function help() {
   echo "Usage: $0 [-b <build_type>] [-t <target>]"
   echo "  -b, --build     Build type (Release, Debug, RelWithDebInfo, MinSizeRel). Default: Release."
   echo "  -t, --target    Target (stm32f103rb, stm32f303cb). Default: stm32f303cb."
   exit 1
}

# Validate value in a list
function is_valid() {
    local value="${1,,}"  # Convert to lowercase
    shift
    local valid_values=("$@")
    for valid in "${valid_values[@]}"; do
        if [[ "$value" == "${valid,,}" ]]; then
            echo "$valid"  # Return the correctly capitalized version
            return 0
        fi
    done
    return 1
}

# Validate BUILD_TYPE
BUILD_TYPE=$(is_valid "$BUILD_TYPE" "${VALID_BUILD_TYPES[@]}")
if [[ -z "$BUILD_TYPE" ]]; then
    echo "Error: Invalid build type '$BUILD_TYPE'. Valid types are: ${VALID_BUILD_TYPES[*]}"
    exit 1
fi

# Validate TARGET
TARGET=$(is_valid "$TARGET" "${VALID_TARGETS[@]}")
if [[ -z "$TARGET" ]]; then
    echo "Error: Invalid target '$TARGET'. Valid targets are: ${VALID_TARGETS[*]}"
    exit 1
fi

# Enable virtual environment
source ./.venv/bin/activate

# Install conan dependencies
if conan install . -pr dev/gcc-target-${TARGET}.txt --build=missing -s build_type=$BUILD_TYPE ; then
   cd build/$BUILD_TYPE

   # Generate Makefiles
   if cmake -GNinja -DCMAKE_TOOLCHAIN_FILE=generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../.. ; then
      # Build CMake
      cmake --build . --clean-first
   fi

   cd ../..
fi

# Disable virtual environment
deactivate

# Move binaries to mounted volume
mkdir -p /build/$BUILD_TYPE/$TARGET
mv -f build/$BUILD_TYPE/$TARGET/* /build/$BUILD_TYPE/$TARGET
