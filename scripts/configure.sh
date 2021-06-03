#!/bin/bash

function help {
	echo "Possible commands:"
	echo "    bootstrap"
	echo "        $0 bootstrap my_project my_namespace \"My Project\" MY_PROJECT"
	echo
	echo "Example: My new project is gonna be called 'The Argos'."
	echo "    >$0 bootstrap argos argos \"The Argos\" ARGOS"
}

function rename {
	newname=$1
	namespace=$2
	spacename=$3
	macroname=$4
	if [[ $newname == "" ]]; then
		echo "Error Required input for unix-name"
		help
		exit 1
	fi
	if [[ $namespace == "" ]]; then
		echo "Error Required input for namespace."
		help
		exit 1
	fi
	if [[ $spacename == "" ]]; then
		echo "Error Required input for space name (with spaces)."
		help
		exit 1
	fi
	if [[ $macroname == "" ]]; then
		echo "Error Required input for macro name."
		help
		exit 1
	fi
	sed -i "s/symbolskel/$newname/g" CMakeLists.txt
	pushd include > /dev/null
		git rm my_project
	popd
	mkdir -p include
	pushd include > /dev/null
		ln -s ../src $newname
		git add $newname
	popd > /dev/null
	sed -i "s/my_project/$newname/g" cli/main.cpp
	sed -i "s/my_offline_project/$namespace/g" cli/main.cpp
	sed -i "s/My Project/$spacename/g" cli/main.cpp
	sed -i "s/my_namespace/$namespace/g" cli/main.cpp
	sed -i "s/my_project/$newname/g" cli/CMakeLists.txt
	sed -i "s/MY_PROJECT/$macroname/g" cli/CMakeLists.txt

	sed -i "s/my_project/$newname/g" src/CMakeLists.txt
	sed -i "s/my_project/$newname/g" src/config.h.in
	sed -i "s/MY_PROJECT/$macroname/g" src/config.h.in
	sed -i "s/my_namespace/$namespace/g" src/MyHmi.h
	sed -i "s/my_namespace/$namespace/g" src/MyHmi.cpp

	pushd cmake/Modules > /dev/null
		git mv FindMY_PROJECT.cmake Find${macroname}.cmake
		sed -i "s/my_project/$newname/g" Find${macroname}.cmake
		sed -i "s/MY_PROJECT/$macroname/g" Find${macroname}.cmake
	popd > /dev/null
}

function bootstrap {
	rename "$@"
	git add -u
	git --no-pager status
	echo "Project has been renamed. You can review and commit the changes."
}

cmd=$1
shift

if [[ $cmd == "bootstrap" ]]; then
	bootstrap "$@"
	exit 0
fi

echo "Invalid command $cmd"
help

exit 1

