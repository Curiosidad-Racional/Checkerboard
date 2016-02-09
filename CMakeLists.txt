cmake_minimum_required(VERSION 2.8.4)
project(Checkerboard)

message(STATUS "Project: ${PROJECT_NAME}")

# Version number
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)

message(STATUS "Version: ${VERSION_MAJOR}.${VERSION_MINOR}")

configure_file("${PROJECT_SOURCE_DIR}/src/config.h.in"
               "${PROJECT_SOURCE_DIR}/src/config.h")

message(STATUS "Config header file: ${PROJECT_SOURCE_DIR}/src/config.h")

find_package(Curses REQUIRED)
find_package(Threads)

include_directories(${CURSES_INCLUDE_DIR})

message(STATUS "Included directory: ${CURSES_INCLUDE_DIR}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

message(STATUS "CXX flags: ${CMAKE_CXX_FLAGS}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

message(STATUS "Runtime output directory: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

##########  PROJECT BINARIES  ##########

add_executable(client src/client.cpp src/board/piece.cpp src/board/board.cpp src/board/drawer.cpp src/board/boardhandler.cpp src/tcp/stream.cpp src/tcp/connector.cpp)

message(STATUS "Added client binary")

add_executable(server src/server.cpp src/tcp/stream.cpp src/tcp/acceptor.cpp)

message(STATUS "Added server binary")

target_link_libraries(client ${CURSES_LIBRARIES})
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT})

message(STATUS "Added ncurses and pthread libraries to link")

##########  TESTs  ##########
include(CTest)

##### BOARD TEST

set(TEST_BOARD_FILES test/board.cpp src/board/board.cpp src/board/piece.cpp src/board/drawer.cpp src/board/boardhandler.cpp)

add_executable(board ${TEST_BOARD_FILES})
target_link_libraries(board ${CURSES_LIBRARIES})


# Manual compilation

add_custom_target(test_board c++ -std=c++14 -o bin/board ${TEST_BOARD_FILES} -lncurses 2>&1 | less
                  DEPENDS ${TEST_BOARD_FILES}
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

##### MULTITHREAD TEST

set(TEST_MULTITHREAD_FILES test/multithread.cpp)

add_executable(multithread ${TEST_MULTITHREAD_FILES})
target_link_libraries(multithread ${CMAKE_THREAD_LIBS_INIT})

add_test(NAME Multithread COMMAND $<TARGET_FILE:multithread>)
set_tests_properties(Multithread
                     PROPERTIES
                     PASS_REGULAR_EXPRESSION "gets object: 9  9000")

# Manual compilation

add_custom_target(test_multithread c++ -std=c++14 -o bin/multithread ${TEST_MULTITHREAD_FILES} -lpthread 2>&1 | less
                  DEPENDS ${TEST_MULTITHREAD_FILES}
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

##### TCP TEST

set(TEST_TCP_FILES test/tcp.cpp src/tcp/connector.cpp src/tcp/acceptor.cpp src/tcp/stream.cpp)

add_executable(tcp ${TEST_TCP_FILES})
target_link_libraries(tcp ${CMAKE_THREAD_LIBS_INIT})

add_test(NAME Tcp COMMAND $<TARGET_FILE:tcp>)
set_tests_properties(Tcp
                     PROPERTIES
                     PASS_REGULAR_EXPRESSION "server recieve: Hola.*client recieve: Adios")

# Manual compilation

add_custom_target(test_tcp c++ -std=c++14 -o bin/tcp ${TEST_TCP_FILES} -lpthread 2>&1 | less
                  DEPENDS ${TEST_TCP_FILES}
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})


##########  INSTALATION  ##########

install(TARGETS server client DESTINATION bin)
