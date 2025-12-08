# Motivation
Having previously worked with COBS encoding, I would like to implement the algorithm using a new version of C++, using newer features.

Reference: (https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing)[Consistent Overhead Byte Stuffing]

**TODO:**
**- Address COBS vs COBS/R**

# Approach
There is a Python package that contains an implementation of COBS.  I have written a series of test cases to validate the functionality.  From this, I will create a comparable C++ implementation and will have substantiated test cases to confirm the functionality.

# Python
To minimize the complexity of the Python environment, 'uv' is used for installation and package management.  'uv' allows dependency strings to be embedded into the Python script, eliminating the need for a virtual environment and project setup.

The file, cobs_validation.py, provides test vectors and verified output for the COBS implementation provided by the cobs package.

# C++
With validated data in hand, we want to implement the same COBS algorithm using C++, and more specifically, modern C++.  I expect to use templates, ranges, and possibly views in this implementation.  As a preview, there are some of the C++ features that I think will apply to COBS:

- Split on 0: the result of COBS encoding is that a 0 is the separator between messages.  Instead of needing to know the length of a message, the code only needs to test for a 0 to find the end of the message.  If multiple messages are received, splitting on 0 will return all of the messages.  Anything left in the buffer after split is an incomplete message and remains in the buffer.

# Algoithm Description

1. Create an empty packet
2. Place a 0 in offset 0 of the packet
3. Copy the input into the packet starting with offset 1
4. Place a 0 at offset packet.size() + 1
5. Replace each 0 (except last 0) with the offset from the current 0 to the next 0



Input           Packet
11 22 00 33     00
                00 11 22 00 33
                00 11 22 00 33 00
                03 11 22 02 33 00

00              00
                00 00
                00 00 00
                01 01 00

00 00           00
                00 00 00
                00 00 00 00
                01 01 01 00

00 11 00        00
                00 00 11 00
                00 00 11 00 00
                01 02 11 01 00

11 22 00 33     00
                00 11 22 00 33
                00 11 22 00 33 00
                03 11 22 02 33 00

11 22 33 44     00
                00 11 22 33 44
                00 11 22 33 44 00
                05 11 22 33 44 00

11 00 00 00     00
                00 11 00 00 00
                00 11 00 00 00 00
                02 11 01 01 01 00