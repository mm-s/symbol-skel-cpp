add_executable(my_project main.cpp)

target_include_directories(my_project
	INTERFACE
	# Headers used from source/build location:
	"$<BUILD_INTERFACE:${MY_PROJECT_SOURCE_DIR}/include>"
	# Headers used from installed location:
	"$<INSTALL_INTERFACE:include>"
)

target_link_libraries(my_project PUBLIC my_projectcore)

install(TARGETS my_project DESTINATION bin)

