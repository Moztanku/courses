#!/usr/bin/env python3

import random

from util import RC4, to_hex_pp

# Bank account number: CC XXXX XXXX YYYY YYYY YYYY YYYY
#
# C - Checksum
# X - Bank number
# Y - User account number

# PKO BP: 1020
# Bank Handlowy: 1030
# ING Bank Śląski: 1050
# Santander Bank Polska: 1090
# mBank: 1140

# 48-57
# 0011  0000 48 : 0
# 0011  0001 49 : 1
# 0011  0010 50 : 2
# 0011  0011 51 : 3
# 0011  0100 52 : 4
# 0011  0101 53 : 5
# 0011  0110 54 : 6
# 0011  0111 55 : 7
# 0011  1000 56 : 8
# 0011  1001 57 : 9
# 0000  XXXX
# ABCD
# A = 1 -> 8,9              |   2/10
# B = 1 -> 4,5,6,7          |   4/10
# C = 1 -> 2,3,6,7          |   4/10
# D = 1 -> 1,3,5,7,9        |   5/10
#

def get_random_account_number():
    bank_numbers: list[str] = ["1020", "1030", "1050", "1090", "1140"]

    bank_number: str = random.choice(bank_numbers) + '0000'
    acc_number:str = ''.join(random.choices('0123456789', k=16))

    checksum: str = calculate_checksum(bank_number + acc_number)

    return checksum + bank_number + acc_number

# Checksum calculation:
def calculate_checksum(account_number):
    # Move the four initial characters to the end of the string
    account_number = account_number[4:] + account_number[:4]
    
    # Convert the string to an integer and calculate the remainder on division by 97
    remainder = int(account_number) % 97
    
    # The checksum is a two-digit number
    checksum = str(remainder).zfill(2)
    
    return checksum

def format_acc_number(account_number: str) -> str:
    return f"{account_number[0:2]} {account_number[2:6]} {account_number[6:10]} {account_number[10:14]} {account_number[14:18]} {account_number[18:22]} {account_number[22:26]}"

def main():
    key: str = "Secret"
    num: int = 20

    account_nbrs: list[str] = [get_random_account_number() for _ in range(num)]
    encoded: list[str] = [RC4(key, acc) for acc in account_nbrs]
    # decoded: list[str] = [RC4(key, enc) for enc in encoded]

    for cip in encoded:
        cip2: str = ""

        for c in cip:
            cip2 += chr((ord(c) & 63) % 0x10)

        print(to_hex_pp(cip2))
    print()
    
    for i in range(num):
        for j in range(i + 1, num):
            cipa: str = encoded[i]
            cipb: str = encoded[j]

            xor: str = "".join([chr(ord(a) ^ ord(b)) for a, b in zip(cipa, cipb)])

            print(to_hex_pp(xor))

    # cip: str = encoded[0]

    # print(to_hex_pp(account_nbrs[0]))
    # print(to_hex_pp(cip))

    # for i in range(1, num):
    #     xor: str = "".join([chr(ord(a) ^ ord(b)) for a, b in zip(cip, encoded[i])])
    #     print(to_hex_pp(xor))

if __name__ == "__main__":
    main()

#
#   C1 = K ^ M1
#   C2 = K ^ M2
#   C3 = K ^ M3
#
#   C1 ^ C2 = (K ^ M1) ^ (K ^ M2) = M1 ^ M2
#   C2 ^ C3 = M2 ^ M3
#   (M1 ^ M2) 
#
#