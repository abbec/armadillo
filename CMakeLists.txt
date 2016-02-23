cmake_minimum_required(VERSION 3.0)
SET(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

project(armadillo C ASM)

SET(CMAKE_SYSTEM_PROCESSOR arm)
SET(CMAKE_CROSSCOMPILING 1)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#configure_file(src/config.h.in ${CMAKE_BINARY_DIR}/config.h)
#configure_file(script/run.sh.in ${CMAKE_BINARY_DIR}/run.sh)

include_directories(${CMAKE_BINARY_DIR} "kernel/include")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -std=gnu99 -g -ffreestanding -O0 -Wall -target arm-none-eabi")

set(CMAKE_EXE_LINKER_FLAGS "-T ${PROJECT_SOURCE_DIR}/script/link.ld -ffreestanding -nostdlib")

add_subdirectory(kernel)
