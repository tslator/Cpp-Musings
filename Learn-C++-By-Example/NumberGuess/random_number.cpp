#include <random>

#include "random_number.h"

namespace random {
    int some_random_number(int start, int stop, int seed) {
        std::random_device rd;
        std::mt19937 engine(rd());
        std::uniform_int_distribution<int> dist(start, stop);

        return dist(engine);
    }
}