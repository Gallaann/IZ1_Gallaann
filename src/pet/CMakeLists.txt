add_library(pet pet.h pet.c)

target_include_directories(pet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
