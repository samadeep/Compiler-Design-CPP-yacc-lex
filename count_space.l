
%{
#include<stdio.h>
#include<string.h>
%}


%{
    int a = 0;
%}

%%
[ ] a++;
%%

main()
{
    yylex();
    printf("Spaces = % d \n",a);
}