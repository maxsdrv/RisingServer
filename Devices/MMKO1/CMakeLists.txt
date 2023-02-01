project(mmko1device)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_DEBUG -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls")

if (NOT DEFINED CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Debug")
endif()

link_directories(../../cmake-build-debug/Libraries/mmko1-lib/)

include_directories(../
        ../../Libraries/mmko1-lib/include/)

file(GLOB_RECURSE PRJ_SRC ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE PRJ_HEADERS ${PROJECT_SOURCE_DIR}/*.h)

#add_executable(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_HEADERS})
add_library(${PROJECT_NAME} ${PRJ_SRC} ${PRJ_HEADERS})

target_link_libraries(${PROJECT_NAME} mmko1lib ${Boost_LIBRARIES})
