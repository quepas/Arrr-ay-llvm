grammar arrr_ay;

// Tokens
WS      : [ \r\t]+ -> channel(HIDDEN);
INT     : [0-9]+ ;

MUL : '*';
DIV: '/';
ADD: '+';
SUB: '-';

// Grammar rules
program: (expr ';')* ;
number: INT;

expr: '(' expr ')'                        # exprParentheses
    | '[' number? (',' number)* ']'       # exprArray
    | left=expr op=(MUL | DIV) right=expr # exprMulDiv
    | left=expr op=(ADD | SUB) right=expr # exprAddSub
    | number                              # exprNumber
    ;
