grammar arrr_ay;

// Tokens
NEWLINE : [\r\n]+ ;
INT     : [0-9]+ ;

// Grammar rules
prog:	(expr NEWLINE)* ;
expr:	expr ('*'|'/') expr
    |	expr ('+'|'-') expr
    |	INT
    |	'(' expr ')'
    ;
