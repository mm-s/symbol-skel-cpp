#!/bin/bash
# marc/os - NEM Software

branch=$1

function help {
	cat << EOF
This rep include copies of docs sourced elsewhere.
Usage:
	$0 <branch>
EOF
}

if [[ "_${branch}" == "_" ]]; then
	help
	exit 1
fi

prj="symbol-sdk-cpp"
gitUrl="https://github.com/nemtech/${prj}.git"
if [[ "_$branch" == "_" ]]; then
	branch="dev"
fi

echo "Obtaining the ${file} from branch ${branch} in ${gitUrl}"
rm -rf ${prj}
git clone -b ${branch} ${gitUrl}

file="FindSYMBOLCORE.cmake"
cp ${prj}/cmake/Modules/$file cmake/Modules/
file="FindSYMBOLRPC.cmake"
cp ${prj}/cmake/Modules/$file cmake/Modules/
file="FindRESTCCPP.cmake"
cp ${prj}/cmake/Modules/$file cmake/Modules/

# staging
git add cmake/Modules/FindSYMBOLCORE.cmake
git add cmake/Modules/FindSYMBOLRPC.cmake
git add cmake/Modules/FindRESTCCPP.cmake
git commit -m "build: Automated syncing files published elsewhere

cmakemodules Find*.cmake"

