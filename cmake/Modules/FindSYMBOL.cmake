# - Find Symbol - https://github.com/nemtech/symbol-sdk-cpp
# Find the native Symbol headers and libraries.
#
#  SYMBOL_INCLUDE_DIRS   - where to find
#  SYMBOL_LIBRARIES      - List of libraries when using it.
#  SYMBOL_FOUND          - True if found.

find_path(SYMBOL_INCLUDE_DIR symbol/rpc.h
  /usr/include
  /usr/local/include
  DOC "Directory containing symbol headers"
)
mark_as_advanced(SYMBOL_INCLUDE_DIR)

FIND_LIBRARY( SYMBOL_LIBRARY
  NAMES symbolrpc
  PATHS /usr/lib
        /usr/local/lib
	/usr/lib/i386-linux-gnu/
	/usr/lib/x86_64-linux-gnu/
)

mark_as_advanced(SYMBOL_LIBRARY)

  if ( NOT SYMBOL_INCLUDE_DIR OR NOT SYMBOL_LIBRARY )
    if ( SYMBOL_REQUIRED )
      message( FATAL_ERROR "symbol is required." )
    endif ()
  else ()
    set( SYMBOL_FOUND 1 )
    mark_as_advanced( SYMBOL_FOUND )
  endif ()


if(SYMBOL_FOUND)
  set(SYMBOL_LIBRARIES ${SYMBOL_LIBRARY})
  set(SYMBOL_INCLUDE_DIRS ${SYMBOL_INCLUDE_DIR})
endif()
