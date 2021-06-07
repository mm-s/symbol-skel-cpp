![Symbol-cpp](./doc/symbolcpp.png)

# Symbol-skel-cpp
Template Repository
TL; DR: Fork this repository to start a new C++ project based on the symbol-sdk-cpp libraries.

## Why Symbol-sdk-cpp

This project is meant to provide a foundation for C++ application development on the Symbol blockchain.

Depends on nemtech/[catapult_server](https://github.com/nemtech/catapult-server "GitHub link"), providing core algorithms.

## Instructions:

### Fork this repository. Customize it.
```sh
git clone https://github.com/nemtech/symbol-skel-cpp
cd <your_project>
scripts/configure.sh <customization_details(enter nothing for help)>
```
Customizable items are:
* The Project Name: 
  variants:
  * Unix. project_name (Used for directories, namespace)
  * Space. "Project Name" (Used for UI) 
  * Upper. PROJECT_NAME (Used for CMake variables)	
	

### Dependencies:
* nemtech/[symbol-sdk-core-cpp](https://github.com/nemtech/symbol-sdk-core-cpp "GitHub link")  -  Symbol algorithms.
* nemtech/[symbol-sdk-cpp](https://github.com/nemtech/symbol-sdk-cpp "GitHub link")  -  REST-API Symbol functions.

### Build:
Once configured proceed to build the project.

```sh
mkdir _build; cd _build
cmake  ..
make
```
You can pass options to cmake to specify alternative locations of the symbol-sdk-core and symbol-sdk libraries using
```
cmake -DSYMBOLCORE_ROOT=<path_to_symbol_sdk_core_cpp> -DSYMBOLRPC_ROOT=<path_to_symbol_sdk_cpp> ..
```
Paths shall point to a directory containing standard directories bin, lib and include.

## Install:
In order to install the library and cliente application in the system type:
```sh
sudo make install
```

CMake accepts the useful definition for specifying the install target location.
```sh
cmake -DCMAKE_INSTALL_PREFIX=<target_directory> ..
```

## Project Governance:
Ships: 
* branch main: 
  * Release Manager TBD

* branch dev:
  * developer marcos.mayorga@nem.software
  * [apply^]



