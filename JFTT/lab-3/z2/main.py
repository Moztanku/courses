#!/usr/bin/env python3

from utils import lexer, parser

import sys

lex = lexer.lexer
par = parser.parser

def main():
    while True:
        try:
            s = input('')
            s += '\n'
        except EOFError:
            break
        if not s:
            continue
        par.parse(s, lexer=lex)

if __name__ == "__main__":
    main()
