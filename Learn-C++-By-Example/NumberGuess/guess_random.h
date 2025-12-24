#pragma once
#include <functional>
#include <string>

using Callable = std::function<std::string(int, int)>;

int some_const_number();
void guess_number_with_clues(int number, Callable const& message);