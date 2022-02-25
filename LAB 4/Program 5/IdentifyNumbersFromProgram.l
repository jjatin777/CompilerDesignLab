%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
%}

%%
(['\n' , ';']) {}
([A-Za-z][0-9a-zA-z]*) { } 

([0-9]*['.'][0-9]+) { fprintf(yyout,"%s\n",yytext); }

[-]?([0-9])+ { fprintf(yyout,"%s\n",yytext); }

. {}



%%

int  yywrap(){ return 1;}

int main(){

    extern FILE *yyin, *yyout;

    yyin = fopen("Input.txt", "r");
    yyout = fopen("Output.txt", "w");

    yylex();
    return 0;
}

