cmake_minimum_required(VERSION 3.13)
project(linux_second_assignment)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_library(ZIPLIB zip)

set(SOURCE_FILES main.cpp execution.cpp func.cpp)
file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) 
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

add_executable(main ${SOURCE_FILES} ${SRC_FILES})
target_link_libraries(main PUBLIC utility ${ZIPLIB})
target_include_directories(main PUBLIC  
                           "${CMAKE_CURRENT_SOURCE_DIR}/include/"
                           "${CMAKE_CURRENT_SOURCE_DIR}/My_lib/include/"
                           "/usr/local/include/"
                           )

# Add the necessary flags for debugging with GDB
target_compile_options(main PRIVATE -g)
target_link_options(main PRIVATE -g)

add_library(utility SHARED utility.cpp)
set_target_properties(utility PROPERTIES OUTPUT_NAME "utility")
set_target_properties(utility PROPERTIES VERSION 1.0 SOVERSION 1)

configure_file(flightScanner.sh ${CMAKE_CURRENT_BINARY_DIR}/flightScanner.sh COPYONLY)

