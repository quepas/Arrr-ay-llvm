grammar arrr_ay;

// Tokens
WS      : [ \r\t]+ -> channel(HIDDEN);

fragment DIGIT : [0-9];
fragment NON_ZERO_DIGIT : [1-9];
fragment LETTER : [a-zA-Z];
fragment EXPONENT : [eE][+\-]? DIGIT+;

FLOATING_POINT
  : NON_ZERO_DIGIT DIGIT+ '.' DIGIT+ EXPONENT?
  | DIGIT '.' DIGIT+ EXPONENT?
  | NON_ZERO_DIGIT DIGIT* //  Integer-like
  ;

MUL : '*';
DIV: '/';
ADD: '+';
SUB: '-';

// Grammar rules
program: (expr ';')* ;
number: FLOATING_POINT;

expr: '(' expr ')'                        # exprParentheses
    | '[' number? (',' number)* ']'       # exprArray
    | left=expr op=(MUL | DIV) right=expr # exprMulDiv
    | left=expr op=(ADD | SUB) right=expr # exprAddSub
    | number                              # exprNumber
    ;
