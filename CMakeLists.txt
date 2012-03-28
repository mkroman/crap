project(crap)
cmake_minimum_required(VERSION 2.6)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

include_directories(headers)

set(crap_sources
	sources/crap.c
)

find_package(Giblib)

add_executable(crap ${crap_sources})
target_link_libraries(crap ${GIBLIB_LIBRARY})
