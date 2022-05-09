#include "tp_args.hpp"
#include <iostream>

int main( int argc, char** argv ) {
    using namespace tp::args;
    auto help = arg( argc, argv, "help", false );
    auto x = arg( argc, argv, "x", 10.0, "the x value" );
    auto some_long_ar = arg( argc, argv, "some_long_ar", 10.0, "experiment with the argument with long name" );
    if ( help ) {
        std::cout << "help screen.." << std::endl;
        args_info( std::cout );
    }
    std::cout << x << " " << help << " " << some_long_ar << std::endl;
    return 0;
}
