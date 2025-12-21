#include <iostream>
#include "triangle.h"

// TODO Implement a constexpr version of triangle

auto main() -> int {
    const Triangle triangle = generate_triangle(16);
    show_triangle(std::cout, triangle);
}