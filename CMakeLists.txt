# CMakeList.txt : CMake project for GcodeRounder, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project(GcodeRounder VERSION 1.0 LANGUAGES CXX)
get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

########################
# settings
########################

if (IS_SUBPROJECT)
    message(STATUS "GcodeRounder не тестируется в режиме подмодуля")
    set(MYLIB_TESTING OFF)
endif()

option(MYLIB_TESTING "Включить тестирование" ON)

#######################
# compilation options
#######################

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# set source executable for this project & source lib
set (SOURCE_EXE main.cpp)

set (SOURCE_LIB GcodeRounder.cpp)

# add static library
add_library(GcodeGounder STATIC ${SOURCE_LIB})

# add executable
add_executable (main ${SOURCE_EXE})

target_link_libraries(main GcodeGounder)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
