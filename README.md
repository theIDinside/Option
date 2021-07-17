## My Rust Option in C++

I have no idea why this is not built into the C++ std::optional so this is just a wrapper around that,
that provides some of the ergonomic functions that Rust provides, because writing code using this style
is *fun* it's easy to read and understand. Now, this isn't optimized, and I don't know all the intricacies
of the language right now to actually make it better/good. But it shouldn't be that expensive as a wrapper.

### Usage

Clone into your project and add it to your project like you usually do (like add_subdirectories or whatever is preferred.
Right now it's not using any of the best practicies, not in the C++ code, nor or in the CMake build script code).

Include the header and go.

```bash
    git clone ...
```

```cpp
#include <iostream>
#include <string>
#include "option.hpp"

struct MyType {
    std::string name;
    int j;
    float x;
    const char* heap_data;
};

using namespace std::literals::string_literals;


int main(int argc, const char** argv) {

    std::optional<int> iOpt{1};
    Option<std::string> i{"hello world"s};
    std::string foo = "foooooooo";

    Option o1 = optutil::make_option(MyType { .name = "foobar",  .j = 1, .x = 0.3, .heap_data = "baz boom"});
    Option o2 = optutil::make_option(1);
    Option o3 = optutil::take_option(std::move(iOpt));
    auto SomeVal = 42;

    auto result = o1.map([&](auto& s) {
        std::cout << "processing MyType value: " << s.name << std::endl;
        return 10 + SomeVal; // returning an integer to next map(), so return value is Option<int> here
    }).map([](auto j) {
        std::cout << "processing int value: " << j << std::endl;
        return 10.1f; // return value Option<float>
    }).value_or(41.9999999);

    std::cout << "value of result: " << result << std::endl;
}
```



#### Current limitations
The Option type can not wrap std::optionals of std::optional<SomePointerType>. Shouldn't be too much work to make it working decently.