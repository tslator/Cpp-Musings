#include <limits>
#include <format>

#include "input_utils.h"

namespace input_utils {
    int some_const_number() {
        return 42;
    }

    unsigned input() {
        unsigned number;
        while (!(std::cin >> number)) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter a number.\n";
        }

        return number;
    }

    std::optional<int> read_number(std::istream& in) {
        if (int result{}; in >> result) {
            return result;
        }
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return {};
    }

    void guess_number_with_clues(int number, Callable const& message) {
        std::cout << "Guess the number.\n";
        std::optional<int> guess;
        while ((guess = read_number(std::cin))) {
            if (guess.value() == number) {
                std::cout << "Well done.";
                return;
            }
            std::cout << message(number, guess.value());
            std::cout << '>';
        }
        std::cout << "The number was " << number << "\n";
    }

    void guess_number_with_clues(int number, Callables const& messages) {
        std::cout << "Guess the number.\n";
        std::optional<int> guess;
        while ((guess = read_number(std::cin))) {
            if (guess.value() == number) {
                std::cout << "Well done.";
                return;
            }

            std::cout << std::format("{:0>5} is wrong. Try again\n", guess.value());
            for (auto message : messages) {
                auto clue = message(guess.value());
                if (!clue.empty()) {
                    std::cout << clue;
                    break;
                }
            }
        }
        std::cout << std::format("The number was {}\n", (number));
    }
}