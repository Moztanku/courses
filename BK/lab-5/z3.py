#!/usr/bin/env python3

import random

from util import RC4, to_hex

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

def get_random_account_number():
    bank_numbers: list[str] = ["1020", "1030", "1050", "1090", "1140"]

    bank_number: str = random.choice(bank_numbers) + '0000'
    acc_number:str = ''.join(random.choices('0123456789', k=16))

    checksum: str = calculate_checksum(bank_number + acc_number)

    return checksum + bank_number + acc_number

# Checksum calculation:
def calculate_checksum(account_number):
    # Replace letters with digits
    account_number = ''.join(str(ord(c) - 55) if c.isalpha() else c for c in account_number)
    
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

    account_nbrs: list[str] = [get_random_account_number() for _ in range(10)]
    encoded: list[str] = [RC4(key, acc) for acc in account_nbrs]
    decoded: list[str] = [RC4(key, enc) for enc in encoded]

    for i in range(10):
        print(f"Account: {format_acc_number(account_nbrs[i])}")
        print(f"Encoded: {to_hex(encoded[i])}")
        print(f"Decoded: {format_acc_number(decoded[i])}\n")

if __name__ == "__main__":
    main()