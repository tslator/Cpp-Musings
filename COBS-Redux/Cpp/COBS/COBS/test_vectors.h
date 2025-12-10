#include <vector>
#include <string>

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

std::vector<std::pair<std::string, std::string>> const TEST_VECTORS = {
        {"00", "0101"},
        {"0000", "010101"},
        {"001100", "01021101"},
        {"11220033", "0311220233"},
        {"11223344", "0511223344"},
        {"11000000", "0211010101"},
        {create_hex_range(1, 255), "FF" + create_hex_range(1, 255)},
        {create_hex_range(0, 255), "01FF" + create_hex_range(1, 255)},
        {create_hex_range(1, 256), "FF" + create_hex_range(1, 255) + "02FF"},
        {create_hex_range(2, 256) + "00", "FF" + create_hex_range(2, 256) + "0101"},
        {create_hex_range(3, 256) + "0001", "FE" + create_hex_range(3, 256) + "0201"},
        {"010203000405", "04010203030405" },
        {"00112200", "0103112201" },
        {"1100", "021101"},
        {"00ff0001ff00", "0102ff0301ff01"},
        {"11220000334400", "0311220103334401"}

};