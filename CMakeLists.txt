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

#------------- Find Symbol-core
find_package (SYMBOLCORE)
if (NOT SYMBOLCORE_FOUND)
        message(FATAL_ERROR "symbol-core required.")
endif()
message("Symbol-Core  headers: ${SYMBOLCORE_INCLUDE_DIRS}")
message("             libs: ${SYMBOLCORE_LIBRARIES}")


#------------- Find Symbol-rpc
find_package (SYMBOLRPC)
if (NOT SYMBOLRPC_FOUND)
        message(FATAL_ERROR "symbol-rpc required.")
endif()
message("Symbol-Rpc  headers: ${SYMBOLRPC_INCLUDE_DIRS}")
message("            libs: ${SYMBOLRPC_LIBRARIES}")




add_subdirectory(src)
add_subdirectory(cli)

install(FILES "${CMAKE_SOURCE_DIR}/cmake/Modules/FindMY_PROJECT.cmake" DESTINATION "share/cmake/MY_PROJECT")
