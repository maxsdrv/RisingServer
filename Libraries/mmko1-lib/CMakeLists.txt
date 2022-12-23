project(mmko1lib)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

link_directories($ENV{HOME}../../usr/local/vxipnp/linux/bin)

set(HEADERS)
set(SOURCE)
set(SUPPORT)
set(INTERFACE)

list(APPEND HEADERS
        include/MonitorMode.h
        include/ControllerMode.h
        include/MMKOErrors.h
        include/AbonentMode.h
        include/MainBus.h
        include/enums.h
        )
list(APPEND SOURCE
        src/MonitorMode.cpp
        src/ControllerMode.cpp
        src/MMKOErrors.cpp
        src/AbonentMode.cpp
        src/MainBus.cpp
        )

include_directories(include/ $ENV{HOME}../../usr/local/vxipnp/linux/unmmko1/
$ENV{HOME}../../usr/local/vxipnp/linux/include/ )

include_directories(include src logs)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCE} ${SUPPORT})

target_link_libraries(${PROJECT_NAME} libunmmko1.so libunmbase.so libvisa.so)
