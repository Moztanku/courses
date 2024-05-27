#!/usr/bin/env python3

import sys

from util import RC4

def same_key(cipa: str, cipb: str) -> bool:
    for i in range(len(cipa)):
        if ord(cipa[i]) ^ ord(cipb[i]) >= 128:
            return False
        
    return True

def test():
    encoded_a: str = RC4("Key", "Plaintext")
    encoded_b: str = RC4("Key", "Attack at dawn")
    encoded_c: str = RC4("Wiki", "pedia")

    if not same_key(encoded_a, encoded_b) or same_key(encoded_a, encoded_c):
        print("Test failed!")
        sys.exit(1)

    print("Test passed!")

def main():
    test()

if __name__ == "__main__":
    main()