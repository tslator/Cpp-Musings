#include <iostream>
#include <format>

#include "triangle.h"
#include "types.h"

Row get_next_row(const Row& last_row) {
    Row next_row{1};
    if (last_row.empty()) {
        return next_row;
    }

    for (auto index = 0; index + 1 < last_row.size(); ++index) {
        next_row.emplace_back(last_row[index] + last_row[index + 1]);
    }

    next_row.emplace_back(1);

    return next_row;
}

Triangle generate_triangle(const int rows) {
    Triangle triangle{{1}};

    for (int row = 0; row < rows; ++row) {
        triangle.push_back(get_next_row(triangle.back()));
    }
    return triangle;
}

void show_triangle(
    std::ostream& stream,
    const Triangle& triangle) {

    const auto final_row_size = triangle.back().size();
    auto spaces = std::string(final_row_size * 3, ' ');
    for (const auto& row: triangle) {
        stream << spaces;
        if (spaces.size() > 3) {
            spaces.resize(spaces.size() - 3);
        }

        for (const auto& value : row) {
            stream << std::format("{: ^{}}", value, 6);
        }

        stream << '\n';
    }
}