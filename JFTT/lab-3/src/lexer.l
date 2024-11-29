%{
#include <stdio.h>
#include "parser.tab.h"

#define MOD 1234577
%}

%option noyywrap

line_extension .*[\\]\n

%%

[ \t]                   ;       // ignore whitespace
[\\]\n                  ;       // ignore line continuation
"#"{line_extension}*.*$ ;       // ignore comments

[0]|[1-9][0-9]* {           // match a number
    yylval = atoi(yytext);

    return NUMBER;
}

"(" { return LEFT;    }
")" { return RIGHT;   }
"+" { return ADD;     }
"-" { return SUB;     }
"*" { return MUL;     }
"/" { return DIV;     }
"^" { return POW;     }
\n  { return NEWLINE; }

. {                             // catch all
    fprintf(stderr, "Unrecognized character: %s\n", yytext);
    exit(1);
}

%%
