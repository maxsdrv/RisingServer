project(MkoServer)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Test Gui Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Test Gui Network REQUIRED)

add_definitions(${Qt5Core_DEFINITIONS})
add_definitions(${Qt5Widgets_DEFINITIONS})
add_definitions(${Qt5Network_DEFINITIONS})

include_directories(${Qt5Core_INCLUDES})
include_directories(${Qt5Widgets_INCLUDES})
include_directories(${Qt5Network_INCLUDES})
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Test_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")

find_package(bsoncxx REQUIRED)

include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
###
add_definitions(-DNOMINMAX)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${Boost_LIBRARY_DIRS}
					../cmake-build-debug/Devices/MMKO1/)
include_directories(enums/ Gui/ Include/ ../Devices/MMKO1/ ../Devices/)

set(SERVER_SOURCES)
set(OPERATORS)
list(APPEND SERVER_SOURCES
		Include/MKOServer.h
		Source/MKOServer.cpp
		Include/ServerSocketRpc.h
		)
list(APPEND OPERATORS
		#		Operators/TestOperators.cpp
		Operators/ControlOperators14N.cpp)

file(GLOB_RECURSE SOURCE ./Source/*.cpp)
file(GLOB_RECURSE HEADERS_GUI Gui/*.h)
file(GLOB_RECURSE SOURCE_GUI Gui/*.cpp)

qt5_add_resources(SERVER_RESOURCES qrc/mezonin_server.qrc)

add_executable(mko_rpc_server ${SOURCE} ${SERVER_RESOURCES} ${SERVER_SOURCES} ${LOGGING_SERVER} ${OPERATORS} enums/enums.h enums/)

target_link_libraries(mko_rpc_server  ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES}
		mmko1device  mongo::bsoncxx_shared )

#[[ADD_CUSTOM_COMMAND(TARGET mko_rpc_server
		PRE_BUILD
		COMMAND rpc_parser ${PROJECT_SOURCE_DIR}/inc/MezoninServer.h ${PROJECT_SOURCE_DIR} server)]]


#[[
set(SERVER_PLUGIN_SOURCES Include/ServerPlugin.h Source/ServerPlugin.cpp Include/ServerRpc.h Source/ServerRpc.cpp)

add_library(mko_server_plugin SHARED ${SERVER_PLUGIN_SOURCES} ${SERVER_RESOURCES})
target_link_libraries(mko_server_plugin ${QT5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} common_functions db_ctrl mongo_controller_v3 socket_rpc devices)
qt5_use_modules(mko_server_plugin Core Widgets)

add_library(mko_server_visualize_plugin SHARED Include/ServerVisualPlugin.h Source/ServerVisualPlugin.cpp)
target_link_libraries(mko_server_visualize_plugin ${QT5Core_LIBRARIES} ${QT5Widgets_LIBRARIES} devices common_functions db_ctrl mongo_controller_v3 ${LIBMONGOCXX_LIBRARIES})
qt5_use_modules(mko_server_visualize_plugin Core Widgets)
]]





























