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
  int i = 1;
  for( string s : codigo )
    cout << s << " ";
    
  cout << endl;  
}

vector<string> limpAcesso(vector<string> s){
  s.pop_back();
  return s;
}

enum TipoDecl { DeclVar, DeclConst, DeclLet };


struct Var {

  int linha, coluna;

  TipoDecl tipo;

};

map<string,Var> ts; // Tabela de Símbolos

#define YYSTYPE Atributos

// Dispara um erro se não pode declarar.

void insere_tabela_de_simbolos( TipoDecl tipo, Atributos at ){

  string nome = at.c[0];
  int linha = at.linha;
  int coluna = at.coluna;

  if( ts.count(nome) > 0 ){

      TipoDecl tipoDaVar = ts[nome].tipo;

      if(!(tipoDaVar == tipo && tipo == DeclVar)){
            cout << "Erro: a variável '" << nome <<"' ja foi declarada na linha " << ts[nome].linha << ".\n";
            exit(1);
      }

  }else{
      Var k;
      k.tipo = tipo;
      k.linha = linha;
      k.coluna = coluna;
      ts[nome] = k;
  }

}

void verificar_variavel(Atributos at){
  string nome = at.c[0];
  if(ts.count(nome) == 0){
      cout << "Erro: a variável '" << nome << "' não foi declarada.\n";
      exit(1);
  }
}

void verificar_const(Atributos at){
  string nome = at.c[0];
  if(ts[nome].tipo == DeclConst){
    cout << "Erro: tentativa de modificar uma variável constante '" << nome << "'' .\n";
    exit(1);
  }
}

%}

%token ID IF ELSE PRINT ELSE_IF
%token CDOUBLE CSTRING CINT
%token AND OR ME_IG MA_IG DIF IGUAL
%token MAIS_IGUAL MAIS_MAIS
%token NEWOBJECT NEWARRAY 
%token FOR WHILE
%token LET CONST VAR

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

CMD : CMD_DECL ';'
    | PRINT E ';' { $$.c = $2.c + "println" + "#"; }
    | A ';' 
    | CMD_IF
    | CMD_FOR
    | '{' CMDs '}' {$$.c = $2.c;}
    | CMD_WHILE
    | ';' {$$.clear();}
    ;

A : Lvalue '=' E            {$$.c = limpAcesso($1.c) + $3.c + "=" + "^";}
  | LvalueProp '=' E        {$$.c = limpAcesso($1.c) + $3.c + "[=]" + "^";}
  | Lvalue MAIS_IGUAL E     {$$.c = limpAcesso($1.c) + $1.c + $3.c + "+" + "=" + "^";}
  | LvalueProp MAIS_IGUAL E {$$.c = limpAcesso($1.c) + $1.c + $3.c + "+" + "[=]" + "^";}
  | MAIS_MAIS Lvalue        {$$.c = limpAcesso($2.c) + $2.c + "1" + "+" + "=";}
  | MAIS_MAIS LvalueProp    {$$.c = limpAcesso($2.c) + $2.c  + "1" + "+" + "[=]";}

Lvalue : ID   {$$.c = $1.c + "@";
                verificar_variavel($1);}

LvalueProp : E '[' E ']'  {$$.c = $1.c + $3.c + "[@]";}
           | E '.' ID     {$$.c = $1.c + $3.c + "[@]";}

CMD_DECL : LET LET_VARs { $$.c = $2.c; }
        | CONST CONST_VARs {$$.c = $2.c;}
        | VAR VAR_VARs  {$$.c = $2.c;}
        ;

LET_VARs : LET_VAR ',' LET_VARs {$$.c = $1.c + $3.c;}
        | LET_VAR
        ;
        
LET_VAR :  ID  { $$.c = $1.c + "&";  insere_tabela_de_simbolos( DeclLet, $1 );}
        |  ID '=' E {$$.c = $1.c + "&" + $1.c + $3.c + "=" + "^"; insere_tabela_de_simbolos( DeclLet, $1 ); }


CONST_VARs : CONST_VAR ',' CONST_VARs {$$.c = $1.c + $3.c;}
           | CONST_VAR
           ;
CONST_VAR : ID  { $$.c = $1.c + "&";  insere_tabela_de_simbolos( DeclConst, $1 );}
           | ID '=' E {$$.c = $1.c + "&" + $1.c + $3.c + "=" + "^"; insere_tabela_de_simbolos( DeclConst, $1 ); }


VAR_VARs : VAR_VAR ',' VAR_VARs {$$.c = $1.c + $3.c;}
         | VAR_VAR
         ;

VAR_VAR : ID      { $$.c = $1.c + "&";  insere_tabela_de_simbolos( DeclVar, $1 );}
        | ID '=' E {$$.c = $1.c + "&" + $1.c + $3.c + "=" + "^"; insere_tabela_de_simbolos( DeclVar, $1 ); }

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

CMD_FOR : FOR '(' CMD  E ';' E ')' CMD            //TROCAR CMD POR IN_FOR TALVEZ
        {
          string inicio_for = gera_label("inicio_for");
          string fim_for = gera_label("fim_for");
          string definicao_inicio_for = ":" + inicio_for;
          string definicao_fim_for = ":" + fim_for;

          $$.c = $3.c + $4.c + 
              inicio_for + "?" +     //Entra no for?
              fim_for + "#" +
              definicao_inicio_for + 
              $8.c + $6.c  + "^" + $4.c + 
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

E : E '<' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '>' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '+' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '-' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '*' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '/' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '%' E   { $$.c = $1.c + $3.c + $2.c; }
  | E IGUAL E { $$.c = $1.c + $3.c + "=="; }
  | Lvalue '=' E {$$.c = limpAcesso($1.c) + $3.c + "="; verificar_const($1);}
  | LvalueProp '=' E {$$.c = limpAcesso($1.c) + $3.c + "[=]";}
  | Lvalue MAIS_IGUAL E {$$.c = limpAcesso($1.c) + $1.c + $3.c + "+" + "=";}
  | LvalueProp MAIS_IGUAL E {$$.c = limpAcesso($1.c) + $1.c + $3.c + "+" + "[=]";}
  | Lvalue  
  | LvalueProp
  | MAIS_MAIS Lvalue      {$$.c = limpAcesso($2.c) + $2.c + "1" + "+" + "=";}
  | MAIS_MAIS LvalueProp  {$$.c = limpAcesso($2.c) + $2.c  + "1" + "+" + "[=]";};
  | Lvalue MAIS_MAIS      {$$.c = $1.c + limpAcesso($1.c) + $1.c + "1" + "+" + "=" + "^";}        
  | LvalueProp MAIS_MAIS  {$$.c = $1.c + limpAcesso($1.c) + $1.c + "1" + "+" + "[=]" + "^";}; 
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