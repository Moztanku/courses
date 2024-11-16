%{
#include <stdio.h>

void
print_help(const char* exec, int status)
{
    FILE* stream = (status == 0) ? stdout : stderr;

    fprintf(stream, "Usage: %s <file-path>\n", exec);

    exit(status);
}

%}

%option noyywrap

%%

"--".*\n { printf("\n"); } /* remove comments. */

%%

int main(int argc, char **argv) {
    if (argc != 2) {
        print_help(argv[0], 1);
    }

    const char* arg = argv[1];

    if (arg[0] == '-' && arg[1] == 'h' && arg[2] == '\0') {
        print_help(argv[0], 0);
    }

    FILE* file = fopen(arg, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file %s\n", arg);
        return 1;
    }

    yyin = file;

    yylex();

    fclose(file);

    return 0;
}
