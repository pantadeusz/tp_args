# tp_args
Header only argument parsing library for c++17 with automatic type and type conversions


## Example usage

```bash
wget https://raw.githubusercontent.com/pantadeusz/tp_args/646b0c692bf1d56cbe6b42397954732d19a35e9d/tp_args.hpp
```

Code sample:

```c++
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

```
And you can execute compiled program with:

```bash
./a.out -x 99 -help
```
