configure_file(config.h.in config.h)

file(GLOB ${PRJNAME}_SRC *.cpp)

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


#------------- libPRJNAME.so
add_library(${PRJNAME}core SHARED ${${PRJNAME}_SRC})

include_directories(${SYMBOLCORE_INCLUDE_DIRS})
target_link_libraries (${PRJNAME}core ${SYMBOLCORE_LIBRARIES})

include_directories(${SYMBOL_INCLUDE_DIRS})
target_link_libraries (${PRJNAME}core ${SYMBOLRPC_LIBRARIES})

set_property(TARGET ${PRJNAME}core PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(${PRJNAME}core
  INTERFACE
    # Headers used from source/build location:
    "${PROJECT_BINARY_DIR}/src"
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    # Headers used from installed location:
    "$<INSTALL_INTERFACE:include>"
)
install(TARGETS ${PRJNAME}core DESTINATION lib)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/" # source directory
        DESTINATION "include/my_project" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
)
