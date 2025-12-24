#include "prime_number.h"
#include "random_number.h"

namespace prime {
    constexpr bool is_prime(int number) {
        if (auto const is_2{number == 2}
            ,is_3{number == 3};
            is_2 || is_3) {
            return true;
            }

        if (auto const less_than_equal_1{number <= 1}
            , is_multiple_of_2{number % 2 == 0}
            , is_multiple_of_3{number % 3 == 0};
            less_than_equal_1 || is_multiple_of_2 || is_multiple_of_3) {
            return false;
            }

        for (auto ii = 5; ii * ii <= number; ++ii) {
            if (number % ii == 0) {
                return false;
            }
        }

        return true;
    }

    int some_prime_number() {
        int number{};
        while (!is_prime(number)) {
            number = random::some_random_number(1, 99999);
        }
        return number;
    }

    void check_properties() {
        static_assert(is_prime(2));
    }
}