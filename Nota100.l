%{
#include <iostream>
#include <string>
using namespace std;

string lexema;

string cleanSTR(string a){
    string newS;
    for(int i = 1; i < a.size()-1; i++){
        if(a[i] == '\\' ){
            if(a[i+1] == '\''|| a[i+1] == '"'){
                newS.push_back(a[i+1]);
                i++;
            }else{
                newS.push_back(a[i]);
            }
        }
        else if(a[i] == '"'){
            newS.push_back('"');
            i++;
        }
        else{newS.push_back(a[i]);}
    }
    return newS;
}

string cleanSTRSIMPLE(string a){
    string newS;
    for(int i = 1; i < a.size()-1; i++){
        if(a[i] == '\\' ){
            if(a[i+1] == '\''|| a[i+1] == '"'){
                newS.push_back(a[i+1]);
                i++;
            }else{
                newS.push_back(a[i]);
            }
        }
        else if(a[i] == '\''){
            newS.push_back('\'');
            i++;
        }
        else{newS.push_back(a[i]);}
    }
    return newS;
}

%}

/* Coloque aqui definições regulares */

WS	[ \t\n]
DIGITO  [0-9]
LETRA   [A-Za-z_]
INT     {DIGITO}+
ID      ({LETRA}|$)({LETRA}|{DIGITO})*
FLOAT   {DIGITO}+(\.{DIGITO}+)?([eE][+\-]?{DIGITO}+)?
FOR     [fF][oO][rR]
IF      [iI][fF]
MAIG    ">="
MEIG    "<="
IG      "=="
DIF     "!="
COMENTARIO1 "//"(.)* 
COMENTARIO2 "/*"([^*]|"*"[^/])*"*/"
STRING \"([^"\n]|\"\"|\\\")*\"
STRINGSIMP \'([^'\n]|\'\'|\\\')*\'
EXPR    "{"{ID}
STRING2 [`][^{EXPR}`]*[`]
STRING3 [`][^`$]*"$"
STRING4 "}"[^`]*[\`]
ERROID ({LETRA}|$)({LETRA}|{DIGITO}|$)*


%%
    /* Padrões e ações. Nesta seção, comentários devem ter um tab antes */

{WS}	{} 

{COMENTARIO1}   {lexema = yytext; return _COMENTARIO;}

{COMENTARIO2}   {lexema = yytext; return _COMENTARIO;}

{EXPR}      {lexema = yytext; lexema = lexema.substr(1, lexema.size()-1);  return _EXPR;}

{STRING}   {lexema = yytext; lexema = cleanSTR(lexema) ;return _STRING;}

{STRINGSIMP}   {lexema = yytext; lexema = cleanSTRSIMPLE(lexema);return _STRING;}

{STRING2}   {lexema = yytext;lexema = lexema.substr(1, lexema.size()-2); return _STRING2;}

{STRING3}   {lexema = yytext;lexema = lexema.substr(1, lexema.size()-2); return _STRING2;}

{STRING4}   {lexema = yytext;lexema = lexema.substr(1, lexema.size()-2); return _STRING2;}

{MAIG}   {lexema = yytext; return _MAIG;}

{MEIG}   {lexema = yytext; return _MAIG;}

{IG}   {lexema = yytext; return _IG;}

{DIF}   {lexema = yytext; return _DIF;}

{FOR}   {lexema = yytext; return _FOR;}

{IF}   {lexema = yytext; return _IF;}

{INT}   {lexema = yytext; return _INT;}

{FLOAT} {lexema = yytext; return _FLOAT;}

{ID}    {lexema = yytext; return _ID;}

{ERROID}    {lexema = yytext; cout << "Erro: Identificador invalido: " << lexema << endl;}

.       {lexema = yytext; return lexema[0];}

%%

/* Não coloque nada aqui - a função main é automaticamente incluída na hora de avaliar e dar a nota. */
