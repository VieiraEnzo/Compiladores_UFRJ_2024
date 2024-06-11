%{
int token( int tk );

vector<string> tokeniza(string lexema){
    vector<string> aux;
    int i = 0, inicio = 0;
    
    for(; i < lexema.size(); i++){
        if(lexema[i] == ' '){
            aux.push_back(lexema.substr(inicio, i-inicio));
            inicio = ++i;
        }
    }
    
    aux.push_back(lexema.substr(inicio, i-inicio));

    return aux;
}

void limpaVazio(char *str){
  char *src = str, *dst = str;
  while (*src) {
      if(*src == '\t') { coluna+= 4; }
      else if(*src == ' ') { coluna++; }
      else if(*src == '\n') { linha++; coluna = 1; }
      else{
          *dst++ = *src;
      }
      src++;
    }
  *dst = '\0';
}

%}

D  	        [0-9]
L   	      [A-Za-z_]
INT	        {D}+
DOUBLE      {D}+"."{D}+([Ee][+\-]?{D}+)?
ID          {L}({L}|{D})*
STRING      \"([^"\n]|\"\"|\\\")*\"
STRING2      \'([^'\n]|\'\'|\\\')*\'
VAZIO       [ \t\n]*

%%

"\t"       { coluna += 4; }
" "        { coluna++; }
"\n"	   { linha++; coluna = 1; }

{DOUBLE}   { return token( CDOUBLE ); }
{INT}	   { return token( CINT ); }
{STRING}   { return token( CSTRING ); }
{STRING2}   { return token( CSTRING ); }

"&&"	   { return token( AND ); }
"||"	   { return token( OR ); }
"<="	   { return token( ME_IG ); }
">="	   { return token( MA_IG ); }
"!="	   { return token( DIF ); }
"=="	   { return token( IGUAL ); }
"=>"     { return token( SETA ); }
")"{VAZIO}"=>" { return token( PARENTESES_FUNCAO ); }

"+="       { return token( MAIS_IGUAL ); }
"++"       { return token( MAIS_MAIS ); }

"if"       { return token( IF ); }
"else"     { return token( ELSE ); }
"else if"     { return token( ELSE_IF ); }

"asm{".*"}"  {  string s = yytext;
                string lexema = s.substr(4);
                lexema.pop_back(); 
                yylval.c = tokeniza( lexema );
                coluna += strlen( yytext ); 
                return ASM; }

"for"     { return token( FOR ); }
"while"   { return token( WHILE ); }

"let"     { return token( LET ); }
"const"   { return token( CONST ); }
"var"     { return token( VAR ); }
"function" {return token( FUNCTION );}
"return" {return token( RETURN );}
"true"  {return token( BOOLEAN );}
"false"  {return token( BOOLEAN );}

{ID}       { return token( ID ); }

.          { return token( *yytext ); }

%%

int token( int tk ) {  
  yylval.c = vector<string>{ yytext };
  coluna += strlen( yytext ); 
  
  yylval.linha = linha;
  yylval.coluna = coluna;

  return tk;
}