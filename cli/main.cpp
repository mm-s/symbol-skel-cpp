#include <my_project/MyHmi.h>
#include <iostream>
#include <sstream>
#include <string>

int main_offline(int argc, char** argv) {
	using namespace std;
	using Cli = my_namespace::MyHmiOffline;

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

int main_online(int argc, char** argv) {
	using namespace std;
	using Cli = my_namespace::MyHmiOnline;

	ostringstream os;
	for (int i=1; i< argc; ++i) {
		os << argv[i] << ' ';
	}
	string cmdline=os.str();

	Cli::Section::init(cout, cerr, "0.0.1");
	Cli cli;
	cli.init(argv[0], "My Project - online.");
	return cli.exec(cmdline)?0:1;
}

int main(int argc, char** argv) {
	/*
		using namespace std;
		char n=' ';
		cout << " 0  - The Argos offline\n";
		cout << " 1  - The Argos online\n";
		cout << "Select HMI Instance [0|1]> "; cout.flush();
		cin >> n;
		if (n=='0') return main_offline(argc, argv);
		*/
	return main_online(argc, argv);
}


