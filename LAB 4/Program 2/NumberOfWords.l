%{
#include<stdio.h>
#include<string.h>
int count = 0;
%}

%%
([A-Za-z0-9])* {count ++;}
([;,.* ,\n]) { ; }
%%

int  yywrap(){}


int main(){

    extern FILE *yyin, *yyout;

    yyin = fopen("Input.txt", "r");
    yyout = fopen("Output.txt", "w");

    yylex();
    printf("%d",count);
    fprintf(yyout,"%d",count);
    return 0;
}
