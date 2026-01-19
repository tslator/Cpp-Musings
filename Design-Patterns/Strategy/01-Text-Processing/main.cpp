#include <string>
#include <functional>
#include <range/v3/all.hpp>
#include <fmt/core.h>

#include "strategy.h"

std::string process_text(const std::string& text, const Strategy& strategy) {
    return strategy(text);
}

auto show = [](std::string before_text, std::string after_text) {
    fmt::print("Text (before): {}, Text (after): {}\n", before_text, after_text);
};

int main() {
    const std::string test_text{"This is the text."};

    auto strategy = make_uppercase_strategy();
    auto result = process_text(test_text, strategy);
    show(test_text, result);

    strategy = make_lowercase_strategy();
    result = process_text(test_text, strategy);
    show(test_text, result);

    strategy = make_titlecase_strategy_20();
    result = process_text(test_text, strategy);
    show(test_text, result);

    strategy = make_titlecase_strategy_range_v3();
    result = process_text(test_text, strategy);
    show(test_text, result);

    return 0;
}