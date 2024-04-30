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

void casa(int esperado){
    if(token == esperado) token = next_token();
    else{
        printf("Esperado %d, encontrado: %d\n", esperado, token);
        exit(1);
    }
}

int next_token(){
    return yylex();
}

void S(){
    switch (token){
        case _PRINT:
            casa(_PRINT);
            E();
            printf(" print #");
            casa(';');
            S();
            break;
        case _ID:
            A();
            casa(';');
            S();
    }
}

void A(){
    string temp = lexema;
    casa(_ID);
    printf(" " + temp);
    casa('=');
    E();
    printf(" = ^");
}

void E(){
    T();
    E_linha();
}

void E_linha(){
    switch(token){
        case '+':
            casa('+');
            T();
            printf(" +");
            E_linha();
            break;
        case '-':
            casa('-');
            T();
            printf(" -");
            E_linha();
            break;
    }
}

void T(){
    L();
    T_linha();
}

void T_linha(){
    switch (token){
        case '*':
            casa('*');
            L();
            printf(" *");
            T_linha();
            break;
        case '/':
            casa('/');
            L();
            printf(" /");
            T_linha();
            break;
    }
}

void L(){
    F();
    R();
}

void R(){
    switch(token){
        case '^':
            casa('^');
            L();
            printf(" ^");
            break;
        case '!':
            casa('!');
            printf(" !");
            break;
    }
}

void F(){
    switch(token){
        case _ID:
            string temp = lexema;
            casa(_ID);
            printf(temp + " @");
            break;
        case _NUM:
            string temp = lexema;
            casa(_NUM);
            printf(" " + temp);
            break;
        case _STRING:
            casa(_STRING);
            break;
        case '(':
            casa('(');
            E();
            casa(')');
            break;
        case _MAX:
            casa(_MAX);
            casa('(');
            E();
            casa(',');
            E();
            casa(')');
            break;
    }
}

int main() {
    
  token = next_token();
  S();
  printf("Sintaxe ok!\n");

  return 0;
}