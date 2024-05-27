#!/usr/bin/env python3

import sys
from util import RC4, to_hex

def test(key: str, plain: str, expected: str):
    encoded: str = RC4(key, plain)
    decoded: str = RC4(key, encoded)

    if expected != to_hex(encoded) or plain != decoded:
        print("Test failed!")
        sys.exit(1)

    print(f"Expected: {expected},", end=" ")
    print(f"Encoded: {to_hex(encoded)}")

    print(f"Expected: {plain},", end=" ")
    print(f"Decoded: {decoded}")

    print()

def main():
    test("Key", "Plaintext", "BBF316E8D940AF0AD3")
    test("Wiki", "pedia", "1021BF0420")
    test("Secret", "Attack at dawn", "45A01F645FC35B383552544B9BF5")

if __name__ == "__main__":
    main()