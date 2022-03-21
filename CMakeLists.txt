cmake_minimum_required(VERSION 3.21)

project(IZ1-Gallaann)

#set(LCOV_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
#set(LCOV_LINK_FLAGS "-lgcov")

if (test)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LCOV_COMPILE_FLAGS} -coverage -lgcov -g -Wall -Werror")
    set(CMAKE_CXX_COMPILE_FLAGS "${CMAKE_CXX_FLAGS} ${LCOV_LINK_FLAGS}")

else ()
    set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused -Werror -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

endif()
set(CMAKE_C_FLAGS "--coverage")

add_executable(main main.c)

add_subdirectory(src)
add_subdirectory(gtests)

target_link_libraries(main LINK_PUBLIC pet storage)
