#include "interpretator.h"

int main(int argc, char *argv[]) {
   boost::program_options::options_description desc("All options");
	desc.add_options()
		("file,f",  boost::program_options::value<std::string>(), "load to file with program")
		("help", "produce help message");
	 boost::program_options::variables_map vm;
     boost::program_options::store( boost::program_options::parse_command_line(argc, argv, desc), vm);
	 boost::program_options::notify(vm);
	if (vm.count("help")) {
		std::cout << desc << "\n";
		return 1;
	}
	interpretator inter;
	inter.Run(vm["file"].as<std::string>());
	return 0;
	
}