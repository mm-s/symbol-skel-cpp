#!/bin/bash

function help {
	echo "Possible commands:"
	echo "    bootstrap"
	echo "        $0 bootstrap my_project my_namespace \"My Project\" MY_PROJECT"
	echo
	echo "Example: My new project is gonna be called 'The Argos'."
	echo "    >$0 bootstrap argos argos \"The Argos\" ARGOS"
}

function dofile {
	newname=$1
	namespace=$2
	spacename=$3
	macroname=$4
	f=$5
	sed -i "s/MY_PROJECT/$macroname/g" $f
	sed -i "s/my_project/$newname/g" $f
	sed -i "s/my_offline_project/$namespace/g" $f
	sed -i "s/My Project/$spacename/g" $f
	sed -i "s/my_namespace/$namespace/g" $f
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

	#Token substitution
	files=CMakeLists.txt cli/main.cpp cli/CMakeLists.txt src/CMakeLists.txt src/config.h.in src/MyHmi.h cmake/Modules/FindMY_PROJECT.cmake
	for f in $files; do
		dofile "$@" $f
	done

	#Include dir
	pushd include > /dev/null
		git rm my_project
	popd
	mkdir -p include
	pushd include > /dev/null
		ln -s ../src $newname
		git add $newname
	popd > /dev/null

	#CMake module
	pushd cmake/Modules > /dev/null
		git mv FindMY_PROJECT.cmake Find${macroname}.cmake
	popd > /dev/null

cat << EOF > README.md
# $spacename

## build:
        mkdir _build; cd _build
        cmake  ..
        make

## install:
        make install

EOF
	git rm scripts/configure.sh
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

