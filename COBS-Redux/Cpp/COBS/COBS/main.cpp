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
#include "test_vectors.h"


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
    std::vector<uint8_t> encoded_data;
	encoded_data.reserve(input.size() + input.size() / 254 + 1);

	encoded_data.emplace_back(0_u8);
    std::size_t code_index = 0;
	auto code = 1_u8;

    for (std::size_t ii = 0; ii < input.size(); ++ii) {
        auto value = input[ii];

        if (value != 0_u8) {
            encoded_data.emplace_back(value);
			code += 1_u8;

            // Check if block is full
            if (code == 255_u8) {
                encoded_data[code_index] = 255_u8;

                if (ii + 1 < input.size()) {
                    code_index = encoded_data.size();
                    encoded_data.emplace_back(0_u8);
                    code = 1_u8;
                }
            }
        }
        else {
            // zero encountered: finish block
			encoded_data[code_index] = code;
            code_index = encoded_data.size();
			encoded_data.emplace_back(0_u8);
			code = 1_u8;
        }
    }

	encoded_data[code_index] = code;

    return encoded_data;
}

std::vector<uint8_t> decode(std::vector<uint8_t> encoded_data)
{
    std::vector<uint8_t> decoded_data;
	decoded_data.reserve(encoded_data.size());
    std::size_t index{ 0 };

    while (index < encoded_data.size()) {

        auto code = encoded_data[index];
		index += 1;

        for (size_t n = 1; n < code; ++n) {
            if (index >= encoded_data.size()) {
                return {};
            }
            decoded_data.emplace_back(encoded_data[index]);
			index += 1;
		}

        if (code < 255_u8 && index < encoded_data.size()) {
            decoded_data.emplace_back(0_u8);
        }
    }

    return decoded_data;
}



int main()
{
    for (const auto& [input_hex, packet_hex] : TEST_VECTORS) {
        auto input = hex_to_bytes(input_hex);
        auto expected_packet = hex_to_bytes(packet_hex);

        auto encoded = encode(input);
        auto decoded = decode(expected_packet);

        bool encode_ok = (encoded == expected_packet);
        bool decode_ok = (decoded == input);

        std::cout << "Test: input=" << input_hex << "\n";
        std::cout << "Expected packet: " << packet_hex << "\n";
        std::cout << "Encoded packet : " << bytes_to_hex(encoded) << "\n";
        std::cout << "Decoded input  : " << bytes_to_hex(decoded) << "\n";
        std::cout << std::boolalpha;
        std::cout << "Encode match: " << encode_ok << "\n";
        std::cout << "Decode match: " << decode_ok << "\n\n";
    }
}
