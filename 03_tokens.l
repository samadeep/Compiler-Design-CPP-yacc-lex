%{
#include <stdio.h>
%}

%option noyywrap

%%

[0-9]+                      { printf("INTEGER: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*      { printf("IDENTIFIER: %s\n", yytext); }
[+\-*/]                     { printf("OPERATOR: %s\n", yytext); }
[=]                         { printf("ASSIGNMENT: %s\n", yytext); }
[;]                         { printf("SEMICOLON: %s\n", yytext); }
[(]                         { printf("LEFT PARENTHESIS: %s\n", yytext); }
[)]                         { printf("RIGHT PARENTHESIS: %s\n", yytext); }
[\n]                        { printf("NEWLINE\n"); }
[ \t]                       /* ignore whitespace */
.                           { printf("ERROR: %s\n", yytext); }

%%


int main()
{
    yylex();
    return 0;
}
