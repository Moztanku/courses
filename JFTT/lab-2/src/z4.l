%{
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef enum {
    STACK_OK,
    STACK_UNDERFLOW,
    STACK_OVERFLOW
} stack_status;

typedef struct {
    int             data[STACK_SIZE];
    size_t          top;
    stack_status    status;

    void (*push) (int);
    int  (*pop)  (void);
} Stack;

Stack* current_stack = NULL;

void push(int value)
{
    if (!current_stack) {
        return;
    }

    if (current_stack->top == STACK_SIZE) {
        current_stack->status = STACK_OVERFLOW;
        return;
    }

    current_stack->data[current_stack->top++] = value;
}

int pop(void)
{
    if (!current_stack) {
        return -1;
    }

    if (current_stack->top == 0) {
        current_stack->status = STACK_UNDERFLOW;
        return -1;
    }

    return current_stack->data[--current_stack->top];
}

Stack*
new_stack()
{
    Stack* stack = (Stack*) malloc(sizeof(Stack));

    stack->top    = 0;
    stack->status = STACK_OK;

    stack->push = push;
    stack->pop  = pop;

    current_stack = stack;

    return stack;
}

void
delete_stack(Stack* stack)
{
    if (current_stack == stack) {
        current_stack = NULL;
    }
    
    free(stack);
}

Stack* stack = NULL;

int
ipow(int base, int exp)
{
    int result = 1;

    while (exp > 0)
    {
        if (exp & 1)
        {
            result *= base;
        }

        exp >>= 1;
        base *= base;
    }

    return result;
}

%}

%option noyywrap

NUMBER [-]?[1-9][0-9]*
OPERATOR [-+*/^%]

%%
{NUMBER} {
    stack->push(atoi(yytext));

    if (stack->status != STACK_OK)
    {
        fprintf(stderr, "Error: stack is full\n");
        yyterminate();
    }
}

{OPERATOR} {
    int b = stack->pop();
    int a = stack->pop();

    if (stack->status != STACK_OK)
    {
        fprintf(stderr, "Error: not enough operands\n");
        yyterminate();
    }

    switch (yytext[0]) {
        case '+':
            stack->push(a + b);
            break;
        case '-':
            stack->push(a - b);
            break;
        case '*':
            stack->push(a * b);
            break;
        case '/':
            stack->push(a / b);
            break;
        case '^':
            stack->push(ipow(a, b));
            break;
        case '%':
            stack->push(a % b);
            break;
    }
}

\n {
    if (stack->top != 1)
    {
        fprintf(stderr, "Error: not enough operators\n");
        yyterminate();
    }

    printf("= %d\n", stack->pop());
}

[ \t] {}

. {
    fprintf(stderr, "Error: invalid character '%s'\n", yytext);
    yyterminate();
}
%%

#define MAX_BUFFER_SIZE 256

int
main()
{
    char buffer[MAX_BUFFER_SIZE];

    printf("Enter a calculation: \n");

    while (fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL)
    {
        // Check whether input doesn't exceed the buffer size
        if (buffer[strlen(buffer) - 1] != '\n')
        {
            fprintf(stderr, "Error: input is too long\n");
            return 1;
        }

        // Check whether user wants to quit
        if (strcmp(buffer, "q\n") == 0 || strcmp(buffer, "quit\n") == 0)
        {
            break;
        }

        // Parse the input
        YY_BUFFER_STATE state = yy_scan_string(buffer);

        stack = new_stack();

        yylex();

        delete_stack(stack);
    }

    return 0;
}
