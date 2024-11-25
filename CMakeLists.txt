cmake_minimum_required(VERSION 3.10)

project(GC)

add_executable(GC 
    main.cpp 
    gc-functions/gc_init.cpp
    gc-functions/gc_insert.cpp
    gc-functions/gc_logic.cpp
    gc-functions/gc_getinfo.cpp
    menu-users/menu.cpp
    menu-users/usr.cpp
)

find_package(PostgreSQL REQUIRED)

include_directories(${PostgreSQL_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GC ${PostgreSQL_LIBRARIES})