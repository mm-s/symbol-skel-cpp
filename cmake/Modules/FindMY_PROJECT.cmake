#Find the native Symbolcore headers and libraries, sourced at https://github.com/you
#
#Usage:
#	FindPackage(MY_PROJECT)
#
#Defines:
#	MY_PROJECT_INCLUDE_DIRS   - where to find
#	MY_PROJECT_LIBRARIES      - List of libraries when using it.
#	MY_PROJECT_FOUND          - True if found.

find_path(MY_PROJECT_INCLUDE_DIR my_project/core.h
	/usr/include
	/usr/local/include
	DOC "Directory containing my_project headers"
)
mark_as_advanced(MY_PROJECT_INCLUDE_DIR)

find_library( MY_PROJECT_LIBRARY
	NAMES my_projectcore
	PATHS /usr/lib
		/usr/local/lib
		/usr/lib/i386-linux-gnu/
		/usr/lib/x86_64-linux-gnu/
)

mark_as_advanced(MY_PROJECT_LIBRARY)

if ( NOT MY_PROJECT_INCLUDE_DIR OR NOT MY_PROJECT_LIBRARY )
	if ( MY_PROJECT_REQUIRED )
		message( FATAL_ERROR "my_project is required." )
	endif ()
else ()
	set( MY_PROJECT_FOUND 1 )
	mark_as_advanced( MY_PROJECT_FOUND )
endif ()

if(MY_PROJECT_FOUND)
	set(MY_PROJECT_LIBRARIES ${MY_PROJECT_LIBRARY})
	set(MY_PROJECT_INCLUDE_DIRS ${MY_PROJECT_INCLUDE_DIR})
endif()

