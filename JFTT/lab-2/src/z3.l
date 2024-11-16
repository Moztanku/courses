%{
#include <stdio.h>
#include <string.h>

void
print_help(const char* exec, int status)
{
    FILE* stream = (status == 0) ? stdout : stderr;

    fprintf(stream, "Usage: %s <file-path> [-d\\--keep-doxygen]\n", exec);
    fprintf(stream, "    -d\\--keep-doxygen: Keep Doxygen comments in the output\n");

    exit(status);
}

int keep_doxygen = 0;

size_t delim_len;
char*  delim;
%}

%option noyywrap

%x RAW_STRING
dchar_seq [^()\\[:space:]]{0,16}

%x IGNORE_BLOCK_COMMENT
%x KEEP_BLOCK_COMMENT

%%

<INITIAL>{
    /* filtering out non-comments */
    \".*\"  { ECHO; }                       /* string literals */
    R["]{dchar_seq}[(] {                    /* raw string literals */
        delim_len = yyleng - 3;

        delim = (char*)malloc(delim_len + 1);
        strncpy(delim, yytext + 2, delim_len);
        delim[delim_len] = '\0';

        ECHO;
        BEGIN(RAW_STRING);
    }

    /* filtering out Doxygen comments */
    "///".*\n   { if (keep_doxygen) ECHO; }
    "//!".*\n   { if (keep_doxygen) ECHO; }

    "/**"|"/*!" {
        if (keep_doxygen) {
            ECHO;
            BEGIN(KEEP_BLOCK_COMMENT);
        } else {
            BEGIN(IGNORE_BLOCK_COMMENT);
        }
    }
    

    /* filtering out comments */
    ^"//".*\n   {}                          /* full-line comments */
    "//".*$     {}                          /* single-line comments */
    "/*"        { BEGIN(IGNORE_BLOCK_COMMENT); }   /* block comments */
}

<RAW_STRING>{
    .*[)]{dchar_seq}["] {
        ECHO;

        if (strncmp(yytext + yyleng - delim_len - 1, delim, delim_len) == 0) {
            free(delim);
            BEGIN(INITIAL);
        }
    }
}

<IGNORE_BLOCK_COMMENT>{
    \*\/     { BEGIN(INITIAL); }
    .|[\n]   {}
}

<KEEP_BLOCK_COMMENT>{
    "*/"     { ECHO; BEGIN(INITIAL); }
    .|[\n]   { ECHO; }
}

%%

int
main(int argc, char **argv)
{
    if (argc != 2 && argc != 3) {
        print_help(argv[0], 1);
    }

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        print_help(argv[0], 0);
    }

    if (argc == 3 && strcmp(argv[2], "-d") != 0 && strcmp(argv[2], "--keep-doxygen") != 0) {
        print_help(argv[0], 1);
    }

    FILE* file = fopen(argv[1], "r");

    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
        return 1;
    }

    keep_doxygen = argc == 3;

    yyin = file;

    yylex();

    return 0;
}