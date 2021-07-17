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