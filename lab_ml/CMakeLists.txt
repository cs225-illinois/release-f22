cmake_minimum_required(VERSION 3.10)

# Assignment Information (these are the *only* things you need to change here between assignments)
set(assignment_name "lab_ml") # Name of the assignment
set(assignment_version 1.2022.05.0) # Version, where minor=semester_year, patch=semester_end_month, tweak=revision
set(assignment_entrypoints "nim") # Entrypoints to run the program
set(assignment_clean_rm "nim_graph.dot" "nim_graph.png") # Generated files that should be removed with "make clean"
set(assignment_container "fa22") # Container we are targetting

# Add color support to our messages.
# See: https://stackoverflow.com/questions/18968979/how-to-get-colorized-output-with-cmake
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColorReset   "${Esc}[m")
  set(ColorBold    "${Esc}[1m")
  set(ColorRed     "${Esc}[31m")
  set(ColorGreen   "${Esc}[32m")
  set(ColorYellow  "${Esc}[33m")
  set(ColorBlue    "${Esc}[34m")
  set(ColorMagenta "${Esc}[35m")
  set(ColorCyan    "${Esc}[36m")
  set(ColorWhite   "${Esc}[37m")
endif()

site_name(SITE_NAME)

if(SITE_NAME MATCHES "ews.illinois.edu$")
    set(EWS TRUE)
endif()

# Handle unsupported container warnings.
# Default to remind students to use our container, unless they are using our targeted container.
set(REMIND_CONTAINER TRUE)
if(DEFINED ENV{CS225_CONTAINER})
    if($ENV{CS225_CONTAINER} STREQUAL ${assignment_container})
        # This is the container we are targetting, so don't print the reminder.
        unset(REMIND_CONTAINER)
    elseif($ENV{CS225_CONTAINER} MATCHES ".+-arm")
        message(STATUS "${ColorYellow}Looks like you are using an ARM/M1 container.${ColorReset}")
    else()
        message(STATUS "${ColorYellow}Looks like you are using an unrecognized container.${ColorReset}")
    endif()
elseif(DEFINED EWS)
    message(STATUS "${ColorYellow}Looks like you are using EWS.${ColorReset}")
    message(STATUS "${ColorRed}EWS is outdated and unsupported. Use at your own risk.${ColorReset}")
else()
    # Warn students who are not using our container at all.
    message(STATUS "${ColorYellow}Looks like you are not using the provided container.${ColorReset}")
endif()

# Remind students to use our container.
if(DEFINED REMIND_CONTAINER)
    message(WARNING "${ColorYellow}Make sure you test on the CS225 container before the deadline.${ColorReset}")
endif()

# Disable in-source builds (running "cmake ." in the project directory)
# This is bad practice as it pollutes the project directory.
# See: https://dpiepgrass.medium.com/cmake-fights-against-disabling-in-source-builds-ab1d71c1d26f
if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}") 
  message(FATAL_ERROR "${ColorRed}In-source builds are disabled.\n"
    "Create a subdirectory `build/` and use `cmake ..` inside it.\n"
    "${ColorBold}Delete `CMakeCache.txt` and `CMakeFiles/` before you continue.${ColorReset}")
endif()

# Specify C++ compiler and linker.
if(NOT DEFINED EWS)
    set(CMAKE_C_COMPILER "/usr/bin/clang")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
    set(CMAKE_LINKER "/usr/bin/clang++")
else()
    set(CMAKE_C_COMPILER "/software/llvm-6.0.1/bin/clang")
    set(CMAKE_CXX_COMPILER "/software/llvm-6.0.1/bin/clang++")
    set(CMAKE_LINKER "/software/llvm-6.0.1/bin/clang++")

    # Add other required flags for EWS.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif()

# Specify C++ Standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define project.   
project(${assignment_name} VERSION ${assignment_version})

# Specify Debug build.
set(CMAKE_BUILD_TYPE Debug)

# Specify warnings for all builds.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function")

# Specify debug symbols and no optimizations for Debug builds.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DCS225_SOLUTION -D_GLIBCXX_DEBUG -O0 -gdwarf-4")

# Specify additional clean files.
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_CLEAN_FILES "${assignment_clean_rm}")

# Add Catch2.
# Note: Ubuntu 20.04 LTS does not have Catch2 on apt
# See: https://github.com/catchorg/Catch2/issues/1383
if(NOT DEFINED EWS)
    find_package(Catch2 REQUIRED)
else()
    include(FetchContent)

    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.0-preview3
    )

    FetchContent_MakeAvailable(Catch2)

    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif()

# Path definitions.
set(lib_dir ${CMAKE_SOURCE_DIR}/lib)
set(src_dir ${CMAKE_SOURCE_DIR}/src)
set(tests_dir ${CMAKE_SOURCE_DIR}/tests)
set(entry_dir ${CMAKE_SOURCE_DIR}/entry)

# Run CMakeLists in lib_dir to build our required libraries.
add_subdirectory(${lib_dir})

# Run CMakeLists in src_dir to build the student's code.
add_subdirectory(${src_dir})

# Add the Catch2 entrypoint using Catch2, our libs and src code.
file(GLOB_RECURSE tests_src CONFIGURE_DEPENDS ${tests_dir}/*.cpp)

include(Catch)

add_executable(test ${tests_src})
target_link_libraries(test PRIVATE Catch2::Catch2WithMain libs src)

catch_discover_tests(test)

# Add the assignment entrypoints using our libs and src code.
foreach(entrypoint IN LISTS assignment_entrypoints)
    add_executable(${entrypoint} ${entry_dir}/${entrypoint}.cpp)
    target_link_libraries(${entrypoint} PRIVATE libs src)
endforeach()

add_custom_target(
    install_graphviz
    COMMAND apt update
    COMMAND apt install -y graphviz
)