# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.18

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = C:\Users\yevhen.surkov\Documents\STM_WORKPLACE\stm32_spinner_project-2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\yevhen.surkov\Documents\STM_WORKPLACE\stm32_spinner_project-2

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	"C:\Program Files\CMake\bin\cmake-gui.exe" -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	"C:\Program Files\CMake\bin\cmake.exe" --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start C:\Users\yevhen.surkov\Documents\STM_WORKPLACE\stm32_spinner_project-2\CMakeFiles C:\Users\yevhen.surkov\Documents\STM_WORKPLACE\stm32_spinner_project-2\\CMakeFiles\progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start C:\Users\yevhen.surkov\Documents\STM_WORKPLACE\stm32_spinner_project-2\CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named stm32_spinner_project-2

# Build rule for target.
stm32_spinner_project-2: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles\Makefile2 stm32_spinner_project-2
.PHONY : stm32_spinner_project-2

# fast build rule for target.
stm32_spinner_project-2/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\stm32_spinner_project-2.dir\build.make CMakeFiles/stm32_spinner_project-2.dir/build
.PHONY : stm32_spinner_project-2/fast

Core/Src/main.obj: Core/Src/main.c.obj

.PHONY : Core/Src/main.obj

# target to build an object file
Core/Src/main.c.obj:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\stm32_spinner_project-2.dir\build.make CMakeFiles/stm32_spinner_project-2.dir/Core/Src/main.c.obj
.PHONY : Core/Src/main.c.obj

Core/Src/main.i: Core/Src/main.c.i

.PHONY : Core/Src/main.i

# target to preprocess a source file
Core/Src/main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\stm32_spinner_project-2.dir\build.make CMakeFiles/stm32_spinner_project-2.dir/Core/Src/main.c.i
.PHONY : Core/Src/main.c.i

Core/Src/main.s: Core/Src/main.c.s

.PHONY : Core/Src/main.s

# target to generate assembly for a file
Core/Src/main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles\stm32_spinner_project-2.dir\build.make CMakeFiles/stm32_spinner_project-2.dir/Core/Src/main.c.s
.PHONY : Core/Src/main.c.s

# Help Target
help:
	@echo The following are some of the valid targets for this Makefile:
	@echo ... all (the default if no target is provided)
	@echo ... clean
	@echo ... depend
	@echo ... edit_cache
	@echo ... rebuild_cache
	@echo ... stm32_spinner_project-2
	@echo ... Core/Src/main.obj
	@echo ... Core/Src/main.i
	@echo ... Core/Src/main.s
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles\Makefile.cmake 0
.PHONY : cmake_check_build_system
