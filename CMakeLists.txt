cmake_minimum_required(VERSION 3.14)
#----------------------------------
#Main tweaking section

set(PRJNAME my_project)
set(PRJVERSION 1.0)
#----------------------------------
project(${PRJNAME} VERSION ${PRJVERSION})
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(src)
add_subdirectory(cli)

install(FILES "${CMAKE_SOURCE_DIR}/cmake/Modules/FindMY_PROJECT.cmake" DESTINATION "share/cmake/MY_PROJECT")
