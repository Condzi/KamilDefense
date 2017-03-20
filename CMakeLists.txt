cmake_minimum_required(VERSION 3.0)

project(KamilDefense)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

find_package(SFML 2.4 COMPONENTS graphics audio window system network)

file(GLOB SOURCE "source/*.hpp" "source/*.cpp" "external/framework/*.hpp" "external/framework/*.cpp") 

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${SFML_INCLUDE_DIR} "external/framework")
add_executable(KamilDefense ${SOURCE})
target_link_libraries(KamilDefense ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
