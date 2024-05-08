%{
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int linha = 1, coluna = 1; 

struct Atributos {
  vector<string> c; // Código

  int linha = 0, coluna = 0;

  void clear() {
    c.clear();
    linha = 0;
    coluna = 0;
  }
};

#define YYSTYPE Atributos

extern "C" int yylex();
int yyparse();
void yyerror(const char *);

vector<string> concatena( vector<string> a, vector<string> b ) {
  a.insert( a.end(), b.begin(), b.end() );
  return a;
}

vector<string> operator+( vector<string> a, vector<string> b ) {
  return concatena( a, b );
}

vector<string> operator+( vector<string> a, string b ) {
  a.push_back( b );
  return a;
}

vector<string> operator+( string a, vector<string> b ) {
  return vector<string>{ a } + b;
}

vector<string> resolve_enderecos( vector<string> entrada ) {
  map<string,int> label;
  vector<string> saida;
  for( int i = 0; i < entrada.size(); i++ ) 
    if( entrada[i][0] == ':' ) 
        label[entrada[i].substr(1)] = saida.size();
    else
      saida.push_back( entrada[i] );
  
  for( int i = 0; i < saida.size(); i++ ) 
    if( label.count( saida[i] ) > 0 )
        saida[i] = to_string(label[saida[i]]);
    
  return saida;
}

string gera_label( string prefixo ) {
  static int n = 0;
  return prefixo + "_" + to_string( ++n ) + ":";
}

void print( vector<string> codigo ) {
  for( string s : codigo )
    cout << s << " ";
    
  cout << endl;  
}
%}

%token ID IF ELSE LET PRINT
%token CDOUBLE CSTRING CINT
%token AND OR ME_IG MA_IG DIF IGUAL
%token MAIS_IGUAL MAIS_MAIS
%token NEWOBJECT NEWARRAY 

%right '='
%left OR
%left AND
%nonassoc '<' '>' ME_IG MA_IG IGUAL DIF
%left '+' '-'
%left '*' '/' '%'
%left MAIS_MAIS

%%

S : CMDs { print( resolve_enderecos( $1.c + "." ) ); }
  ;

CMDs  : CMDs CMD {$$.c = $1.c + $2.c;};
      | CMD
      ;

CMD : CMD_LET ';'
    | PRINT E ';' { $$.c = $2.c + "println" + "#"; }
    | A ';' 
    ;

A : ID '=' E          {$$.c = $1.c + $3.c + "=" + "^";}
  | IDls '=' E        {$$.c = $1.c + $3.c + "[=]" + "^";}
  | ID MAIS_IGUAL E   {$$.c = $1.c + $1.c + "@" + $3.c + "+" + "=" + "^";}
  | IDls MAIS_IGUAL E {$$.c = $1.c + $1.c + "[@]" + $3.c + "+" + "[=]" + "^";}
  | ID MAIS_MAIS      {$$.c = $1.c + $1.c + "@" + "1" + "+" + "=" + "^";}
  | IDls MAIS_MAIS    {$$.c = $1.c + $1.c + "[@]" + "1" + "+" + "[=]" + "^";};
  ;

IDls : 
    | ID '.' IDls  {$$.c = $1.c + "@" + $3.c; }
    | ID '[' E ']'  {$$.c = $1.c + "@" + $3.c;}
    | ID
    ;

CMD_LET : LET VARs { $$.c = $2.c; }
        ;

VARs : VAR ',' VARs { $$.c = $1.c + $3.c; } 
     | VAR
     ;

VAR : ID  { $$.c = $1.c + "&"; }
    | ID '=' E {$$.c = $1.c + "&" + $1.c + $3.c + "=" + "^"; }
    ;


E : E '<' E { $$.c = $1.c + $3.c + $2.c; }
  | E '>' E { $$.c = $1.c + $3.c + $2.c; }
  | E '+' E { $$.c = $1.c + $3.c + $2.c; }
  | E '-' E { $$.c = $1.c + $3.c + $2.c;}
  | E '*' E { $$.c = $1.c + $3.c + $2.c;}
  | E '/' E { $$.c = $1.c + $3.c + $2.c;}
  | E '%' E { $$.c = $1.c + $3.c + $2.c;}
  | IDls '=' E {$$.c = $1.c + $3.c + "=";}
  | ID {$$.c = $1.c + "@";}
  | ID '.' IDls {$$.c = $1.c + "@" + $3.c + "[@]"; }
  | ID '[' E ']'  {$$.c = $1.c + "@" + $3.c + "[@]";}
  | ID MAIS_MAIS {$$.c = $1.c + $1.c + "@" + "1" + "+" + "=";}
  | IDls MAIS_MAIS {$$.c = $1.c + $1.c + "[@]" + "1" + "+" + "[=]";};
  | CDOUBLE
  | CINT
  | CSTRING
  | '-' E {$$.c = "0" + $2.c + "-";}
  | NEWARRAY
  | NEWOBJECT
  | '(' E ')' {$$.c = $2.c;}
  ;
  

%%

#include "lex.yy.c"

void yyerror( const char* st ) {
   puts( st ); 
   printf( "Proximo a: %s\n", yytext );
   exit( 0 );
}

int main( int argc, char* argv[] ) {
  yyparse();
  
  return 0;
}