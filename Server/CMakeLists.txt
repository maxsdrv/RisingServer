project(MkoServer)
cmake_minimum_required(VERSION 2.8)

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
include_directories($ENV{VISA_HOME}include)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(../../lib/db_ctrl)
include_directories(../../lib/common_functions)
include_directories(../../lib/mongo_ctrl_v3)
include_directories(../../lib/socket_rpc/include)
include_directories(../../lib/interfaces)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Test_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Network_EXECUTABLE_COMPILE_FLAGS}")

find_package(libmongocxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
###
add_definitions(-DNOMINMAX)

link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY} ${Boost_LIBRARY_DIRS}
		$ENV{OMNIBUS_HOME}/lib $ENV{MONGO_HOME}/lib
		$ENV{VISA_LIBS})
include_directories(../../Devices ../../Devices/instruments ../../Devices/14N737_14N736/ enums/ inc/ Gui/)

set(SERVER_SOURCES)
set(OPERATORS)
list(APPEND SERVER_SOURCES
		Include/MezoninServer.h  	 Source/MezoninServer.cpp
		Include/ServerSocketRpc.h	 Source/ServerSocketRpc.cpp
		Source/main.cpp
		)

list(APPEND OPERATORS
		#		Operators/TestOperators.cpp
		Operators/ControlOperators14N.cpp)

file(GLOB_RECURSE SOURCE ./Source/*.cpp)
file(GLOB_RECURSE SOURCE ./Gui/*.cpp)

qt5_add_resources(SERVER_RESOURCES qrc/mezonin_server.qrc)

add_executable(mezonin_rpc_server WIN32 ${SOURCE} ${SERVER_RESOURCES} ${SERVER_SOURCES} ${LOGGING_SERVER} ${OPERATORS} enums/enums.h enums/)

target_link_libraries(mezonin_rpc_server ${Qt5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5Network_LIBRARIES}
		socket_rpc  mongo_controller_v3 common_functions db_ctrl devices ${LIBMONGOCXX_LIBRARIES} )

ADD_CUSTOM_COMMAND(TARGET mezonin_rpc_server
		PRE_BUILD
		COMMAND rpc_parser ${PROJECT_SOURCE_DIR}/inc/MezoninServer.h ${PROJECT_SOURCE_DIR} server)


set(SERVER_PLUGIN_SOURCES Include/ServerPlugin.h Source/ServerPlugin.cpp Include/ServerRpc.h Source/ServerRpc.cpp)

add_library(mezonin_server_plugin SHARED ${SERVER_PLUGIN_SOURCES} ${SERVER_RESOURCES})
target_link_libraries(mezonin_server_plugin ${QT5Core_LIBRARIES} ${Qt5Widgets_LIBRARIES} common_functions db_ctrl mongo_controller_v3 socket_rpc devices)
qt5_use_modules(mezonin_server_plugin Core Widgets)

add_library(mezonin_server_visualize_plugin SHARED Include/ServerVisualPlugin.h Source/ServerVisualPlugin.cpp)
target_link_libraries(mezonin_server_visualize_plugin ${QT5Core_LIBRARIES} ${QT5Widgets_LIBRARIES} devices common_functions db_ctrl mongo_controller_v3 ${LIBMONGOCXX_LIBRARIES})
qt5_use_modules(mezonin_server_visualize_plugin Core Widgets)





























