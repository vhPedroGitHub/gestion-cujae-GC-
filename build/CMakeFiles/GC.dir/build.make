# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build"

# Include any dependencies generated for this target.
include CMakeFiles/GC.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/GC.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/GC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GC.dir/flags.make

CMakeFiles/GC.dir/main.cpp.obj: CMakeFiles/GC.dir/flags.make
CMakeFiles/GC.dir/main.cpp.obj: CMakeFiles/GC.dir/includes_CXX.rsp
CMakeFiles/GC.dir/main.cpp.obj: C:/Users/HP\ i5-7/Documents/Pedro/ProyectoConvalidacionBasedeDatos/gestion-cujae(GC)/main.cpp
CMakeFiles/GC.dir/main.cpp.obj: CMakeFiles/GC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/GC.dir/main.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GC.dir/main.cpp.obj -MF CMakeFiles\GC.dir\main.cpp.obj.d -o CMakeFiles\GC.dir\main.cpp.obj -c "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\main.cpp"

CMakeFiles/GC.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GC.dir/main.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\main.cpp" > CMakeFiles\GC.dir\main.cpp.i

CMakeFiles/GC.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GC.dir/main.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\main.cpp" -o CMakeFiles\GC.dir\main.cpp.s

CMakeFiles/GC.dir/gc-functions/gc_init.cpp.obj: CMakeFiles/GC.dir/flags.make
CMakeFiles/GC.dir/gc-functions/gc_init.cpp.obj: CMakeFiles/GC.dir/includes_CXX.rsp
CMakeFiles/GC.dir/gc-functions/gc_init.cpp.obj: C:/Users/HP\ i5-7/Documents/Pedro/ProyectoConvalidacionBasedeDatos/gestion-cujae(GC)/gc-functions/gc_init.cpp
CMakeFiles/GC.dir/gc-functions/gc_init.cpp.obj: CMakeFiles/GC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/GC.dir/gc-functions/gc_init.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GC.dir/gc-functions/gc_init.cpp.obj -MF CMakeFiles\GC.dir\gc-functions\gc_init.cpp.obj.d -o CMakeFiles\GC.dir\gc-functions\gc_init.cpp.obj -c "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_init.cpp"

CMakeFiles/GC.dir/gc-functions/gc_init.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GC.dir/gc-functions/gc_init.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_init.cpp" > CMakeFiles\GC.dir\gc-functions\gc_init.cpp.i

CMakeFiles/GC.dir/gc-functions/gc_init.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GC.dir/gc-functions/gc_init.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_init.cpp" -o CMakeFiles\GC.dir\gc-functions\gc_init.cpp.s

CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.obj: CMakeFiles/GC.dir/flags.make
CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.obj: CMakeFiles/GC.dir/includes_CXX.rsp
CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.obj: C:/Users/HP\ i5-7/Documents/Pedro/ProyectoConvalidacionBasedeDatos/gestion-cujae(GC)/gc-functions/gc_insert.cpp
CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.obj: CMakeFiles/GC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.obj -MF CMakeFiles\GC.dir\gc-functions\gc_insert.cpp.obj.d -o CMakeFiles\GC.dir\gc-functions\gc_insert.cpp.obj -c "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_insert.cpp"

CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_insert.cpp" > CMakeFiles\GC.dir\gc-functions\gc_insert.cpp.i

CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_insert.cpp" -o CMakeFiles\GC.dir\gc-functions\gc_insert.cpp.s

CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.obj: CMakeFiles/GC.dir/flags.make
CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.obj: CMakeFiles/GC.dir/includes_CXX.rsp
CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.obj: C:/Users/HP\ i5-7/Documents/Pedro/ProyectoConvalidacionBasedeDatos/gestion-cujae(GC)/gc-functions/gc_logic.cpp
CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.obj: CMakeFiles/GC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.obj -MF CMakeFiles\GC.dir\gc-functions\gc_logic.cpp.obj.d -o CMakeFiles\GC.dir\gc-functions\gc_logic.cpp.obj -c "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_logic.cpp"

CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_logic.cpp" > CMakeFiles\GC.dir\gc-functions\gc_logic.cpp.i

CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_logic.cpp" -o CMakeFiles\GC.dir\gc-functions\gc_logic.cpp.s

CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.obj: CMakeFiles/GC.dir/flags.make
CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.obj: CMakeFiles/GC.dir/includes_CXX.rsp
CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.obj: C:/Users/HP\ i5-7/Documents/Pedro/ProyectoConvalidacionBasedeDatos/gestion-cujae(GC)/gc-functions/gc_getinfo.cpp
CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.obj: CMakeFiles/GC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.obj -MF CMakeFiles\GC.dir\gc-functions\gc_getinfo.cpp.obj.d -o CMakeFiles\GC.dir\gc-functions\gc_getinfo.cpp.obj -c "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_getinfo.cpp"

CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_getinfo.cpp" > CMakeFiles\GC.dir\gc-functions\gc_getinfo.cpp.i

CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\gc-functions\gc_getinfo.cpp" -o CMakeFiles\GC.dir\gc-functions\gc_getinfo.cpp.s

CMakeFiles/GC.dir/menu-users/menu.cpp.obj: CMakeFiles/GC.dir/flags.make
CMakeFiles/GC.dir/menu-users/menu.cpp.obj: CMakeFiles/GC.dir/includes_CXX.rsp
CMakeFiles/GC.dir/menu-users/menu.cpp.obj: C:/Users/HP\ i5-7/Documents/Pedro/ProyectoConvalidacionBasedeDatos/gestion-cujae(GC)/menu-users/menu.cpp
CMakeFiles/GC.dir/menu-users/menu.cpp.obj: CMakeFiles/GC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/GC.dir/menu-users/menu.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GC.dir/menu-users/menu.cpp.obj -MF CMakeFiles\GC.dir\menu-users\menu.cpp.obj.d -o CMakeFiles\GC.dir\menu-users\menu.cpp.obj -c "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\menu-users\menu.cpp"

CMakeFiles/GC.dir/menu-users/menu.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GC.dir/menu-users/menu.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\menu-users\menu.cpp" > CMakeFiles\GC.dir\menu-users\menu.cpp.i

CMakeFiles/GC.dir/menu-users/menu.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GC.dir/menu-users/menu.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\menu-users\menu.cpp" -o CMakeFiles\GC.dir\menu-users\menu.cpp.s

CMakeFiles/GC.dir/menu-users/usr.cpp.obj: CMakeFiles/GC.dir/flags.make
CMakeFiles/GC.dir/menu-users/usr.cpp.obj: CMakeFiles/GC.dir/includes_CXX.rsp
CMakeFiles/GC.dir/menu-users/usr.cpp.obj: C:/Users/HP\ i5-7/Documents/Pedro/ProyectoConvalidacionBasedeDatos/gestion-cujae(GC)/menu-users/usr.cpp
CMakeFiles/GC.dir/menu-users/usr.cpp.obj: CMakeFiles/GC.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/GC.dir/menu-users/usr.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/GC.dir/menu-users/usr.cpp.obj -MF CMakeFiles\GC.dir\menu-users\usr.cpp.obj.d -o CMakeFiles\GC.dir\menu-users\usr.cpp.obj -c "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\menu-users\usr.cpp"

CMakeFiles/GC.dir/menu-users/usr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/GC.dir/menu-users/usr.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\menu-users\usr.cpp" > CMakeFiles\GC.dir\menu-users\usr.cpp.i

CMakeFiles/GC.dir/menu-users/usr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/GC.dir/menu-users/usr.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\menu-users\usr.cpp" -o CMakeFiles\GC.dir\menu-users\usr.cpp.s

# Object files for target GC
GC_OBJECTS = \
"CMakeFiles/GC.dir/main.cpp.obj" \
"CMakeFiles/GC.dir/gc-functions/gc_init.cpp.obj" \
"CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.obj" \
"CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.obj" \
"CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.obj" \
"CMakeFiles/GC.dir/menu-users/menu.cpp.obj" \
"CMakeFiles/GC.dir/menu-users/usr.cpp.obj"

# External object files for target GC
GC_EXTERNAL_OBJECTS =

GC.exe: CMakeFiles/GC.dir/main.cpp.obj
GC.exe: CMakeFiles/GC.dir/gc-functions/gc_init.cpp.obj
GC.exe: CMakeFiles/GC.dir/gc-functions/gc_insert.cpp.obj
GC.exe: CMakeFiles/GC.dir/gc-functions/gc_logic.cpp.obj
GC.exe: CMakeFiles/GC.dir/gc-functions/gc_getinfo.cpp.obj
GC.exe: CMakeFiles/GC.dir/menu-users/menu.cpp.obj
GC.exe: CMakeFiles/GC.dir/menu-users/usr.cpp.obj
GC.exe: CMakeFiles/GC.dir/build.make
GC.exe: C:/Program\ Files/PostgreSQL/14/lib/libpq.lib
GC.exe: CMakeFiles/GC.dir/linkLibs.rsp
GC.exe: CMakeFiles/GC.dir/objects1.rsp
GC.exe: CMakeFiles/GC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable GC.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GC.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GC.dir/build: GC.exe
.PHONY : CMakeFiles/GC.dir/build

CMakeFiles/GC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GC.dir\cmake_clean.cmake
.PHONY : CMakeFiles/GC.dir/clean

CMakeFiles/GC.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)" "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)" "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build" "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build" "C:\Users\HP i5-7\Documents\Pedro\ProyectoConvalidacionBasedeDatos\gestion-cujae(GC)\build\CMakeFiles\GC.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/GC.dir/depend

