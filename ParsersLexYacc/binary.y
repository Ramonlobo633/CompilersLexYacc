%{
#include <stdio.h>

void yyerror(char *c);
int yylex(void);

%}

%token POS NEG Z U EOL

%%

PROGRAMA:
	PROGRAMA NUMBER EOL
	|
	;
NUMBER:
	SIGN LIST {
		$$ = $1 * $2;
		printf("%d\n", $1*$2 );
		};
	
SIGN:	
	NEG { $$ = -1; };
	| POS { $$ = 1;}
	| {$$ = 1;}
	;

LIST:
	LIST BIT {$$ = 2 * $1 + $2;}
	| BIT {$$ = $1; }
	;

BIT: 
	Z {$$ = 0; }
	| U { $$ = 1; }
	;

%%


void yyerror( char *c) {
  printf("Meu erro foi %s\n", c);


}

int main(){
  yyparse();
  return 0;
}


