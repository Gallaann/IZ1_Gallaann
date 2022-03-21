add_library(storage storage.h storage.c)

target_include_directories(storage PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(storage LINK_PUBLIC pet)
