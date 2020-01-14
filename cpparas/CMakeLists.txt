cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME cpparas)
project(${PROJECT_NAME})

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM gtkmm-3.0)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

option(BUILD_DOC "Build documentation" OFF)
option(BUILD_TESTS "Build unit tests" OFF)

if (BUILD_DOC)
  # check if Doxygen is installed
  find_package(Doxygen)
  if (DOXYGEN_FOUND)
      # set input and output files
      set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
      set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

      # request to configure the file
      configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
      message("Doxygen build started")

      # note the option ALL which allows to build the docs together with the application
      add_custom_target( doc_doxygen ALL
          COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
          WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
          COMMENT "Generating documentation with Doxygen"
          VERBATIM )
  else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
  endif (DOXYGEN_FOUND)
endif()

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS} include evdk_operators)

set(GENERAL_FLAGS "-Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GENERAL_FLAGS} -std=c++14 -pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GENERAL_FLAGS} -std=c11")

file(GLOB SOURCES
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*/*.cpp"
	"${PROJECT_SOURCE_DIR}/evdk_operators/*.c")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${GTKMM_LIBRARIES})

if (BUILD_TESTS)
  pkg_check_modules(GTEST gtest>=1.6.0)
  include_directories(${GTEST_INCLUDE_DIRS})

  file(GLOB TEST_SOURCES
	  ${SOURCES}
          "${PROJECT_SOURCE_DIR}/tests/*.cpp")
  list(REMOVE_ITEM TEST_SOURCES "${PROJECT_SOURCE_DIR}/src/main.cpp")
  add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})

  target_link_libraries(${PROJECT_NAME}_tests ${GTEST_LIBRARIES} ${GTKMM_LIBRARIES})
endif()
