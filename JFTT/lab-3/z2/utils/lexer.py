import ply.lex as lex
import sys

tokens = (
    'NUMBER',   # numbers
    'LEFT',   # parenthesis
    'RIGHT',
    'ADD',      # operators
    'SUB',
    'MUL',
    'DIV',
    'POW',
    'NEWLINE'   # newline
)

# Ignore whitespace
t_ignore = ' \t'

# Ignore line continuation
def t_line_continuation(t):
    r'\\\n'
    pass  # Simply ignore the token (no value is returned)

# Ignore comments
def t_comment(t):
    r'\#([^\n]*[\\]\n)*[^\n]*$'
    pass  # Simply ignore the token (no value is returned)

def t_NUMBER(t):
    r'\d+'
    t.value = int(t.value)
    return t

t_LEFT    = r'\('
t_RIGHT   = r'\)'
t_ADD     = r'\+'
t_SUB     = r'-'
t_MUL     = r'\*'
t_DIV     = r'/'
t_POW     = r'\^'
t_NEWLINE = r'\n'

def t_error(t):
    print("Illegal character '%s'" % t.value[0])
    sys.exit(1)

lexer = lex.lex()
