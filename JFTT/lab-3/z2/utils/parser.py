import ply.yacc as yacc

from .lexer import tokens
from .galois import Galois

precedence = (
    ('left', 'ADD', 'SUB'),
    ('left', 'MUL', 'DIV'),
    ('nonassoc', 'POW')
)

Order: int = 1234577

buffer = ""

def write_to_buffer(s: str):
    global buffer
    buffer += s + ' '

def print_buffer():
    global buffer
    print(buffer)
    buffer = ""

def clear_buffer():
    global buffer
    buffer = ""

def p_empty(p):
    '''expression : NEWLINE'''
    pass

def p_expression_newline(p):
    '''expression : expression NEWLINE'''
    p[0] = p[1]
    print_buffer()
    clear_buffer()
    print("Result: ", p[0].value)

def p_expression_number(p):
    '''expression : NUMBER'''
    p[0] = Galois(Order, p[1])
    write_to_buffer(str(p[0].value))

def p_expression_sub_number(p):
    '''expression : SUB NUMBER'''
    p[0] = Galois(Order, -p[2])
    write_to_buffer(str(p[0].value))

def p_expression_binop(p):
    '''expression : expression ADD expression
                  | expression SUB expression
                  | expression MUL expression
                  | expression DIV expression
                  | expression POW expression'''
    if p[2] == '+':
        p[0] = p[1].add(p[3])
    elif p[2] == '-':
        p[0] = p[1].sub(p[3])
    elif p[2] == '*':
        p[0] = p[1].mul(p[3])
    elif p[2] == '/':
        p[0] = p[1].div(p[3])
    elif p[2] == '^':
        p[0] = p[1].pow(p[3])

    write_to_buffer(str(p[2]))

def p_expression_group(p):
    '''expression : LEFT expression RIGHT'''
    p[0] = p[2]

def p_error(p):
    print("Błąd.")

parser = yacc.yacc()

