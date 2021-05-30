configure_file(config.h.in config.h)

file(GLOB ${PRJNAME}_SRC *.cpp)

#------------- Find SymbolCore


#------------- libPRJNAME.so
add_library(${PRJNAME} SHARED ${PRJNAME}_SRC})

#-------------Use OpenSSL, Boost
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PRJNAME} ${SYMBOLCORE-LIBRARIES})

set_property(TARGET ${PRJNAME} PROPERTY POSITION_INDEPENDENT_CODE ON)


target_include_directories(${PRJNAME}
  INTERFACE
    # Headers used from source/build location:
    "${PROJECT_BINARY_DIR}/src"
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
    # Headers used from installed location:
    "$<INSTALL_INTERFACE:include>"
)
install(TARGETS ${PRJNAME} DESTINATION lib)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/src/" # source directory
        DESTINATION "include/symbol/core" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.h" # select header files
)
