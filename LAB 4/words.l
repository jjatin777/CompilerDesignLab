%{
#include<stdio.h>
#include<string.h>
int i =0;
%}

%%
([a-zA-Z0-9])* {i++; printf("%s %d %d\n",yytext,yyleng,i);}
([ ]) ;
"\n" {printf("%d\n", i); i = 0;}

%%

int  yywrap(){
    return 1;
}

int main(){
    yylex();
    return 0;
}