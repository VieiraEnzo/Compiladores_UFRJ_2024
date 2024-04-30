%{
#include <iostream>
#include <string>
using namespace std;

int token;
string lexema, temp;

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

"print" {lexema = yytext; return _PRINT;}

"max"   {lexema = yytext; return _MAX;}

{STRING}   {lexema = yytext; return _STRING;}

{INT}   {lexema = yytext; return _NUM;}

{FLOAT} {lexema = yytext; return _NUM;}

{ID}    {lexema = yytext; return _ID;}

.       {lexema = yytext; return lexema[0];}

%%

void casa(int esperado){
    if(token == esperado) token = next_token();
    else{
        printf("Esperado %d, encontrado: %d\n", esperado, token);
        exit(1);
    }
}

void print(string s){
    cout << s;
}

int next_token(){
    return yylex();
}

void S(){
    switch (token){
        case _PRINT:
            casa(_PRINT);
            E();
            print(" print #");
            casa(';');
            print("\n");
            S();
            break;
        case _ID:
            A();
            casa(';');
            print("\n");
            S();
            break;
    }
}

void A(){
    temp = lexema;
    casa(_ID);
    print(" " + temp);
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
            print(" +");
            E_linha();
            break;
        case '-':
            casa('-');
            T();
            print(" -");
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
            print(" *");
            T_linha();
            break;
        case '/':
            casa('/');
            L();
            print(" /");
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
            print(" power #");
            break;
        case '!':
            casa('!');
            print(" fat #");
            break;
    }
}

void F(){
    switch(token){
        case _ID:
            temp = lexema;
            casa(_ID);
            print(" " + temp + " @");
            break;
        case _NUM:
            temp = lexema;
            casa(_NUM);
            print(" " + temp);
            break;
        case _STRING:
            temp = lexema;
            casa(_STRING);
            print(" " + temp);
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
            print(" max #");
            break;
    }
}

int main() {
    
  token = next_token();
  S();

  return 0;
}