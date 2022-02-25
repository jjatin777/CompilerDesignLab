%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int line_no = 0;
%}

%%

([\n]) { line_no++; fprintf(yyout,"%s%d ",yytext,line_no);}
. {fprintf(yyout,"%s",yytext);}

%%

int  yywrap(){ return 1;}

int main(){

    extern FILE *yyin, *yyout;

    yyin = fopen("Input.txt", "r");
    yyout = fopen("Output.txt", "w");

    line_no++; fprintf(yyout,"%d ",line_no);

    yylex();
    return 0;
}

