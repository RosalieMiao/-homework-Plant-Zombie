# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\Program Files (x86)\Clion\CLion 2018.2.6\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "D:\Program Files (x86)\Clion\CLion 2018.2.6\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "D:\Code\Plants&Zombies"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "D:\Code\Plants&Zombies\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Plants_Zombies.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Plants_Zombies.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Plants_Zombies.dir/flags.make

CMakeFiles/Plants_Zombies.dir/main.cpp.obj: CMakeFiles/Plants_Zombies.dir/flags.make
CMakeFiles/Plants_Zombies.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Code\Plants&Zombies\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Plants_Zombies.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Plants_Zombies.dir\main.cpp.obj -c "D:\Code\Plants&Zombies\main.cpp"

CMakeFiles/Plants_Zombies.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Plants_Zombies.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Code\Plants&Zombies\main.cpp" > CMakeFiles\Plants_Zombies.dir\main.cpp.i

CMakeFiles/Plants_Zombies.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Plants_Zombies.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Code\Plants&Zombies\main.cpp" -o CMakeFiles\Plants_Zombies.dir\main.cpp.s

CMakeFiles/Plants_Zombies.dir/zombie.cpp.obj: CMakeFiles/Plants_Zombies.dir/flags.make
CMakeFiles/Plants_Zombies.dir/zombie.cpp.obj: ../zombie.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Code\Plants&Zombies\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Plants_Zombies.dir/zombie.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Plants_Zombies.dir\zombie.cpp.obj -c "D:\Code\Plants&Zombies\zombie.cpp"

CMakeFiles/Plants_Zombies.dir/zombie.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Plants_Zombies.dir/zombie.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Code\Plants&Zombies\zombie.cpp" > CMakeFiles\Plants_Zombies.dir\zombie.cpp.i

CMakeFiles/Plants_Zombies.dir/zombie.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Plants_Zombies.dir/zombie.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Code\Plants&Zombies\zombie.cpp" -o CMakeFiles\Plants_Zombies.dir\zombie.cpp.s

CMakeFiles/Plants_Zombies.dir/plant.cpp.obj: CMakeFiles/Plants_Zombies.dir/flags.make
CMakeFiles/Plants_Zombies.dir/plant.cpp.obj: ../plant.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Code\Plants&Zombies\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Plants_Zombies.dir/plant.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Plants_Zombies.dir\plant.cpp.obj -c "D:\Code\Plants&Zombies\plant.cpp"

CMakeFiles/Plants_Zombies.dir/plant.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Plants_Zombies.dir/plant.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Code\Plants&Zombies\plant.cpp" > CMakeFiles\Plants_Zombies.dir\plant.cpp.i

CMakeFiles/Plants_Zombies.dir/plant.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Plants_Zombies.dir/plant.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Code\Plants&Zombies\plant.cpp" -o CMakeFiles\Plants_Zombies.dir\plant.cpp.s

CMakeFiles/Plants_Zombies.dir/game.cpp.obj: CMakeFiles/Plants_Zombies.dir/flags.make
CMakeFiles/Plants_Zombies.dir/game.cpp.obj: ../game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Code\Plants&Zombies\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Plants_Zombies.dir/game.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Plants_Zombies.dir\game.cpp.obj -c "D:\Code\Plants&Zombies\game.cpp"

CMakeFiles/Plants_Zombies.dir/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Plants_Zombies.dir/game.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Code\Plants&Zombies\game.cpp" > CMakeFiles\Plants_Zombies.dir\game.cpp.i

CMakeFiles/Plants_Zombies.dir/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Plants_Zombies.dir/game.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Code\Plants&Zombies\game.cpp" -o CMakeFiles\Plants_Zombies.dir\game.cpp.s

CMakeFiles/Plants_Zombies.dir/bullet.cpp.obj: CMakeFiles/Plants_Zombies.dir/flags.make
CMakeFiles/Plants_Zombies.dir/bullet.cpp.obj: ../bullet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Code\Plants&Zombies\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Plants_Zombies.dir/bullet.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Plants_Zombies.dir\bullet.cpp.obj -c "D:\Code\Plants&Zombies\bullet.cpp"

CMakeFiles/Plants_Zombies.dir/bullet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Plants_Zombies.dir/bullet.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Code\Plants&Zombies\bullet.cpp" > CMakeFiles\Plants_Zombies.dir\bullet.cpp.i

CMakeFiles/Plants_Zombies.dir/bullet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Plants_Zombies.dir/bullet.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Code\Plants&Zombies\bullet.cpp" -o CMakeFiles\Plants_Zombies.dir\bullet.cpp.s

CMakeFiles/Plants_Zombies.dir/object.cpp.obj: CMakeFiles/Plants_Zombies.dir/flags.make
CMakeFiles/Plants_Zombies.dir/object.cpp.obj: ../object.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="D:\Code\Plants&Zombies\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Plants_Zombies.dir/object.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Plants_Zombies.dir\object.cpp.obj -c "D:\Code\Plants&Zombies\object.cpp"

CMakeFiles/Plants_Zombies.dir/object.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Plants_Zombies.dir/object.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "D:\Code\Plants&Zombies\object.cpp" > CMakeFiles\Plants_Zombies.dir\object.cpp.i

CMakeFiles/Plants_Zombies.dir/object.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Plants_Zombies.dir/object.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "D:\Code\Plants&Zombies\object.cpp" -o CMakeFiles\Plants_Zombies.dir\object.cpp.s

# Object files for target Plants_Zombies
Plants_Zombies_OBJECTS = \
"CMakeFiles/Plants_Zombies.dir/main.cpp.obj" \
"CMakeFiles/Plants_Zombies.dir/zombie.cpp.obj" \
"CMakeFiles/Plants_Zombies.dir/plant.cpp.obj" \
"CMakeFiles/Plants_Zombies.dir/game.cpp.obj" \
"CMakeFiles/Plants_Zombies.dir/bullet.cpp.obj" \
"CMakeFiles/Plants_Zombies.dir/object.cpp.obj"

# External object files for target Plants_Zombies
Plants_Zombies_EXTERNAL_OBJECTS =

Plants_Zombies.exe: CMakeFiles/Plants_Zombies.dir/main.cpp.obj
Plants_Zombies.exe: CMakeFiles/Plants_Zombies.dir/zombie.cpp.obj
Plants_Zombies.exe: CMakeFiles/Plants_Zombies.dir/plant.cpp.obj
Plants_Zombies.exe: CMakeFiles/Plants_Zombies.dir/game.cpp.obj
Plants_Zombies.exe: CMakeFiles/Plants_Zombies.dir/bullet.cpp.obj
Plants_Zombies.exe: CMakeFiles/Plants_Zombies.dir/object.cpp.obj
Plants_Zombies.exe: CMakeFiles/Plants_Zombies.dir/build.make
Plants_Zombies.exe: CMakeFiles/Plants_Zombies.dir/linklibs.rsp
Plants_Zombies.exe: CMakeFiles/Plants_Zombies.dir/objects1.rsp
Plants_Zombies.exe: CMakeFiles/Plants_Zombies.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="D:\Code\Plants&Zombies\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable Plants_Zombies.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Plants_Zombies.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Plants_Zombies.dir/build: Plants_Zombies.exe

.PHONY : CMakeFiles/Plants_Zombies.dir/build

CMakeFiles/Plants_Zombies.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Plants_Zombies.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Plants_Zombies.dir/clean

CMakeFiles/Plants_Zombies.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "D:\Code\Plants&Zombies" "D:\Code\Plants&Zombies" "D:\Code\Plants&Zombies\cmake-build-debug" "D:\Code\Plants&Zombies\cmake-build-debug" "D:\Code\Plants&Zombies\cmake-build-debug\CMakeFiles\Plants_Zombies.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Plants_Zombies.dir/depend
