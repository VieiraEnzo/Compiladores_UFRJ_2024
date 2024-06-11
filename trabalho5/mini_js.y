%{
#include <iostream>
#include <string>
#include <vector>
#include <map>

//A COMPLETAR
//1 - reconhecer [] e {} com quebra de linha dentro (RESOLVIDO NO LEX)
//2- Reconhecer MAIS_MAIS
//3- Completar declaração de argumentos em funções
//4- Reconhecer true e false (RESOLVIDO NO LEX)
//5- Quando chamamos um simbolo dentro da função, nn devemos checa-lo (RESOLVIDO COM IN_FUNC)
//6- Não produzir codigo de re-declaração se ja declarada


using namespace std;

int linha = 1, coluna = 1; 

struct Atributos {
  vector<string> c; // Código

  int linha = 0, coluna = 0;

  int n_args = 0;

  vector<string>   valor_default; 

  void clear() {
    c.clear();
    valor_default.clear();
    linha = 0;
    coluna = 0;
    n_args = 0;
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
  bool debug = false;
  if(!debug){
    for( string s : codigo ) cout << s << " ";
    cout << endl;
  }else{
    for(int i = 0; i < codigo.size(); i++) 
      cout << i << ": " << codigo[i] << "\n";
  }
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

int in_func = 0;  
vector< map< string, Var > > ts = { map< string, Var >{} };
vector<string> funcoes;



#define YYSTYPE Atributos

// Dispara um erro se não pode declarar.

bool insere_tabela_de_simbolos( TipoDecl tipo, Atributos at ){

  string nome = at.c[0];
  int linha = at.linha;
  int coluna = at.coluna;

  if( ts.back().count(nome) > 0 ){

      TipoDecl tipoDaVar = ts.back()[nome].tipo;
      if(!(tipoDaVar == tipo && tipo == DeclVar)){
            cout << "Erro: a variável '" << nome <<"' já foi declarada na linha " << ts.back()[nome].linha << ".\n";
            exit(1);
      }
      return true;

  }else{
      Var k;
      k.tipo = tipo;
      k.linha = linha;
      k.coluna = coluna;
      ts.back()[nome] = k;
      return false;
  }

}

void verificar_variavel(Atributos at, bool modificavel){

  string nome = at.c[0];
  for( int i = ts.size() - 1; i >= 0; i-- ) {  
    auto& atual = ts[i];

    if( atual.count( nome ) > 0 ) {
      if( modificavel && atual[nome].tipo == DeclConst ) {
        cout << "Erro: tentativa de modificar uma variável constante '" << nome << "'' .\n";
        exit( 1 );     
      }
      else 
        return;
    }
  }

  if(in_func) return;
  cout << "in_func = " << in_func << "\n"; 
  cout << "Erro: a variável '" << nome << "' não foi declarada.\n";
  exit(1);
}

%}

%token ID IF ELSE ELSE_IF
%token CDOUBLE CSTRING CINT
%token AND OR ME_IG MA_IG DIF IGUAL
%token MAIS_IGUAL MAIS_MAIS
%token NEWOBJECT NEWARRAY 
%token FOR WHILE
%token LET CONST VAR FUNCTION
%token ASM RETURN BOOLEAN SETA
%token PARENTESES_FUNCAO

%right '=' SETA
%left OR
%left AND
%nonassoc '<' '>' ME_IG MA_IG IGUAL DIF
%left '+' '-'
%left '*' '/' '%'
%left MAIS_IGUAL 
%nonassoc MAIS_MAIS
%right '[' '('
%left '.'


%%

S : CMDs { print( resolve_enderecos( $1.c + "."  + funcoes) ); }
  ;

CMDs  : CMDs CMD {$$.c = $1.c + $2.c;};
      |   {$$.clear();}
      ;

CMD : CMD_DECL ';'
    | CMD_IF
    | CMD_FOR
    | CMD_WHILE
    | CMD_FUNC  
    | RETURN E ';' {$$.c = $2.c + "'&retorno'" + "@"+ "~";}
    | E ';' { $$.c = $1.c + "^"; };
    | E ASM ';' {$$.c = $1.c + $2.c + "^";}
    | '{' EMPILHA_TS CMDs '}' {
          ts.pop_back();
          $$.c = "<{" +  $3.c  + "}>";}
    | ';' {$$.clear();}
    ;

EMPILHA_TS : { ts.push_back( map< string, Var >{} ); } 
           ;
    
CMD_FUNC : FUNCTION ID { in_func++; insere_tabela_de_simbolos( DeclVar, $2 ); } 
             '(' EMPILHA_TS LISTA_PARAMs ')' '{' CMDs '}'
           {
            in_func--;
             string lbl_endereco_funcao = gera_label( "func_" + $2.c[0] );
             string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
             
             $$.c = $2.c + "&" + $2.c + "{}"  + "=" + "'&funcao'" +
                    lbl_endereco_funcao + "[=]" + "^";
             funcoes = funcoes + definicao_lbl_endereco_funcao + $6.c + $9.c +
                       "undefined" + "@" + "'&retorno'" + "@"+ "~";
             ts.pop_back();
           }
         ;
         
LISTA_PARAMs : PARAMs
           | { $$.c.clear(); }
           ;
           
PARAMs : PARAMs ',' PARAM  
       { 
         $$.c = $1.c + $3.c + "&" + $3.c + "arguments" + "@" + to_string( $1.n_args )
                + "[@]" + "=" + "^"; 
                
         if( $3.valor_default.size() > 0 ) {
       
            string lbl_true = gera_label( "lbl_true" );
            string lbl_fim_if = gera_label( "lbl_fim_if" );
            string definicao_lbl_true = ":" + lbl_true;
            string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
           $$.c = $$.c + $3.c + "@" + "undefined" + "@" + "==" +                   // Codigo da expressão
                   lbl_true + "?" +                                       // Código do IF
                   lbl_fim_if + "#" +                                     // Código do False
                   definicao_lbl_true + "<{" + $3.c + $3.valor_default + "=" + "^" + "}>" +   // Código do True
                   definicao_lbl_fim_if                                   // Fim do IF
                   ;
         }
         $$.n_args = $1.n_args + $3.n_args; 
       }
     | PARAM 
       {  
         $$.c = $1.c + "&" + $1.c + "arguments" + "@" + "0" + "[@]" + "=" + "^"; 
                
         if( $1.valor_default.size() > 0 ) {
       
            string lbl_true = gera_label( "lbl_true" );
            string lbl_fim_if = gera_label( "lbl_fim_if" );
            string definicao_lbl_true = ":" + lbl_true; 
            string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
             $$.c = $$.c + $1.c + "@" + "undefined" + "@" + "==" +                   // Codigo da expressão
                   lbl_true + "?" +                                       // Código do IF
                   lbl_fim_if + "#" +                                     // Código do False
                   definicao_lbl_true + "<{" + $1.c + $1.valor_default + "=" + "^" + "}>" +   // Código do True
                   definicao_lbl_fim_if                                   // Fim do IF
                   ;

         }
         $$.n_args = $1.n_args; 
       }
     ;  
     
PARAM : ID 
      { $$.c = $1.c;      
        $$.n_args = 1;
        $$.valor_default.clear();
        insere_tabela_de_simbolos( DeclLet, $1 );
      }
    | ID '=' E
      { 
        $$.c = $1.c;
        $$.n_args = 1;
        $$.valor_default = $3.c; 
        insere_tabela_de_simbolos( DeclLet, $1 );
        }
    ;

Lvalue : ID   {$$.c = $1.c + "@";
                verificar_variavel($1, false);}
          ;

LvalueProp : E '[' E ']'  {$$.c = $1.c + $3.c + "[@]";}
           | E '.' ID     {$$.c = $1.c + $3.c + "[@]";}
           ;

CMD_DECL : LET LET_VARs { $$.c = $2.c; }
        | CONST CONST_VARs {$$.c = $2.c;}
        | VAR VAR_VARs  {$$.c = $2.c;}
        ;

LET_VARs : LET_VAR ',' LET_VARs {$$.c = $1.c + $3.c;}
        | LET_VAR
        ;
        
LET_VAR :  ID  {if(!insere_tabela_de_simbolos( DeclLet, $1)) $$.c = $1.c + "&";}
        |  ID '=' E {if(!insere_tabela_de_simbolos( DeclLet, $1 )) $$.c = $1.c + "&" + $1.c + $3.c + "=" + "^";
                      else $$.c = $1.c + $3.c + "=" + "^"; }
        ;

CONST_VARs : CONST_VAR ',' CONST_VARs {$$.c = $1.c + $3.c;}
           | CONST_VAR
           ;

CONST_VAR : ID  { if(!insere_tabela_de_simbolos( DeclConst, $1)) $$.c = $1.c + "&";}
           | ID '=' E {if(!insere_tabela_de_simbolos( DeclConst, $1 )) $$.c = $1.c + "&" + $1.c + $3.c + "=" + "^";
                        else $$.c = $1.c + $3.c + "=" + "^"; }
           ;


VAR_VARs : VAR_VAR ',' VAR_VARs {$$.c = $1.c + $3.c;}
         | VAR_VAR
         ;

VAR_VAR : ID    { if(!insere_tabela_de_simbolos( DeclVar, $1)) $$.c = $1.c + "&";}
        | ID '=' E {if(!insere_tabela_de_simbolos( DeclVar, $1 )) $$.c = $1.c + "&" + $1.c + $3.c + "=" + "^";
                     else $$.c = $1.c + $3.c + "=" + "^"; }
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

E : Lvalue '=' E {$$.c = limpAcesso($1.c) + $3.c + "="; verificar_variavel($1, true);}
  | LvalueProp '=' E {$$.c = limpAcesso($1.c) + $3.c + "[=]";}
  | Lvalue MAIS_IGUAL E {$$.c = limpAcesso($1.c) + $1.c + $3.c + "+" + "=";}
  | LvalueProp MAIS_IGUAL E {$$.c = limpAcesso($1.c) + $1.c + $3.c + "+" + "[=]";}
  // | MAIS_MAIS Lvalue      {$$.c = limpAcesso($2.c) + $2.c + "1" + "+" + "=";}
  // | MAIS_MAIS LvalueProp  {$$.c = limpAcesso($2.c) + $2.c  + "1" + "+" + "[=]";}
  | Lvalue MAIS_MAIS      {$$.c = $1.c + limpAcesso($1.c) + $1.c + "1" + "+" + "=" + "^";}        
  | LvalueProp MAIS_MAIS  {$$.c = $1.c + limpAcesso($1.c) + $1.c + "1" + "+" + "[=]" + "^";}; 
  |E '<' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '>' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '+' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '-' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '*' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '/' E   { $$.c = $1.c + $3.c + $2.c; }
  | E '%' E   { $$.c = $1.c + $3.c + $2.c; }
  | E IGUAL E { $$.c = $1.c + $3.c + "=="; }
  | E '(' LISTA_ARGs ')'
    {
      $$.c = $3.c + to_string( $3.n_args ) + $1.c + "$";
    }
  //Function (FARGS) {CMDS}        -Usar as mesamas coisa que usamos para gerar codigo de função
  //(FARGS) => {CMDS}              -menos, declar um objeto de função. Para isso, usaremos [<=], nova
  //(FARGS) => E (Pd causar confl) -função que, na expressão a[b] = c, retorna o objeto a em vez de 'c'
  //(FARGS Parenteses_Função => E
  //id => {CMDS}
  | ID EMPILHA_TS SETA { in_func++; } E 
      {
              in_func--;    
              string lbl_endereco_funcao = gera_label( "func_" + $1.c[0] );
              string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;

              $$.clear();
              $$.c = $$.c + "{}" + "'&funcao'" + lbl_endereco_funcao + "[<=]" + "^";
              funcoes = funcoes + definicao_lbl_endereco_funcao + 
              $1.c + "&" + $1.c + "arguments" + "@" + "0" + "[@]" + "=" + "^" +   //Gera parametro
              $5.c  + "'&retorno'" + "@"+ "~";                 //CMDs e retorno
              ts.pop_back();
      }
  | ID EMPILHA_TS SETA '{' { in_func++; } CMDs '}' 
    { 
              in_func--;    
              string lbl_endereco_funcao = gera_label( "func_" + $1.c[0] );
              string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;

              $$.clear();
              $$.c = $$.c + "{}" + "'&funcao'" + lbl_endereco_funcao + "[<=]" + "^";
              funcoes = funcoes + definicao_lbl_endereco_funcao + 
              $1.c + "&" + $1.c + "arguments" + "@" + "0" + "[@]" + "=" + "^" +   //Gera parametro
              $6.c  + "'&retorno'" + "@"+ "~";                 //CMDs e retorno
              ts.pop_back();
    }
  | Lvalue  
  | LvalueProp
  | CDOUBLE
  | CINT
  | CSTRING
  | '[' ']' {$$.clear(); $$.c = $$.c + "[]";}
  | '-' E {$$.c = "0" + $2.c + "-";}
  | NEWARRAY
  | BOOLEAN
  | '(' E ')' {$$.c = $2.c;}
  | Lvalue '=' '{' '}' { $$.c = limpAcesso($1.c) + "{}" + "="; verificar_variavel($1, true);}
  | '(' '{' '}' ')' { $$.clear(); $$.c =  $$.c + "{}"; }
  // | '{' Campos '}'  { $$.c = $2.c; }  //não sabe se é bloco ou objeto
  | '[' ELEMENTOS ']' {$$.c = "[]" + $2.c;}
  ;

//FARGS : FARG , FARGS
      //| FARG

//FARG : ID
      //| LAVUE = E
      //| 

// Campos : Campo ',' Campos {$$.c = $1.c + $3.c;}
//         |Campo
  
// Campo : ID ':' E  {$$.c = $1.c + $3.c + "[<=]";}
  
ELEMENTOS : ELEMENTOS ',' ELEMENTO 
      {
          $$.c = $1.c + $3.c + to_string( $1.n_args ) + "[<=]"; 
          $$.n_args = $1.n_args + $3.n_args;
      }
          | ELEMENTO  
      {
          $$.c = $1.c + "0" +  "[<=]"; 
          $$.n_args = $1.n_args;
      }
          ; 

ELEMENTO: CDOUBLE {$$.c = $1.c;  $$.n_args = 1;}
        | CINT  {$$.c = $1.c;  $$.n_args = 1;}
        | CSTRING {$$.c = $1.c;  $$.n_args = 1;}
        ;

LISTA_ARGs : ARGs {$$.c = $1.c; $$.n_args = $1.n_args;}
           | { $$.clear(); }
           ;
             
ARGs : ARGs ',' E
       { $$.c = $1.c + $3.c;
         $$.n_args = $1.n_args + 1; 
        }
     | E
       { $$.c = $1.c;
         $$.n_args = 1; }
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