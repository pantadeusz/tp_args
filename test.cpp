#include <iostream>
#include "tp_args.hpp"

int main(int argc, char** argv) {
	using namespace tp::args;
	auto help = arg(argc, argv, "help", false);
	auto x = arg(argc, argv,"x",10.0, "the x value");
	if (help) std::cout << "help screen.." << std::endl;
	std::cout << x << " " << help << std::endl;
	args_info(std::cout);
	return 0;
}
