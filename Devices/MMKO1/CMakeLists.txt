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
        ../../Libraries/vxipnp/linux/unmmko1)

set(MKO_DEVICE_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/../../Libraries/mmko1-lib/include")
set(${PROJECT_NAME}_SRC test.cpp MmkoModule.cpp ModuleFactory.cpp ../IDevice.cpp)
set(${PROJECT_NAME}_LIB_SRC ../../Libraries/mmko1-lib/src/MainBus.cpp
        ../../Libraries/mmko1-lib/src/AbonentMode.cpp
        ../../Libraries/mmko1-lib/src/ControllerMode.cpp
        ../../Libraries/mmko1-lib/src/MonitorMode.cpp
        ../../Libraries/mmko1-lib/src/MMKOErrors.cpp)

source_group(source FILES "${${PROJECT_NAME}_SRC}" "${${PROJECT_NAME}_LIB_SRC}")

add_executable(${PROJECT_NAME} "${${PROJECT_NAME}_SRC}" "${${PROJECT_NAME}_LIB_SRC}")

target_link_libraries(${PROJECT_NAME} libmmko1lib.a libunmmko1.so libunmbase.so libvisa.so)