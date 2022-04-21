# tp_args
Header only argument parsing library for c++17 with automatic type and type conversions


## Example usage

```bash
wget https://raw.githubusercontent.com/pantadeusz/tp_args/87d75f26493cb06ae5688ba5206e0d618a808367/tp_args.hpp
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
