project(test_mko)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_DEBUG -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls")

find_package(Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(../Libraries/mmko1-lib/include)

add_executable(${PROJECT_NAME} test_lib_mko.cpp)

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} mmko1lib)
