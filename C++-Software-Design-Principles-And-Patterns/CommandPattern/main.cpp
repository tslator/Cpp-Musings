#include <cstdlib>
#include <format>
#include <memory>
#include <iostream>
#include "Add.h"
#include "Calculator.h"
#include "Subtract.h"


namespace initial_calculator {
    void run_calculator() {
        Calculator calculator{};

        auto op1 = std::make_unique<Add>(3);
        auto op2 = std::make_unique<Add>(7);
        auto op3 = std::make_unique<Subtract>(4);
        auto op4 = std::make_unique<Subtract>(2);

        calculator.compute(std::move(op1));
        calculator.compute(std::move(op2));
        calculator.compute(std::move(op3));
        calculator.compute(std::move(op4));

        calculator.undoLast();
        int const res = calculator.result();
        std::cout << std::format("Result: {}\n", res);
    }
}


int main() {
    initial_calculator::run_calculator();

    return EXIT_SUCCESS;
}