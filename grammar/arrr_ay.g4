grammar arrr_ay;

// Tokens
NEWLINE : [\r\n]+ ;
INT     : [0-9]+ ;

MUL : '*';
DIV: '/';
ADD: '+';
SUB: '-';

// Grammar rules
program: (expr ';')* ;
number: INT;

expr: '(' expr ')'                        # exprParentheses
    | left=expr op=(MUL | DIV) right=expr # exprMulDiv
    | left=expr op=(ADD | SUB) right=expr # exprAddSub
    | number                              # exprNumber
    ;
