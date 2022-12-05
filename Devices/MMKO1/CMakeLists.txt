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
        ../../Libraries/mmko1-lib/include
        ../../Libraries/vxipnp/linux/include
        ../../Libraries/vxipnp/linux/include
        ../../Libraries/vxipnp/linux/unmmko1)

set(SOURCES)
set(HEADERS)
list(APPEND SOURCES
        MmkoModule.cpp
        ModuleFactory.cpp
        ../IDevice.cpp
        ../../Libraries/mmko1-lib/src/MainBus.cpp
        )

list(APPEND HEADERS
        ModuleFactory.h
        MmkoModule.h
        ../IDevice.h
        )


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} test.cpp)

target_link_libraries(${PROJECT_NAME} libmmko1lib.a libunmmko1.so libunmbase.so libvisa.so)