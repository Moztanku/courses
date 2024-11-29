%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "galois.h"
#include "print.h"

extern int yylex();
extern int yyparse();

void yyerror(const char*){
}

%}

%token NUMBER
%token LEFT RIGHT
%left ADD SUB
%left MUL DIV
%right POW
%token NEWLINE

%start input

%%

input:
    | input line
    ;

line:
    NEWLINE
    | error NEWLINE     {
        clear_buffer();
        printf("Błąd.\n"); 
    }
    | expr NEWLINE      {
        if (buffer_status == NOOK)
        {
            clear_buffer();
            printf("Błąd. Przepełnienie bufora zapisu.\n");
        }
        else
        {
            print_buffer();
            clear_buffer();
            printf("\nWynik: %d\n", $1); }
        }
    ;

expr:
    NUMBER       { $$ = gf_norm($1);     write_buffer("%d ", $$); }
    | SUB NUMBER { $$ = gf_norm(-$2);    write_buffer("%d ", $$); }
    | expr POW expr POW expr { YYERROR; }
    | expr ADD expr     { $$ = gf_add($1, $3);  write_buffer("+ "); }
    | expr SUB expr     { $$ = gf_sub($1, $3);  write_buffer("- "); }
    | expr MUL expr     { $$ = gf_mul($1, $3);  write_buffer("* "); }
    | expr DIV expr     { $$ = gf_div($1, $3);  write_buffer("/ "); }
    | expr POW expr     { $$ = gf_pow($1, $3);  write_buffer("^ "); }
    | LEFT expr RIGHT   { $$ = $2; }
    ;

%%

int main()
{
    return yyparse();
}
