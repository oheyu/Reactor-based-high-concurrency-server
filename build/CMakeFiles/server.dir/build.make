# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aaron/Projects/Reactor_Server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aaron/Projects/Reactor_Server/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/src/Channel.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/Channel.cpp.o: /home/aaron/Projects/Reactor_Server/src/Channel.cpp
CMakeFiles/server.dir/src/Channel.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aaron/Projects/Reactor_Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/src/Channel.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/Channel.cpp.o -MF CMakeFiles/server.dir/src/Channel.cpp.o.d -o CMakeFiles/server.dir/src/Channel.cpp.o -c /home/aaron/Projects/Reactor_Server/src/Channel.cpp

CMakeFiles/server.dir/src/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/src/Channel.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aaron/Projects/Reactor_Server/src/Channel.cpp > CMakeFiles/server.dir/src/Channel.cpp.i

CMakeFiles/server.dir/src/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/Channel.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aaron/Projects/Reactor_Server/src/Channel.cpp -o CMakeFiles/server.dir/src/Channel.cpp.s

CMakeFiles/server.dir/src/Epoll.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/Epoll.cpp.o: /home/aaron/Projects/Reactor_Server/src/Epoll.cpp
CMakeFiles/server.dir/src/Epoll.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aaron/Projects/Reactor_Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/src/Epoll.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/Epoll.cpp.o -MF CMakeFiles/server.dir/src/Epoll.cpp.o.d -o CMakeFiles/server.dir/src/Epoll.cpp.o -c /home/aaron/Projects/Reactor_Server/src/Epoll.cpp

CMakeFiles/server.dir/src/Epoll.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/src/Epoll.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aaron/Projects/Reactor_Server/src/Epoll.cpp > CMakeFiles/server.dir/src/Epoll.cpp.i

CMakeFiles/server.dir/src/Epoll.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/Epoll.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aaron/Projects/Reactor_Server/src/Epoll.cpp -o CMakeFiles/server.dir/src/Epoll.cpp.s

CMakeFiles/server.dir/src/InetAddress.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/InetAddress.cpp.o: /home/aaron/Projects/Reactor_Server/src/InetAddress.cpp
CMakeFiles/server.dir/src/InetAddress.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aaron/Projects/Reactor_Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/src/InetAddress.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/InetAddress.cpp.o -MF CMakeFiles/server.dir/src/InetAddress.cpp.o.d -o CMakeFiles/server.dir/src/InetAddress.cpp.o -c /home/aaron/Projects/Reactor_Server/src/InetAddress.cpp

CMakeFiles/server.dir/src/InetAddress.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/src/InetAddress.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aaron/Projects/Reactor_Server/src/InetAddress.cpp > CMakeFiles/server.dir/src/InetAddress.cpp.i

CMakeFiles/server.dir/src/InetAddress.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/InetAddress.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aaron/Projects/Reactor_Server/src/InetAddress.cpp -o CMakeFiles/server.dir/src/InetAddress.cpp.s

CMakeFiles/server.dir/src/Socket.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/Socket.cpp.o: /home/aaron/Projects/Reactor_Server/src/Socket.cpp
CMakeFiles/server.dir/src/Socket.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aaron/Projects/Reactor_Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/src/Socket.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/Socket.cpp.o -MF CMakeFiles/server.dir/src/Socket.cpp.o.d -o CMakeFiles/server.dir/src/Socket.cpp.o -c /home/aaron/Projects/Reactor_Server/src/Socket.cpp

CMakeFiles/server.dir/src/Socket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/src/Socket.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aaron/Projects/Reactor_Server/src/Socket.cpp > CMakeFiles/server.dir/src/Socket.cpp.i

CMakeFiles/server.dir/src/Socket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/Socket.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aaron/Projects/Reactor_Server/src/Socket.cpp -o CMakeFiles/server.dir/src/Socket.cpp.s

CMakeFiles/server.dir/src/epoll_server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/epoll_server.cpp.o: /home/aaron/Projects/Reactor_Server/src/epoll_server.cpp
CMakeFiles/server.dir/src/epoll_server.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aaron/Projects/Reactor_Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server.dir/src/epoll_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/epoll_server.cpp.o -MF CMakeFiles/server.dir/src/epoll_server.cpp.o.d -o CMakeFiles/server.dir/src/epoll_server.cpp.o -c /home/aaron/Projects/Reactor_Server/src/epoll_server.cpp

CMakeFiles/server.dir/src/epoll_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/server.dir/src/epoll_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aaron/Projects/Reactor_Server/src/epoll_server.cpp > CMakeFiles/server.dir/src/epoll_server.cpp.i

CMakeFiles/server.dir/src/epoll_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/epoll_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aaron/Projects/Reactor_Server/src/epoll_server.cpp -o CMakeFiles/server.dir/src/epoll_server.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/src/Channel.cpp.o" \
"CMakeFiles/server.dir/src/Epoll.cpp.o" \
"CMakeFiles/server.dir/src/InetAddress.cpp.o" \
"CMakeFiles/server.dir/src/Socket.cpp.o" \
"CMakeFiles/server.dir/src/epoll_server.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

/home/aaron/Projects/Reactor_Server/bin/server: CMakeFiles/server.dir/src/Channel.cpp.o
/home/aaron/Projects/Reactor_Server/bin/server: CMakeFiles/server.dir/src/Epoll.cpp.o
/home/aaron/Projects/Reactor_Server/bin/server: CMakeFiles/server.dir/src/InetAddress.cpp.o
/home/aaron/Projects/Reactor_Server/bin/server: CMakeFiles/server.dir/src/Socket.cpp.o
/home/aaron/Projects/Reactor_Server/bin/server: CMakeFiles/server.dir/src/epoll_server.cpp.o
/home/aaron/Projects/Reactor_Server/bin/server: CMakeFiles/server.dir/build.make
/home/aaron/Projects/Reactor_Server/bin/server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/aaron/Projects/Reactor_Server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable /home/aaron/Projects/Reactor_Server/bin/server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: /home/aaron/Projects/Reactor_Server/bin/server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/aaron/Projects/Reactor_Server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aaron/Projects/Reactor_Server /home/aaron/Projects/Reactor_Server /home/aaron/Projects/Reactor_Server/build /home/aaron/Projects/Reactor_Server/build /home/aaron/Projects/Reactor_Server/build/CMakeFiles/server.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/server.dir/depend

