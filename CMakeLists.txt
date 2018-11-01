# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.0)

# Project's name
project(linux_cp_command)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
#set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)

# The following folder will be included
include_directories("${INCLUDE_PATH}")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

#set(LIBRARIES -pthread -lboost_system)

add_executable(copy_normal ${PROJECT_SOURCE_DIR}/src/copy.c)
target_link_libraries(copy_normal ${LIBRARIES} ${ADDITIONAL_LIBRARIES})

add_executable(copy_sg ${PROJECT_SOURCE_DIR}/src/scaterGatherIO.c)
target_link_libraries(copy_sg ${LIBRARIES} ${ADDITIONAL_LIBRARIES})

SET(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -Wall -Wextra -D_GLIBCXX_USE_CXX11_ABI=0 -march -mtune")
