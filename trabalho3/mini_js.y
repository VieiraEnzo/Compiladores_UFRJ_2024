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

%token ID IF ELSE LET PRINT ELSE_IF
%token CDOUBLE CSTRING CINT
%token AND OR ME_IG MA_IG DIF IGUAL
%token MAIS_IGUAL MAIS_MAIS
%token NEWOBJECT NEWARRAY 
%token FOR WHILE

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
    | CMD_IF
    | CMD_FOR ';'
    | '{' CMDs '}' {$$.c = $2.c;}
    | CMD_WHILE ';'
    ;

A : ID '=' E          {$$.c = $1.c + $3.c + "=" + "^";}
  | IDls '=' E        {$$.c = $1.c + $3.c + "[=]" + "^";}
  | ID MAIS_IGUAL E   {$$.c = $1.c + $1.c + "@" + $3.c + "+" + "=" + "^";}
  | IDls MAIS_IGUAL E {$$.c = $1.c + $1.c + "[@]" + $3.c + "+" + "[=]" + "^";}
  | MAIS_MAIS ID       {$$.c = $2.c + $2.c + "@" + "1" + "+" + "=" + "^";}
  | MAIS_MAIS IDls     {$$.c = $2.c + $2.c + "[@]" + "1" + "+" + "[=]" + "^";};
  ;

IDls : ID '.' CAMPO  {$$.c = $1.c + "@" + $3.c; }
      | ID '[' E ']'  {$$.c = $1.c + "@" + $3.c;}
      | ID
      ;

CAMPO : ID '.' CAMPO  {$$.c = $1.c + "[@]" + $3.c; }
      | ID '[' E ']'  {$$.c = $1.c + "[@]" + $3.c;}
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

CMD_WHILE : WHILE '(' E ')' CMD
          {
            string inicio_while = gera_label("inicio_while");
            string fim_while = gera_label("fim_while");
            string definicao_inicio_while = ":" + inicio_while;
            string definicao_fim_while = ":" + fim_while;

            $$.c = $3.c + 
                    inicio_while  + "?" +
                    fim_while + "#" +
                    definicao_inicio_while + 
                    $5.c + $3.c + 
                    inicio_while + "?" +
                    definicao_fim_while;
          }

CMD_FOR : FOR '(' CMD  E ';' A ')' CMD            //TROCAR CMD POR IN_FOR TALVEZ
        {
          string inicio_for = gera_label("inicio_for");
          string fim_for = gera_label("fim_for");
          string definicao_inicio_for = ":" + inicio_for;
          string definicao_fim_for = ":" + fim_for;

          $$.c = $3.c + $4.c + 
              inicio_for + "?" +     //Entra no for?
              fim_for + "#" +
              definicao_inicio_for + 
              $8.c + $6.c + $4.c + 
              inicio_for + "?" +    //Executa comando e verifica
              definicao_fim_for;  
        }

CMD_IF : IF '(' E ')' CMD CMD_ELSE  
         { string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
            $$.c = $3.c +                       // Codigo da expressão
                   lbl_true + "?" +             // Código do IF
                   $6.c + lbl_fim_if + "#" +    // Código do False
                   definicao_lbl_true + $5.c +  // Código do True
                   definicao_lbl_fim_if         // Fim do IF
                   ;
         }

CMD_ELSE : ELSE_IF '(' E ')' CMD CMD_ELSE
        { string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
            $$.c = $3.c +                       // Codigo da expressão
                   lbl_true + "?" +             // Código do IF
                   $6.c + lbl_fim_if + "#" +    // Código do False
                   definicao_lbl_true + $5.c +  // Código do True
                   definicao_lbl_fim_if         // Fim do IF
                   ;
        }
         | ELSE CMD {$$.c = $2.c;}
         | {$$.clear();}
         ;

E : E '<' E { $$.c = $1.c + $3.c + $2.c; }
  | E '>' E { $$.c = $1.c + $3.c + $2.c; }
  | E '+' E { $$.c = $1.c + $3.c + $2.c; }
  | E '-' E { $$.c = $1.c + $3.c + $2.c;}
  | E '*' E { $$.c = $1.c + $3.c + $2.c;}
  | E '/' E { $$.c = $1.c + $3.c + $2.c;}
  | E '%' E { $$.c = $1.c + $3.c + $2.c;}
  | E IGUAL E {$$.c = $1.c + $3.c + "==";}
  | IDls '=' E {$$.c = $1.c + $3.c + "=";}
  | ID {$$.c = $1.c + "@";}
  | ID '.' CAMPO {$$.c = $1.c + "@" + $3.c + "[@]"; }
  | ID '[' E ']'  {$$.c = $1.c + "@" + $3.c + "[@]";}
  | MAIS_MAIS ID  {$$.c = $2.c + $2.c + "@" + "1" + "+" + "=";}
  | MAIS_MAIS IDls  {$$.c = $2.c + $2.c + "[@]" + "1" + "+" + "[=]";};
  | ID MAIS_MAIS {$$.c = $1.c + $1.c + "@" + "1" + "+" + "=";}          //MUITO ERRADO
  | IDls MAIS_MAIS  {$$.c = $2.c + $1.c + "[@]" + "1" + "+" + "[=]";}; //MUITO ERRADO
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