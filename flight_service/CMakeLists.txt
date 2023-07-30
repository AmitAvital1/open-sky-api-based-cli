cmake_minimum_required(VERSION 3.13)
project(linux_second_assignment)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp func.cpp)
file(GLOB SRC_FILES CONFIGURE_DEPENDS "src/*.cpp")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) 
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

add_executable(main ${SOURCE_FILES} ${SRC_FILES})
          
# Add the necessary flags for debugging with GDB
target_compile_options(main PRIVATE -g)
target_link_options(main PRIVATE -g)

