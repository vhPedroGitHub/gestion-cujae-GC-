cmake_minimum_required(VERSION 3.10)

project(GC)

add_executable(GC 
    main.cpp 
    gc-functions/complements.cpp
    gc-functions/consult.cpp
    gc-functions/gc_getinfo.cpp
    gc-functions/gc_init.cpp
    gc-functions/gc_insert.cpp
    gc-functions/gc_logic.cpp
    gc-functions/gc_opcprof.cpp
    gc-functions/gc_verify.cpp

    menu-users/menu_admin.cpp
    menu-users/menu_prof.cpp
    menu-users/menu_student.cpp
    menu-users/usr.cpp
)

find_package(PostgreSQL REQUIRED)

include_directories(${PostgreSQL_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(GC ${PostgreSQL_LIBRARIES})