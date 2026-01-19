#include <format>

#include "random_number.h"
#include "prime_number.h"
#include "guess_prime.h"
#include "input_utils.h"


void run_guess_random() {
    auto too_high_too_low = [](int const number, int const guess) {
        return std::format("Your guess was too {}\n", (guess < number ? "too low" : "too high"));
    };
    input_utils::guess_number_with_clues(random::some_random_number(), too_high_too_low);
}

void run_guess_prime() {
    prime::check_properties();
    guess_prime::check_properties();

    auto check_prime = [](int guess) {
        return std::string((prime::is_prime(guess)) ? "" : "Not prime\n");
    };

    auto check_length = [](int guess) {
        return std::string((guess < 100000) ? "" : "Too long\n");
    };

    int const number = prime::some_prime_number();
    auto check_digits = [number](int guess) {
        return std::format("{}\n",
            guess_prime::check_which_digits_correct(number, guess));
    };

    input_utils::Callables messages {
        check_length,
        check_prime,
        check_digits
    };

    input_utils::guess_number_with_clues(number, messages);
}


int main() {
    // run_guess_random();
    run_guess_prime();
}