%{
int token( int tk );
%}

D  	        [0-9]
L   	    [A-Za-z_]
INT	        {D}+
DOUBLE      {D}+"."{D}+([Ee][+\-]?{D}+)?
ID          {L}({L}|{D})*
STRING      \"([^"\n]|\"\"|\\\")*\"
STRING2      \'([^'\n]|\'\'|\\\')*\'

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

"+="       { return token( MAIS_IGUAL ); }
"++"       { return token( MAIS_MAIS ); }

"if"       { return token( IF ); }
"else"     { return token( ELSE ); }
"else if"     { return token( ELSE_IF ); }
"print"    { return token( PRINT ); }

"for"     { return token( FOR ); }
"while"   { return token( WHILE ); }

"let"     { return token( LET ); }
"const"   { return token( CONST ); }
"var"     { return token( VAR ); }

"{}"       { return token( NEWOBJECT ); }
"[]"       { return token( NEWARRAY ); }

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