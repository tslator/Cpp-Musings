"""
Defines test vectors for COBS encode/decode
"""

from utils import create_hex_range

TEST_VECTORS = [
    (bytearray.fromhex("00"), bytearray.fromhex("0101")),
    (bytearray.fromhex("0000"), bytearray.fromhex("010101")),
    (bytearray.fromhex("001100"), bytearray.fromhex("01021101")),
    (bytearray.fromhex("11220033"), bytearray.fromhex("0311220233")),
    (bytearray.fromhex("11223344"), bytearray.fromhex("0511223344")),
    (bytearray.fromhex("11000000"), bytearray.fromhex("0211010101")),

    (bytearray.fromhex(create_hex_range(1, 255)), bytearray.fromhex(f"FF{create_hex_range(1, 255)}")),
    (bytearray.fromhex(create_hex_range(0, 255)), bytearray.fromhex(f"01FF{create_hex_range(1, 255)}")),
    (bytearray.fromhex(create_hex_range(1, 256)), bytearray.fromhex(f"FF{create_hex_range(1, 255)}02FF")),
    (bytearray.fromhex(f"{create_hex_range(2, 256)}00"), bytearray.fromhex(f"FF{create_hex_range(2, 256)}0101")),
    (bytearray.fromhex(f"{create_hex_range(3, 256)}0001"), bytearray.fromhex(f"FE{create_hex_range(3, 256)}0201")),

    (bytearray.fromhex("010203000405"), bytearray.fromhex("04010203030405")),
    (bytearray.fromhex("00112200"), bytearray.fromhex("0103112201")),
    (bytearray.fromhex("1100"), bytearray.fromhex("021101")),
    (bytearray.fromhex("00ff0001ff00"), bytearray.fromhex("0102ff0301ff01")),
    (bytearray.fromhex("11220000334400"), bytearray.fromhex("0311220103334401"))
]