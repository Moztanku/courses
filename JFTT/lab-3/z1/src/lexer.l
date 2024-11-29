%{
#include <stdio.h>
#include "parser.tab.h"
%}

%option noyywrap

line_extension .*[\\]\n

%%

[ \t]                   ;       // ignore whitespace
[\\]\n                  ;       // ignore line continuation
"#"{line_extension}*.*$ ;       // ignore comments

[0]|[1-9][0-9]* {               // match a number
    yylval = atoi(yytext);

    return NUMBER;
}

"(" { return LEFT;    }         // match parentheses
")" { return RIGHT;   }
"+" { return ADD;     }         // match operators
"-" { return SUB;     }
"*" { return MUL;     }
"/" { return DIV;     }
"^" { return POW;     }
\n  { return NEWLINE; }         // match newline

. {                             // unrecognized character
    fprintf(stderr, "Unrecognized character: %s\n", yytext);
    exit(1);
}

%%
