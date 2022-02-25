%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
%}

%%
include|break|continue|using|namespace|main|std|cout|cin|endl { printf("Keywords %s\n",yytext); }

int|double|string|float|short|long { printf("Datatype %s\n",yytext); }

[<].*[>] { printf("Libraries %s\n",yytext); }

"=="|"++"|"+="|"-="|"--"|"*="|"**"|"<<"|">>"|"%="|"="|"-"|"+"|"%"|"*" { printf("Operators %s\n",yytext); }

([A-Za-z][0-9a-zA-z]*) { printf("Identifiers %s\n",yytext); } 

([0-9]*['.'][0-9]+) { printf("Literal %s\n",yytext); }

([0-9]+) { printf("Literal %s\n",yytext); }

["].*["] { printf("Literal %s\n",yytext); }

","|"("|")"|"{"|"}"|"#"|";" { printf("punctuator %s\n",yytext); }

. { ; }
%%

int  yywrap(){ return 1;}

int main(){

    extern FILE *yyin, *yyout;

    yyin = fopen("Input.txt", "r");
    yyout = fopen("Output.txt", "w");

    yylex();
    return 0;
}

