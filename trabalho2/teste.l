%{
#include <iostream>
#include <string>
using namespace std;

int token;

enum TOKEN { _ID = 256, _NUM, _STRING};

%}

/* Coloque aqui definições regulares */

WS	[ \t\n]
DIGITO  [0-9]
LETRA   [A-Za-z_]
INT     {DIGITO}+
ID      ({LETRA}|$)({LETRA}|{DIGITO})*
FLOAT   {DIGITO}+(\.{DIGITO}+)?([eE][+\-]?{DIGITO}+)?
STRING \"([^"\n]|\"\"|\\\")*\"


%%
    /* Padrões e ações. Nesta seção, comentários devem ter um tab antes */

{WS}	{} 

{STRING}   {lexema = yytext; lexema = cleanSTR(lexema) ;return _STRING;}

{INT}   {lexema = yytext; return _INT;}

{FLOAT} {lexema = yytext; return _NUM;}

{ID}    {lexema = yytext; return _NUM;}

.       {lexema = yytext; return lexema[0];}

%%

void casa(int esperado){
    if(token == esperado) token = next_token();
    else{
        printf("Esperado %d, encontrado: %d\n", esperado, token);
        exit(1);
    }
}

int next_token(){
    return yylex;
}


int main() {


    
  token = next_token();
  V();
  printf("Sintaxe ok!\n");

  return 0;
}