%{
#include <stdio.h>
#include <string.h>

void yyerror(char *c);
#include "y.tab.h"


%}


%%

[+]? { return POS; }
[-]?  { yylval = -1; return NEG; }



 

[0] {yylval = atoi(yytext); return Z;} 
[1] {yylval = atoi(yytext); return U;} 

\n { return EOL; }


. ; 

%%

int yywrap() {
  return 1;
}
