// COBS.cpp : Defines the entry point for the application.
//

#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <ranges>
#include <iterator>
#include <array>

using namespace std;


constexpr uint8_t operator"" _u8(unsigned long long v) {
    return static_cast<uint8_t>(v);
}

// Convert hex string to vector<uint8_t>
std::vector<uint8_t> hex_to_bytes(const std::string& hex) {
    std::vector<uint8_t> bytes;
    for (std::size_t i = 0; i + 1 < hex.size(); i += 2) {
        uint8_t byte = static_cast<uint8_t>(std::stoi(hex.substr(i, 2), nullptr, 16));
        bytes.push_back(byte);
    }
    return bytes;
}

// Convert vector<uint8_t> to hex string
std::string bytes_to_hex(const std::vector<uint8_t>& bytes) {
    std::ostringstream oss;
    for (uint8_t b : bytes) {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b);
    }
    return oss.str();
}

std::vector<uint8_t> encode(std::vector<uint8_t> const& input)
{
    std::size_t capacity = input.size() + input.size() / 254 + 2;
    std::vector<uint8_t> packet;
    packet.reserve(capacity);

    // Step 1: emplace leading zero
    packet.emplace_back(0_u8);

    // Step 2: copy input into packet
    std::copy(input.begin(), input.end(), std::back_inserter(packet));

    // Step 3: emplace trailing zero
    packet.emplace_back(0_u8);

    // Step 4: patch each zero with offset to next zero
    auto it = packet.begin();
    while (it != packet.end()) {
        auto next = std::find_if(
            std::next(it),
            packet.end(),
            [](uint8_t x) { return x == 0_u8; });
        if (next == packet.end()) {
            break; // trailing zero remains unchanged
        }

        *it = static_cast<uint8_t>(std::distance(it, next));
        it = next;
    }

    return packet;
}

std::vector<uint8_t> decode(std::vector<uint8_t> packet)
{
    std::vector<uint8_t> output;

    // Given:
    //  01 01 00
    // Produce:
    //  00

    auto it = packet.begin();
    while (it != packet.end()) {
        uint8_t offset = *it;
        auto next = std::ranges::next(it, offset, packet.end());

        if (next == packet.end()) {
            break; // reached trailing zero
		}

        // Copy the range between markers
        auto slice = std::ranges::subrange(std::next(it), next);
        std::ranges::copy(slice, std::back_inserter(output));

        it = next;
    }

    return output;
}


void run_test(const std::string& input_hex, const std::string& expected_packet_hex) {

    auto input = hex_to_bytes(input_hex);
    auto expected_packet = hex_to_bytes(expected_packet_hex);

    auto encoded = encode(input);
    auto decoded = decode(expected_packet);

    bool encode_ok = (encoded == expected_packet);
    bool decode_ok = (decoded == input);

    std::cout << "Test: input=" << input_hex << "\n";
    std::cout << "Expected packet: " << expected_packet_hex << "\n";
    std::cout << "Encoded packet : " << bytes_to_hex(encoded) << "\n";
    std::cout << "Decoded input  : " << bytes_to_hex(decoded) << "\n";
    std::cout << "Encode match: " << (encode_ok ? "✅" : "❌") << "\n";
    std::cout << "Decode match: " << (decode_ok ? "✅" : "❌") << "\n\n";
}

int main()
{
    std::vector<std::pair<std::string, std::string>> tests = {
            {"00", "0101"},
            //{"0000", "01010100"},
            //{"001100", "0102110100"},
            //{"11220033", "031122023300"},
            //{"11223344", "051122334400"},
            //{"11000000", "021101010100"},
            // Add more test cases here...
    };

    for (const auto& [input_hex, packet_hex] : tests) {
        run_test(input_hex, packet_hex);
    }
}
