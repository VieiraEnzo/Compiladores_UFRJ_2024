%{
#include <iostream>
#include <string>
using namespace std;

int token;
string lexema;

enum TOKEN { _ID = 256, _NUM, _STRING, _PRINT, _MAX};

void S();
void A();
void E();
void T();
void L();
void F();
void R();
void E_linha();
void T_linha();
void L_linha();
int next_token();
void casa(int esperado);

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

{STRING}   {lexema = yytext; return _STRING;}

{INT}   {lexema = yytext; return _NUM;}

{FLOAT} {lexema = yytext; return _NUM;}

{ID}    {lexema = yytext; return _ID;}

'print' {lexema = yytext; return _PRINT;}

'max'   {lexema = yytext; return _MAX;}

.       {lexema = yytext; return lexema[0];}

%%

// void casa(int esperado){
//     if(token == esperado) token = next_token();
//     else{
//         printf("Esperado %d, encontrado: %d\n", esperado, token);
//         exit(1);
//     }
// }

int main() {
  int token = 0;
  
  while( (token = yylex()) != 0 )  
    printf( "%d %s\n", token, lexema.c_str() );
  
  return 0;
}