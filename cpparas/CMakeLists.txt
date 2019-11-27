cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME cpparas)
project(${PROJECT_NAME})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS} include evdk_operators)

set(GENERAL_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GENERAL_FLAGS} -std=c++14")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GENERAL_FLAGS} -std=c11")

file(GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/util/*.cpp"
	"${PROJECT_SOURCE_DIR}/evdk_operators/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})
