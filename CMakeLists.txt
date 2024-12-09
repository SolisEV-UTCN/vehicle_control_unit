cmake_minimum_required(VERSION 3.18)
project(vehicle_control_unit LANGUAGES CXX)

# Use C++ 20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optimization options
set(CMAKE_C_FLAGS_DEBUG "-Og -g -DDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g")
set(CMAKE_C_FLAGS_RELEASE "-Os -flto")
set(CMAKE_CXX_FLAGS_RELEASE "-Os -flto")

if(NOT DEFINED CONAN_OPTION_PLATFORM)
    message(FATAL_ERROR "The Conan option 'platform' is not defined. Please set the 'platform' option in your conanfile.txt or pass it via the command line(e.g., -o platform=stm32f303rb) . ")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CONAN_OPTION_PLATFORM})

# Enable compiler flags for a strict compiler
set(COMPILE_OPTIONS
    $<$<COMPILE_LANGUAGE:CXX>:-fms-extensions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-threadsafe-statics>
    -fstrict-volatile-bitfields
    -ffunction-sections
    -fno-threadsafe-statics
    -Werror
    -Wall
    -Wextra
    -Wcast-align
    -Wconversion
    -Wsign-conversion
    -Wold-style-cast
    -Wshadow
    -Wlogical-op
    -Wsuggest-override
    -Wsuggest-final-types
    -Wsuggest-final-methods
)
add_compile_options(${CPU_OPTIONS} ${COMPILE_OPTIONS})

# Main executable
include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR})
add_executable(${PROJECT_NAME}
    src/main.cpp
    ${STARTUP_FILES}
)

# Include conan packages
# find_package(libhal REQUIRED)

# Link conan packages
# target_link_libraries(${PROJECT_NAME} libhal::libhal)

# Use custom linker
target_link_libraries(${PROJECT_NAME}
    ${CPU_OPTIONS}
    -T${LINKER_SCRIPT}
    -nostartfiles
    -nolibc
    m
)

set_property(TARGET ${PROJECT_NAME} PROPERTY LINK_DEPENDS ${CMAKE_SOURCE_DIR}/${LINKER_SCRIPT})

include("cmake/flash.cmake")
