#include <format>
#include <cassert>

#include "guess_prime.h"
#include "input_utils.h"

namespace guess_prime {
    std::string check_which_digits_correct(int number, int guess) {
        auto number_format = std::format("{:0>5}", (number));
        auto guess_format = std::format("{:0>5}", (guess));
        std::string matches(5, '.');

        for (size_t ii = 0, stop = guess_format.length(); ii < stop; ++ii) {
            char guess_char = guess_format[ii];
            if (ii < number_format.length() && guess_char == number_format[ii]) {
                matches[ii] = '*';
                number_format[ii] = '*';
            }
        }

        for (size_t ii = 0, stop = guess_format.length(); ii < stop; ++ii) {
            char guess_char = guess_format[ii];
            if (ii < number_format.length() && matches[ii] != '*') {
                if (size_t index = number_format.find(guess_char, 0); index != std::string::npos) {
                    matches[ii] = '^';
                    number_format[index] = '^';
                }
            }
        }
        return matches;
    }



    void check_properties() {
        assert(check_which_digits_correct(12347, 23471) == "^^^^^");
        assert(check_which_digits_correct(17231, 1723) == ".^^^^");
    }
}