#!/usr/bin/env python3

import sys
import zlib

FRAME_BORDER = '01111110'

def to_bytes(data: str) -> bytes:
    data += '0' * (8 - (len(data) % 8))
    output: bytes = b''

    for i in range(0, len(data), 8):
        output += int(data[i:i+8], 2).to_bytes(1, 'big')

    return output

def encode(data: str) -> str:
    crc_checksum: str = bin(
        zlib.crc32(to_bytes(data))
    )[2:].zfill(32)

    data += crc_checksum
    data = data.replace('11111', '111110')

    return FRAME_BORDER + data + FRAME_BORDER


def decode(data: str) -> str:
    data = data.replace(FRAME_BORDER, '')
    data = data.replace('111110', '11111')

    crc_checksum: int = int(data[-32:], 2)
    crc_expected: int = zlib.crc32(to_bytes(data[:-32]))

    if crc_checksum != crc_expected:
        exit(f'CRC32 checksum mismatch: actual {crc_checksum}, expected {crc_expected}.')

    return data[:-32]

def print_help(exec: str, exit_code: int):
    print(f'Usage: input | {exec} --decode/--encode')
    exit(exit_code)

def main():
    args: list[str] = sys.argv

    if len(args) != 2:
        print_help(args[0], 1)

    if args[1] in ['-h', '--help']:
        print_help(args[0], 0)

    if args[1] not in ['--encode', '--decode']:
        print_help(args[0], 1)

    mode: str = args[1][2:]

    if sys.stdin.isatty():
        print_help(args[0], 1)

    data: str = sys.stdin.read()

    for c in data:
        if c not in ['0', '1']:
            exit(f'Invalid input data: {repr(c)} not expected, only \'0\' or \'1\' expected.')

    parsed: str = encode(data) if mode == 'encode' else decode(data)

    print(parsed, end='')

if __name__ == '__main__':
    main()