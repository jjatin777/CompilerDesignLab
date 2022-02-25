%{
#include<stdio.h>
#include<string.h>

%}

%%
([A-Z]) {fprintf(yyout,"%c",yytext[0]+32);}
([. ,\n]) { fprintf(yyout,"%c",yytext[0]);}

%%

int  yywrap(){}


int main(){

    extern FILE *yyin, *yyout;

    yyin = fopen("uppercase input file.txt", "r");
    yyout = fopen("uppercase ouput file.txt", "w");

    yylex();
    return 0;
}
