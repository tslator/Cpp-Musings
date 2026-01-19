#pragma once
#include <functional>
#include <string>

using Strategy = std::function<std::string(std::string)>;

Strategy make_uppercase_strategy();
Strategy make_lowercase_strategy();
Strategy make_titlecase_strategy_20();
Strategy make_titlecase_strategy_range_v3();
