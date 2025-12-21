#pragma once

#include "types.h"


Triangle generate_triangle(int rows);
void show_triangle(
    std::ostream& stream,
    const Triangle& triangle);