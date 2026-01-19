#include <string>
#include <range/v3/all.hpp>
#include <ranges>

#include "strategy.h"

Strategy make_uppercase_strategy() {
    return [](std::string text) {
        std::ranges::transform(
            text.begin(),
            text.end(),
            text.begin(),
            [](unsigned char c) {
                return std::toupper(c);
            } );
        return text;
    };
}

Strategy make_lowercase_strategy() {
    return [](std::string text) {
        std::ranges::transform(
            text.begin(),
            text.end(),
            text.begin(),
            [](unsigned char character) {
                return std::tolower(character);
            }
        );
        return text;
    };
}

template <typename R>
auto to_vector_of_strings(R&& r) {
    std::vector<std::string> out;
    for (auto&& sub : r) {
        out.emplace_back(sub.begin(), sub.end());
    }
    return out;
}

Strategy make_titlecase_strategy_20() {
    return [](std::string text) {
        // Necessary for C++20, but not in C++23 which will have 'to'
        // ranges_v3 has an appropriate 'to'
        // std::vector<std::string> words;
        // for (auto&& subrange : text | std::ranges::views::split(' ')) {
        //     words.emplace_back(subrange.begin(), subrange.end());
        // }
        // Alternative:
        auto words = to_vector_of_strings(text | std::views::split(' '));
        // Change the first letter of each word to uppercase
        std::ranges::transform(words, words.begin(), [](std::string word) {
            if (!word.empty()) {
                word[0] = std::toupper(static_cast<unsigned char>(word[0]));
            }
            return word;
        });

        std::string result;
        for (size_t ii = 0; ii < words.size(); ++ii) {
            if (ii > 0) {
                result += ' ';
            }
            result += words[ii];
        }
        return result;
    };
}

Strategy make_titlecase_strategy_range_v3() {
    return [](std::string text) {
        auto title_word = [](std::string word) {
            if (!word.empty()) {
                word[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(word[0])));
            }
            return word;
        };

        auto to_string_vector = [](auto&& subrange) {
            return subrange | ranges::to<std::string>;
        };

        auto result = text
            | ranges::views::split(' ')
            | ranges::views::transform(to_string_vector)
            | ranges::views::transform(title_word)
            | ranges::views::intersperse(std::string{" "})
            | ranges::views::join
            | ranges::to<std::string>;

        return result;
    };
}