# CompilersLexYacc
exercises focused on compiler discipline, using Lex and Yacc, to solve 2 problems

Problem 1:
implementation of a scanner and a parser that receive a number in binary format and print the entire decimal value on the screen. The grammar to be used as a basis is:

Number -> Sign List
Sign -> +
         | -
List -> List Bit
         | Bit
Bit -> 0
         | 1

Execution example:

$ ./binary
111 (you type)
7 (exit)
1111 (you type)
15 (exit)
-101 (you type)
-5 (exit)
-10001 (you type)
-17 (exit)
+1111 (you type)
15 (exit)

Problem 2:

Consider the file LexAndYaccTutorial.pdf, posted on Slack's #general channel. Starting on page 18, the tutorial describes creating a front end for a simple language. This front end will generate a syntactic tree representation, which can be processed by three back end: expression interpreter, translator for stack code and graphic drawing of the tree.

The file calc3.h (page 21) presents the structures that will be used to represent the nodes of the tree. The files calc.l (page 22) and calc.y (page 23) are the definitions for the lexicon and parser, respectively. Back ends are defined in the ex functions (pages 27, 28 and 39). In theory, you don't need to change the calc3.h, calc.l and calc.y files at all. Just create a new .c file with your version of the ex function that plays the ILOC instruction set for the corresponding program on the screen.

You can consider the following:

There is an infinite number of registers.
There are an infinite number of labels.
Every time a variable is referenced, it must be loaded from memory. So it is not wrong to load the address of the variable x twice to handle the expression x = x + 1.
For the PRINT instruction, consider that its execution requires the loading of the value 1 to the fixed register rsys, followed by the invocation of the CALL_SYS rn instruction, where n is the number of the register that contains the value to be printed.


Execution Example
jmhal @ TITAN: ~ $ cat
x = 0;
while (x <3) {
   print x;
   x = x + 1;
}
jmhal @ TITAN: ~ / $ ./calculator <test entry
       LOADI @x, r1
       LOADI 0, r2
       STORE r2, r1
L0:
       LOADI @x, r3
       LOADI 3, r4
       LOAD r3, r5
       CMP_LT r5, r4, r6
       CBR r6, L1, L2
L1:
       LOADI 1, rsys
       LOADI @x, r7
       LOAD r7, r8
       CALL_SYS r8
       LOADI @x, r9
       LOADI @x, r10
       LOADI 1, r11
       LOAD r10, r12
       ADD r11, r12, r13
       STORE r13, r9
       JUMPI L0
L2:

This is just an example. Also create examples to test if-then-else and other arithmetic operations. You can also use other ILOC instructions if you find it more appropriate. In the correction I will consider more cases.
