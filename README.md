# tp_args
Header only argument parsing library for c++17 with automatic type and type conversions


## Example usage

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
