project(mmko1)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories($ENV{HOME}../../usr/local/vxipnp/linux/bin)

include_directories(include/ enums/ $ENV{HOME}../../usr/local/vxipnp/linux/unmmko1/
        $ENV{HOME}../../usr/local/vxipnp/linux/include/)

file(GLOB_RECURSE SOURCE ./src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCE} main.cpp include/UpdateCommon.h)

target_link_libraries(mmko1 libunmmko1.so libunmbase.so libvisa.so)
