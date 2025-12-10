"""
The purpose of this file is to validate the COBS encode/decoding using the pycob package.
The test vectors defined and test here will be used as truth for the C++ implementation.
"""

from cobs import cobs

from test_vectors import TEST_VECTORS
from utils import print_range

def main():
    """
    Executes each test vector displaying the results
    """

    for test_case, (input, expected) in enumerate(TEST_VECTORS):
        encoded = cobs.encode(input)

        print(f"Test Case {test_case + 1}:")
        print(f"Input: {print_range(input)}")
        print(f"Encoded: {print_range(encoded)}")
        print(f"Expected: {print_range(expected)}")
        print(f"Match: {encoded == bytes(expected)}")
        print()

if __name__ == "__main__":
    main()