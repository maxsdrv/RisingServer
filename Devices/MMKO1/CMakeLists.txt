project(mmko1device)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT DEFINED CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug")
endif()

link_directories(../../cmake-build-debug/Libraries/mmko1-lib/
        ../../Libraries/vxipnp/linux/bin/)

include_directories(../
        ../../Libraries/mmko1-lib/include/
        ../../Libraries/vxipnp/linux/include/
        ../../Libraries/vxipnp/linux/unmmko1)

file(GLOB_RECURSE PRJ_SRC ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE PRJ_HEADERS ${PROJECT_SOURCE_DIR}/*.h)

add_executable(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_HEADERS})

target_link_libraries(${PROJECT_NAME} mmko1lib libunmmko1.so libunmbase.so libvisa.so)