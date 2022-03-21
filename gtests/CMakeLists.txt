cmake_minimum_required(VERSION 3.0)
project(gtests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" )

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

file(GLOB TEST_FILES input_test_1.txt input_test_2.txt input_test_3.txt input_test_4.txt sort_test_sorted.txt sort_test_unsorted.txt)

add_executable(${PROJECT_NAME} gtests.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gtests PUBLIC pet storage GTest::gtest_main)