%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void sub(char *);
int count =0;
%}

%%

([A-Za-z0-9])* { sub(yytext); } 
([. ,\n]) {fprintf(yyout,"%s",yytext);}

%%

int  yywrap(){ return 1;}

int main(){

    extern FILE *yyin, *yyout;

    yyin = fopen("Input.txt", "r");
    yyout = fopen("Output.txt", "w");

    yylex();
    fprintf(yyout,"\nCount : %d",count);
    return 0;
}

void sub(char * s){
    int len = strlen(s);
    if(len > 10 ){
        count++;
        len = 10;
    } 
    for(int i = 0; i< len; i++)
        fprintf(yyout,"%c",s[i]);
}
