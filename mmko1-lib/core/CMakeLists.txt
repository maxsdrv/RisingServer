project(mmko1)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories($ENV{HOME}../../usr/local/vxipnp/linux/bin)

set(HEADERS)
set(SOURCE)
set(SUPPORT)

list(APPEND SUPPORT
        support/Actions.h
        support/Actions.cpp
        support/SCurDateTime.cpp
        support/SCurDateTime.h
        support/SFileLogger.cpp
        support/SFileLogger.h)
list(APPEND HEADERS
        include/ITestMmko.h
        include/TestMmko.h)
list(APPEND SOURCE
        src/TestMmko.cpp)

include_directories(include/ enums/ $ENV{HOME}../../usr/local/vxipnp/linux/unmmko1/
        $ENV{HOME}../../usr/local/vxipnp/linux/include/)
include_directories(include src defines enums support logs)


add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCE} ${SUPPORT} main.cpp)

target_link_libraries(mmko1 libunmmko1.so libunmbase.so libvisa.so)
