"""
Utility routines for formatting and displaying string and byte data
"""

create_hex_range = lambda start, stop: "".join(f"{b:02x}" for b in range(start, stop))

to_hex_str = lambda input, separator: separator.join(f"{b:02x}" for b in input)

print_range = lambda input: f"{to_hex_str(bytes(input)[0:4], " ")}...{to_hex_str(bytes(input)[-4:], " ")}"
