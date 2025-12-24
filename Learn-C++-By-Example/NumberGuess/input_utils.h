#pragma once
#include <optional>
#include <iostream>
#include <functional>

namespace input_utils {
    using Callable = std::function<std::string(int, int)>;
    using Callables = std::vector<std::function<std::string(int)>>;

    unsigned input();
    std::optional<int> read_number(std::istream& in);

    int some_const_number();

    void guess_number_with_clues(int number, Callable const& message);
    void guess_number_with_clues(int number, Callables const& message);
}