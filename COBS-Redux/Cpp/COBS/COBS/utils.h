#pragma once

auto create_hex_range = [](int start, int stop) {
    std::string out;
    out.reserve((stop - start) * 2);   // avoid reallocations

    for (int b = start; b < stop; ++b) {
        char buf[3];
        std::snprintf(buf, sizeof(buf), "%02x", static_cast<unsigned>(b) & 0xFF);
        out.append(buf);
    }

    return out;
    };


auto to_hex_str = [](const std::vector<uint8_t>& bytes, std::string separator = " ") {
    std::ostringstream oss;
    for (uint8_t b : bytes) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b) << separator;
    }
    return oss.str();
	};


auto print_range = [](const auto& range) {
    // Print elements of a range printing the first 2 elements, then "...", then the last 2 elements.  If a range has 4 or fewer print the entire range.
	// leverage to_hex_str to convert elements to hex strings.
    std::ostringstream oss;
    auto size = std::ranges::distance(range);
    if (size <= 4) {
        for (const auto& elem : range) {
            oss << to_hex_str({static_cast<uint8_t>(elem)});
        }
    }
    else {
        auto it = range.begin();
        for (int i = 0; i < 2; ++i, ++it) {
            oss << to_hex_str({static_cast<uint8_t>(*it)});
        }
        oss << "...";
        it = range.end();
        std::advance(it, -2);
        for (; it != range.end(); ++it) {
            oss << to_hex_str({static_cast<uint8_t>(*it)});
        }
    }
	return oss.str();
	};