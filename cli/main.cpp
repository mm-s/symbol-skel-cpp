#include <my_project/Hmi.h>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
	using namespace std;
	using Cli = my_namespace::Hmi;

    ostringstream os;
    for (int i=1; i< argc; ++i) {
        os << argv[i] << ' ';
    }
    string cmdline=os.str();

    Cli::Section::init(cout, cerr, "0.0.1");
    Cli cli;
    cli.init(argv[0], "My Project - offline.");
    return cli.exec(cmdline)?0:1;
}

