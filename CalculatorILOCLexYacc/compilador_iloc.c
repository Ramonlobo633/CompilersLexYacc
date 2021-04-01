#include <stdio.h>
#include "calc3.h"
#include "y.tab.h"

static int lbl = 0, registers = 0;

int ex(nodeType *p) {
	
	int lbl1, lbl2, n, rsys, aux, aux2;
	


	if (!p) return 0;

	switch(p->type) {
		case typeCon:
			printf("\tLoadI\t%d, r%d\n", p->con.value, n = registers++);
			
		break;
		
		case typeId:
			printf("\tLoadI \t@%c, r%d\n", p->id.i, n = registers++);
			
		break;
		case typeOpr:
		
			switch(p->opr.oper) {
				case WHILE:
					printf("L%03d:\n", lbl1 = lbl++);
					ex(p->opr.op[0]);
					ex(p->opr.op[1]);
					printf("\tjumpI\tL%03d\n", lbl1);
					lbl2 = lbl++;
					printf("L%03d:\n", lbl2);
				break;
			
				case IF:
					ex(p->opr.op[0]);
					if (p->opr.nops > 2) {
				
					/* if else */
						printf("L%03d:\n", lbl1 = lbl++);
						ex(p->opr.op[1]);
						lbl1 = lbl++;
						lbl2 = lbl++;
						printf("L%03d:\n", lbl1);
						ex(p->opr.op[2]);
						printf("L%03d:\n", lbl2);
					} else {
				
					/* if */
						printf("L%03d:\n", lbl1 = lbl++);
						ex(p->opr.op[1]);
						printf("L%03d:\n", lbl2);
					}
				break;
			
				case PRINT:
					ex(p->opr.op[0]);
					printf("\tLoadI\t1, rsys\n");
					printf("\tLoadI\t @%c, r%d\n", p->id.i, n = registers++);
					printf("\tLoad\tr%d, r%d\n", n, n = registers++);
					printf("\tCALL_SYS r%d\n", n);
				break;
			
				case '=':
					//armazena o numero do registrador quando '=' é chamado
					aux = n;
					ex(p->opr.op[1]);
					printf("\tstore\tr%d, r%d\n", n = registers++, aux);
					
				break;
			
				case UMINUS:
					ex(p->opr.op[0]);
					printf("\tneg\n");
				break;
			
				default:
					ex(p->opr.op[0]);
					ex(p->opr.op[1]);
				switch(p->opr.oper) {
				
					case '+':
						aux = n;
						ex(p->opr.op[1]);
						aux2 = n;
						printf("\tLoad\tr%d, r%d \n", aux, n = registers++);
						printf("\tadd\tr%d, r%d, r%d \n", aux2, n, n = registers++);	
						break;
					case '-':
						aux = n;
						ex(p->opr.op[1]);
						aux2 = n;
						printf("\tLoad\tr%d, r%d \n", aux, n = registers++);
						printf("\tsub\tr%d, r%d, r%d \n", aux2, n, n = registers++); 
						
						break;
					case '*':
						aux = n;
						ex(p->opr.op[1]);
						aux2 = n;
						printf("\tLoad\tr%d, r%d \n", aux, n = registers++);
						printf("\tmult\tr%d, r%d, r%d \n", aux2, n, n = registers++); 
						
						break;
					case '/':
						aux = n;
						ex(p->opr.op[1]);
						aux2 = n;
						printf("\tLoad\tr%d, r%d \n", aux, n = registers++);
						printf("\tdiv\tr%d, r%d, r%d \n", aux2, n, n = registers++); 
						
						break;
					case '<':
						aux = n;
						ex(p->opr.op[1]);
						aux2 = n;
						printf("\tcmp_LT\tr%d, r%d, r%d \n", aux2, aux, n = registers++); 
						printf("\tcbr\tr%d, L%03d, L%03d\n", n, lbl1, lbl2);
				
						break;
					case '>':
						aux = n;
						ex(p->opr.op[1]);
						aux2 = n;
						printf("\tcmp_GT\tr%d, r%d, r%d \n", aux2, aux, n = registers++); 
						printf("\tcbr\tr%d, L%03d, L%03d\n", n, lbl1, lbl2);
						n = registers++;
						break;
					case GE:
						aux = n;
						ex(p->opr.op[1]);
						aux2 = n;
						printf("\tcmp_GE\tr%d, r%d, r%d \n", aux2, aux, n = registers++); 
						printf("\tcbr\tr%d, L%03d, L%03d\n", n, lbl1, lbl2);
						n = registers++;
						break;
					case LE:
						printf("\tcmp_LE\tr%d, r%d, r%d \n", aux2, aux, n = registers++); 
						printf("\tcbr\tr%d, L%03d, L%03d\n", n, lbl1, lbl2);
						n = registers++;
						break;
					case NE:
						aux = n;
						ex(p->opr.op[1]);
						aux2 = n;
						printf("\tcmp_NE\tr%d, r%d, r%d \n", aux2, aux, n = registers++); 
						printf("\tcbr\tr%d, L%03d, L%03d\n", n, lbl1, lbl2);
						n = registers++;
						break;
					case EQ:
						aux = n;
						ex(p->opr.op[1]);
						aux2 = n;
						printf("\tcmp_EQ\tr%d, r%d, r%d \n", aux2, aux, n = registers++); 
						printf("\tcbr\tr%d, L%03d, L%03d\n", n, lbl1, lbl2);
						n = registers++;
						break;
				}
			}
	}
	return 0;
}
