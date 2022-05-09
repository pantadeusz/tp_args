# tp_args
Header only argument parsing library for c++17 with automatic type and type conversions


## Example usage

```bash
wget https://raw.githubusercontent.com/pantadeusz/tp_args/33c158a8a890e05fbd53a73d90f4664be0e726bb/tp_args.hpp
```

Code sample:

```c++
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
```

And you can execute compiled program with:

```bash
./a.out -x 99 -help
./a.out -x 99
```
