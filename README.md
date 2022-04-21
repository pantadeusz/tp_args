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

int main(int argc, char **argv) {
    using namespace std;
    using namespace tp::args;
    auto arguments = parse_arguments(argc, argv, {{"height","int"}});
    auto height = arg(arguments, "height",0);

    std::cout <<"height " << height << std::endl;
}
```
And you can execute compiled program with:

```bash
./a.out height=1234
```
