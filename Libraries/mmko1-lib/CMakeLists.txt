project(mmko1lib)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories($ENV{HOME}../../usr/local/vxipnp/linux/bin)

set(HEADERS)
set(SOURCE)
set(SUPPORT)
set(INTERFACE)

list(APPEND SUPPORT
        support/Actions.h
        support/Actions.cpp
        support/SCurDateTime.cpp
        support/SCurDateTime.h
        support/SFileLogger.cpp
        support/SFileLogger.h)
list(APPEND HEADERS
        include/MainBus.h
        include/MonitorMode.h
        include/ControllerMode.h
        include/MMKOErrors.h
        include/AbonentMode.h
        )
list(APPEND SOURCE
        src/MainBus.cpp
        src/MonitorMode.cpp
        src/ControllerMode.cpp
        src/MMKOErrors.cpp
        src/AbonentMode.cpp
        )
include_directories(../../Devices ../../Devices/MMKO1)

include_directories(include/ enums/ $ENV{HOME}../../usr/local/vxipnp/linux/unmmko1/
$ENV{HOME}../../usr/local/vxipnp/linux/include/ )

include_directories(include src support logs)


#add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCE} main.cpp)
add_library(${PROJECT_NAME} ${HEADERS} ${SOURCE} ${SUPPORT})

target_link_libraries(${PROJECT_NAME} libunmmko1.so libunmbase.so libvisa.so)
