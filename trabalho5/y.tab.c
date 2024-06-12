/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "mini_js.y"

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
  cout << "Erro: a variável '" << nome << "' não foi declarada.\n";
  exit(1);
}


#line 239 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ID = 258,                      /* ID  */
    IF = 259,                      /* IF  */
    ELSE = 260,                    /* ELSE  */
    ELSE_IF = 261,                 /* ELSE_IF  */
    CDOUBLE = 262,                 /* CDOUBLE  */
    CSTRING = 263,                 /* CSTRING  */
    CINT = 264,                    /* CINT  */
    AND = 265,                     /* AND  */
    OR = 266,                      /* OR  */
    ME_IG = 267,                   /* ME_IG  */
    MA_IG = 268,                   /* MA_IG  */
    DIF = 269,                     /* DIF  */
    IGUAL = 270,                   /* IGUAL  */
    MAIS_IGUAL = 271,              /* MAIS_IGUAL  */
    MAIS_MAIS = 272,               /* MAIS_MAIS  */
    NEWOBJECT = 273,               /* NEWOBJECT  */
    NEWARRAY = 274,                /* NEWARRAY  */
    FOR = 275,                     /* FOR  */
    WHILE = 276,                   /* WHILE  */
    LET = 277,                     /* LET  */
    CONST = 278,                   /* CONST  */
    VAR = 279,                     /* VAR  */
    FUNCTION = 280,                /* FUNCTION  */
    ASM = 281,                     /* ASM  */
    RETURN = 282,                  /* RETURN  */
    BOOLEAN = 283,                 /* BOOLEAN  */
    SETA = 284,                    /* SETA  */
    PARENTESES_FUNCAO = 285        /* PARENTESES_FUNCAO  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ID 258
#define IF 259
#define ELSE 260
#define ELSE_IF 261
#define CDOUBLE 262
#define CSTRING 263
#define CINT 264
#define AND 265
#define OR 266
#define ME_IG 267
#define MA_IG 268
#define DIF 269
#define IGUAL 270
#define MAIS_IGUAL 271
#define MAIS_MAIS 272
#define NEWOBJECT 273
#define NEWARRAY 274
#define FOR 275
#define WHILE 276
#define LET 277
#define CONST 278
#define VAR 279
#define FUNCTION 280
#define ASM 281
#define RETURN 282
#define BOOLEAN 283
#define SETA 284
#define PARENTESES_FUNCAO 285

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_IF = 4,                         /* IF  */
  YYSYMBOL_ELSE = 5,                       /* ELSE  */
  YYSYMBOL_ELSE_IF = 6,                    /* ELSE_IF  */
  YYSYMBOL_CDOUBLE = 7,                    /* CDOUBLE  */
  YYSYMBOL_CSTRING = 8,                    /* CSTRING  */
  YYSYMBOL_CINT = 9,                       /* CINT  */
  YYSYMBOL_AND = 10,                       /* AND  */
  YYSYMBOL_OR = 11,                        /* OR  */
  YYSYMBOL_ME_IG = 12,                     /* ME_IG  */
  YYSYMBOL_MA_IG = 13,                     /* MA_IG  */
  YYSYMBOL_DIF = 14,                       /* DIF  */
  YYSYMBOL_IGUAL = 15,                     /* IGUAL  */
  YYSYMBOL_MAIS_IGUAL = 16,                /* MAIS_IGUAL  */
  YYSYMBOL_MAIS_MAIS = 17,                 /* MAIS_MAIS  */
  YYSYMBOL_NEWOBJECT = 18,                 /* NEWOBJECT  */
  YYSYMBOL_NEWARRAY = 19,                  /* NEWARRAY  */
  YYSYMBOL_FOR = 20,                       /* FOR  */
  YYSYMBOL_WHILE = 21,                     /* WHILE  */
  YYSYMBOL_LET = 22,                       /* LET  */
  YYSYMBOL_CONST = 23,                     /* CONST  */
  YYSYMBOL_VAR = 24,                       /* VAR  */
  YYSYMBOL_FUNCTION = 25,                  /* FUNCTION  */
  YYSYMBOL_ASM = 26,                       /* ASM  */
  YYSYMBOL_RETURN = 27,                    /* RETURN  */
  YYSYMBOL_BOOLEAN = 28,                   /* BOOLEAN  */
  YYSYMBOL_SETA = 29,                      /* SETA  */
  YYSYMBOL_PARENTESES_FUNCAO = 30,         /* PARENTESES_FUNCAO  */
  YYSYMBOL_31_ = 31,                       /* '='  */
  YYSYMBOL_32_ = 32,                       /* '<'  */
  YYSYMBOL_33_ = 33,                       /* '>'  */
  YYSYMBOL_34_ = 34,                       /* '+'  */
  YYSYMBOL_35_ = 35,                       /* '-'  */
  YYSYMBOL_36_ = 36,                       /* '*'  */
  YYSYMBOL_37_ = 37,                       /* '/'  */
  YYSYMBOL_38_ = 38,                       /* '%'  */
  YYSYMBOL_39_ = 39,                       /* '['  */
  YYSYMBOL_40_ = 40,                       /* '('  */
  YYSYMBOL_41_ = 41,                       /* '.'  */
  YYSYMBOL_42_ = 42,                       /* ';'  */
  YYSYMBOL_43_ = 43,                       /* '{'  */
  YYSYMBOL_44_ = 44,                       /* '}'  */
  YYSYMBOL_45_ = 45,                       /* ')'  */
  YYSYMBOL_46_ = 46,                       /* ','  */
  YYSYMBOL_47_ = 47,                       /* ']'  */
  YYSYMBOL_48_ = 48,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_S = 50,                         /* S  */
  YYSYMBOL_CMDs = 51,                      /* CMDs  */
  YYSYMBOL_CMD = 52,                       /* CMD  */
  YYSYMBOL_EMPILHA_TS = 53,                /* EMPILHA_TS  */
  YYSYMBOL_CMD_FUNC = 54,                  /* CMD_FUNC  */
  YYSYMBOL_55_1 = 55,                      /* $@1  */
  YYSYMBOL_LISTA_PARAMs = 56,              /* LISTA_PARAMs  */
  YYSYMBOL_PARAMs = 57,                    /* PARAMs  */
  YYSYMBOL_PARAM = 58,                     /* PARAM  */
  YYSYMBOL_Lvalue = 59,                    /* Lvalue  */
  YYSYMBOL_LvalueProp = 60,                /* LvalueProp  */
  YYSYMBOL_CMD_DECL = 61,                  /* CMD_DECL  */
  YYSYMBOL_LET_VARs = 62,                  /* LET_VARs  */
  YYSYMBOL_LET_VAR = 63,                   /* LET_VAR  */
  YYSYMBOL_CONST_VARs = 64,                /* CONST_VARs  */
  YYSYMBOL_CONST_VAR = 65,                 /* CONST_VAR  */
  YYSYMBOL_VAR_VARs = 66,                  /* VAR_VARs  */
  YYSYMBOL_VAR_VAR = 67,                   /* VAR_VAR  */
  YYSYMBOL_CMD_WHILE = 68,                 /* CMD_WHILE  */
  YYSYMBOL_CMD_FOR = 69,                   /* CMD_FOR  */
  YYSYMBOL_CMD_IF = 70,                    /* CMD_IF  */
  YYSYMBOL_CMD_ELSE = 71,                  /* CMD_ELSE  */
  YYSYMBOL_E = 72,                         /* E  */
  YYSYMBOL_73_2 = 73,                      /* $@2  */
  YYSYMBOL_74_3 = 74,                      /* $@3  */
  YYSYMBOL_75_4 = 75,                      /* $@4  */
  YYSYMBOL_FARGS = 76,                     /* FARGS  */
  YYSYMBOL_77_5 = 77,                      /* $@5  */
  YYSYMBOL_FARG = 78,                      /* FARG  */
  YYSYMBOL_OBJ = 79,                       /* OBJ  */
  YYSYMBOL_List_Campos = 80,               /* List_Campos  */
  YYSYMBOL_Campos = 81,                    /* Campos  */
  YYSYMBOL_Campo = 82,                     /* Campo  */
  YYSYMBOL_ELEMENTOS = 83,                 /* ELEMENTOS  */
  YYSYMBOL_ELEMENTO = 84,                  /* ELEMENTO  */
  YYSYMBOL_LISTA_ARGs = 85,                /* LISTA_ARGs  */
  YYSYMBOL_ARGs = 86                       /* ARGs  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   519

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  104
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  203

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   285


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    38,     2,     2,
      40,    45,    36,    34,    46,    35,    41,    37,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    48,    42,
      32,    31,    33,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    39,     2,    47,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,    44,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   193,   193,   196,   197,   200,   201,   202,   203,   204,
     205,   209,   214,   215,   216,   219,   222,   225,   225,   240,
     241,   244,   265,   288,   294,   303,   307,   308,   311,   312,
     313,   316,   317,   320,   321,   323,   327,   328,   331,   332,
     337,   338,   341,   342,   346,   362,   378,   392,   405,   406,
     410,   411,   412,   413,   414,   417,   418,   419,   420,   421,
     422,   423,   424,   425,   426,   427,   431,   431,   443,   443,
     457,   469,   469,   480,   481,   482,   483,   484,   485,   486,
     487,   488,   489,   490,   493,   515,   515,   538,   545,   552,
     560,   563,   564,   567,   568,   571,   572,   576,   581,   588,
     589,   592,   593,   596,   600
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "IF", "ELSE",
  "ELSE_IF", "CDOUBLE", "CSTRING", "CINT", "AND", "OR", "ME_IG", "MA_IG",
  "DIF", "IGUAL", "MAIS_IGUAL", "MAIS_MAIS", "NEWOBJECT", "NEWARRAY",
  "FOR", "WHILE", "LET", "CONST", "VAR", "FUNCTION", "ASM", "RETURN",
  "BOOLEAN", "SETA", "PARENTESES_FUNCAO", "'='", "'<'", "'>'", "'+'",
  "'-'", "'*'", "'/'", "'%'", "'['", "'('", "'.'", "';'", "'{'", "'}'",
  "')'", "','", "']'", "':'", "$accept", "S", "CMDs", "CMD", "EMPILHA_TS",
  "CMD_FUNC", "$@1", "LISTA_PARAMs", "PARAMs", "PARAM", "Lvalue",
  "LvalueProp", "CMD_DECL", "LET_VARs", "LET_VAR", "CONST_VARs",
  "CONST_VAR", "VAR_VARs", "VAR_VAR", "CMD_WHILE", "CMD_FOR", "CMD_IF",
  "CMD_ELSE", "E", "$@2", "$@3", "$@4", "FARGS", "$@5", "FARG", "OBJ",
  "List_Campos", "Campos", "Campo", "ELEMENTOS", "ELEMENTO", "LISTA_ARGs",
  "ARGs", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-70)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-90)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -70,    18,   275,   -70,    -9,    -4,   -70,   -70,   -70,    -3,
       1,    26,    39,    40,    -2,   284,   -70,   136,    72,   313,
     -70,   -70,   -70,   -70,    -1,    15,     2,   -70,   -70,   -70,
     422,   -70,   136,   275,   136,    14,   -70,     3,    16,   -70,
      10,    21,   -70,    20,   -70,   -70,    27,    65,   434,    31,
      84,   -70,   462,   -70,   -33,   -70,   -20,    23,   325,   -19,
     -70,    32,   -70,   136,   -70,   284,   136,   -70,   136,   -70,
     136,    36,   136,   136,   136,   136,   136,   136,   136,   136,
     136,    79,   -70,    41,   339,   136,   353,   284,    26,   136,
      39,   136,    40,    43,   -70,    37,    45,   -70,    44,   -70,
     -70,   284,   -70,   284,   -70,    58,    88,   -70,   -70,   159,
     -17,   462,   -70,   -17,   462,   478,   -70,   478,   478,    84,
      84,   -17,   -17,   -17,   296,   462,    47,    48,   -70,   136,
      53,   275,   450,   275,   462,   -70,   -70,   462,   -70,   462,
     -70,   -70,    95,   284,   -70,    65,   -70,   367,   -18,   136,
      68,    70,   -70,   -70,   -70,   -70,   -70,   136,   462,   -70,
      28,   136,   -70,    95,    71,    61,    62,   -70,   462,   -70,
     -70,   462,   284,   462,   188,   275,    73,   -70,   381,    81,
     136,    67,    95,   462,   -70,   -70,   -70,   136,   275,    74,
     462,   -70,   -70,   395,   -70,   -70,   217,   275,   246,   -70,
      28,   -70,   -70
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,    25,     0,    75,    77,    76,     0,
       0,     0,     0,     0,     0,     0,    78,     0,     0,     0,
      15,    16,     3,     9,    73,    74,     0,     8,     7,     6,
       0,    16,     0,     0,     0,    33,    28,    32,    38,    29,
      37,    42,    30,    41,    17,    71,     0,    92,     0,     0,
      79,    80,    99,   100,     0,    98,    25,    73,     0,     0,
      16,     0,     4,     0,    55,     0,     0,    56,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     102,     0,    12,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,     0,     0,    91,    94,    10,
      11,     0,    81,     0,    82,     0,     0,    85,    83,     0,
      53,    51,    50,    54,    52,    64,    13,    57,    58,    59,
      60,    61,    62,    63,     0,   104,     0,   101,    27,     0,
       0,     0,     0,     0,    34,    35,    31,    39,    36,    43,
      40,    16,    20,     0,    90,     0,    97,    88,    50,     0,
      87,     0,    84,    86,    14,    26,    65,     0,    67,     4,
      49,     0,    44,    20,    23,     0,    19,    22,    95,    96,
      93,    70,     0,   103,     0,     0,     0,    46,     0,     0,
       0,     0,     0,    88,    89,    69,    48,     0,     0,     0,
      24,     4,    21,     0,    45,     4,     0,     0,     0,    72,
      49,    18,    47
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -70,   -70,   -55,   -28,   -25,   -70,   -70,   -45,   -70,   -53,
     -11,   -70,   -70,    42,   -70,    51,   -70,    35,   -70,   -70,
     -70,   -70,   -69,   -15,   -70,   -70,   -70,   -70,   -70,    29,
       6,   -70,   -13,   -70,   -70,    49,   -70,   -70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    22,    62,    23,    93,   165,   166,   167,
      24,    25,    26,    36,    37,    39,    40,    42,    43,    27,
      28,    29,   177,    30,   129,   130,    94,    59,   153,    60,
      53,    96,    97,    98,    54,    55,   126,   127
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,    44,    50,    52,    58,    85,    83,   109,    57,    31,
     -87,   105,   -89,   101,   102,    63,    64,    84,     3,    86,
      31,    49,    79,    80,    81,    61,   -87,   106,   -89,    35,
      65,    66,    67,   175,   176,   107,    32,    33,    45,    63,
      64,    34,    38,    41,    69,    87,    68,    89,   110,    88,
     111,   113,    91,   114,   103,   115,    90,   117,   118,   119,
     120,   121,   122,   123,   124,   125,    92,    45,    95,   142,
     132,   112,   134,   100,   137,     4,   139,   108,   116,     6,
       7,     8,   128,   141,   -68,   143,    52,   149,   147,   144,
     145,   150,   156,   135,   157,   151,   159,    46,   164,   -25,
      16,   172,   180,   160,   174,   162,   181,    17,   182,   148,
     191,    18,    19,   187,   158,    47,   163,   195,   179,    51,
      76,    77,    78,    79,    80,    81,   189,   140,   168,   192,
     136,   202,   170,     0,   171,   152,   196,     0,     0,     4,
     198,   138,   173,     6,     7,     8,   178,   186,     0,   169,
     146,     0,     0,     0,     0,     0,     0,   183,     0,     0,
     194,    46,     4,     5,    16,   190,     6,     7,     8,   200,
       0,    17,   193,     0,     0,    18,    19,     0,   184,     9,
      10,    11,    12,    13,    14,     0,    15,    16,     0,     0,
       0,     4,     5,     0,    17,     6,     7,     8,    18,    19,
       0,    20,    21,   154,     0,     0,     0,     0,     9,    10,
      11,    12,    13,    14,     0,    15,    16,     0,     0,     0,
       4,     5,     0,    17,     6,     7,     8,    18,    19,     0,
      20,    21,   185,     0,     0,     0,     0,     9,    10,    11,
      12,    13,    14,     0,    15,    16,     0,     0,     0,     4,
       5,     0,    17,     6,     7,     8,    18,    19,     0,    20,
      21,   199,     0,     0,     0,     0,     9,    10,    11,    12,
      13,    14,     0,    15,    16,     0,     0,     0,     4,     5,
       0,    17,     6,     7,     8,    18,    19,     4,    20,    21,
     201,     6,     7,     8,     0,     9,    10,    11,    12,    13,
      14,     0,    15,    16,     0,     0,     0,     0,     0,    46,
      17,    70,    16,     0,    18,    19,    56,    20,    21,    17,
       6,     7,     8,    18,    19,     0,     0,    47,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    46,     0,
      70,    16,     0,   155,     0,     0,     0,     0,    17,     0,
       0,     0,    18,    19,    70,     0,    47,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,     0,    70,     0,
     104,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,     0,    70,     0,   131,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,     0,    70,     0,   133,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,     0,
      70,     0,   -51,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,     0,     0,     0,   188,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    70,     0,     0,
     197,     0,     0,     0,     0,     0,     0,     0,    71,    70,
       0,     0,     0,     0,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    70,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    99,    70,     0,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,   161,   -90,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,     0,     0,     0,     0,     0,     0,
     -90,   -90,    74,    75,    76,    77,    78,    79,    80,    81
};

static const yytype_int16 yycheck[] =
{
      15,     3,    17,    18,    19,    33,    31,    62,    19,    29,
      30,    30,    30,    46,    47,    16,    17,    32,     0,    34,
      29,    15,    39,    40,    41,    19,    46,    46,    46,     3,
      31,    16,    17,     5,     6,    60,    40,    40,    40,    16,
      17,    40,     3,     3,    42,    31,    31,    31,    63,    46,
      65,    66,    31,    68,    31,    70,    46,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    46,    40,     3,    94,
      85,    65,    87,    42,    89,     3,    91,    45,    42,     7,
       8,     9,     3,    40,    43,    48,   101,    29,   103,    44,
      46,     3,    45,    87,    46,   106,    43,    25,     3,    31,
      28,    31,    31,   131,   159,   133,    45,    35,    46,   103,
      43,    39,    40,    40,   129,    43,   141,    43,   163,    47,
      36,    37,    38,    39,    40,    41,    45,    92,   143,   182,
      88,   200,   145,    -1,   149,   106,   191,    -1,    -1,     3,
     195,    90,   157,     7,     8,     9,   161,   175,    -1,   143,
     101,    -1,    -1,    -1,    -1,    -1,    -1,   172,    -1,    -1,
     188,    25,     3,     4,    28,   180,     7,     8,     9,   197,
      -1,    35,   187,    -1,    -1,    39,    40,    -1,   172,    20,
      21,    22,    23,    24,    25,    -1,    27,    28,    -1,    -1,
      -1,     3,     4,    -1,    35,     7,     8,     9,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    20,    21,
      22,    23,    24,    25,    -1,    27,    28,    -1,    -1,    -1,
       3,     4,    -1,    35,     7,     8,     9,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    20,    21,    22,
      23,    24,    25,    -1,    27,    28,    -1,    -1,    -1,     3,
       4,    -1,    35,     7,     8,     9,    39,    40,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    20,    21,    22,    23,
      24,    25,    -1,    27,    28,    -1,    -1,    -1,     3,     4,
      -1,    35,     7,     8,     9,    39,    40,     3,    42,    43,
      44,     7,     8,     9,    -1,    20,    21,    22,    23,    24,
      25,    -1,    27,    28,    -1,    -1,    -1,    -1,    -1,    25,
      35,    15,    28,    -1,    39,    40,     3,    42,    43,    35,
       7,     8,     9,    39,    40,    -1,    -1,    43,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    25,    -1,
      15,    28,    -1,    47,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    39,    40,    15,    -1,    43,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    -1,    15,    -1,
      45,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    -1,    15,    -1,    45,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    -1,    15,    -1,    45,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      15,    -1,    45,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    45,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    15,    -1,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    26,    15,
      -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    15,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    15,    -1,    -1,
      -1,    -1,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    15,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,     0,     3,     4,     7,     8,     9,    20,
      21,    22,    23,    24,    25,    27,    28,    35,    39,    40,
      42,    43,    52,    54,    59,    60,    61,    68,    69,    70,
      72,    29,    40,    40,    40,     3,    62,    63,     3,    64,
      65,     3,    66,    67,     3,    40,    25,    43,    72,    79,
      72,    47,    72,    79,    83,    84,     3,    59,    72,    76,
      78,    79,    53,    16,    17,    31,    16,    17,    31,    42,
      15,    26,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    53,    72,    52,    72,    31,    46,    31,
      46,    31,    46,    55,    75,     3,    80,    81,    82,    42,
      42,    46,    47,    31,    45,    30,    46,    53,    45,    51,
      72,    72,    79,    72,    72,    72,    42,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    85,    86,     3,    73,
      74,    45,    72,    45,    72,    79,    62,    72,    64,    72,
      66,    40,    53,    48,    44,    46,    84,    72,    79,    29,
       3,    59,    78,    77,    44,    47,    45,    46,    72,    43,
      52,    42,    52,    53,     3,    56,    57,    58,    72,    79,
      81,    72,    31,    72,    51,     5,     6,    71,    72,    56,
      31,    45,    46,    72,    79,    44,    52,    40,    45,    45,
      72,    43,    58,    72,    52,    43,    51,    45,    51,    44,
      52,    44,    71
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    55,    54,    56,
      56,    57,    57,    58,    58,    59,    60,    60,    61,    61,
      61,    62,    62,    63,    63,    63,    64,    64,    65,    65,
      66,    66,    67,    67,    68,    69,    70,    71,    71,    71,
      72,    72,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    72,    72,    73,    72,    74,    72,
      72,    75,    72,    72,    72,    72,    72,    72,    72,    72,
      72,    72,    72,    72,    76,    77,    76,    78,    78,    78,
      79,    80,    80,    81,    81,    82,    82,    83,    83,    84,
      84,    85,    85,    86,    86
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       3,     3,     2,     3,     4,     1,     0,     0,    10,     1,
       0,     3,     1,     1,     3,     1,     4,     3,     2,     2,
       2,     3,     1,     1,     3,     3,     3,     1,     1,     3,
       3,     1,     1,     3,     5,     8,     6,     6,     2,     0,
       3,     3,     3,     3,     3,     2,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     0,     5,     0,     7,
       5,     0,     9,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     3,     3,     0,     3,     1,     3,     3,
       3,     1,     0,     3,     1,     3,     3,     3,     1,     1,
       1,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* S: CMDs  */
#line 193 "mini_js.y"
         { print( resolve_enderecos( yyvsp[0].c + "."  + funcoes) ); }
#line 1607 "y.tab.c"
    break;

  case 3: /* CMDs: CMDs CMD  */
#line 196 "mini_js.y"
                 {yyval.c = yyvsp[-1].c + yyvsp[0].c;}
#line 1613 "y.tab.c"
    break;

  case 4: /* CMDs: %empty  */
#line 197 "mini_js.y"
          {yyval.clear();}
#line 1619 "y.tab.c"
    break;

  case 10: /* CMD: RETURN E ';'  */
#line 205 "mini_js.y"
                   {
          if(!in_func){ cout << "Erro: Não é permitido 'return' fora de funções.\n"; exit(1);}
          yyval.c = yyvsp[-1].c + "'&retorno'" + "@"+ "~";
        }
#line 1628 "y.tab.c"
    break;

  case 11: /* CMD: RETURN OBJ ';'  */
#line 210 "mini_js.y"
      {
        if(!in_func){ cout << "Erro: Não é permitido 'return' fora de funções.\n"; exit(1);}
        yyval.c = yyvsp[-1].c + "'&retorno'" + "@"+ "~";
      }
#line 1637 "y.tab.c"
    break;

  case 12: /* CMD: E ';'  */
#line 214 "mini_js.y"
            { yyval.c = yyvsp[-1].c + "^"; }
#line 1643 "y.tab.c"
    break;

  case 13: /* CMD: E ASM ';'  */
#line 215 "mini_js.y"
                {yyval.c = yyvsp[-2].c + yyvsp[-1].c + "^"; }
#line 1649 "y.tab.c"
    break;

  case 14: /* CMD: '{' EMPILHA_TS CMDs '}'  */
#line 216 "mini_js.y"
                              {
          ts.pop_back();
          yyval.c = "<{" +  yyvsp[-1].c  + "}>";}
#line 1657 "y.tab.c"
    break;

  case 15: /* CMD: ';'  */
#line 219 "mini_js.y"
          {yyval.clear();}
#line 1663 "y.tab.c"
    break;

  case 16: /* EMPILHA_TS: %empty  */
#line 222 "mini_js.y"
             { ts.push_back( map< string, Var >{} ); }
#line 1669 "y.tab.c"
    break;

  case 17: /* $@1: %empty  */
#line 225 "mini_js.y"
                       { in_func++; insere_tabela_de_simbolos( DeclVar, yyvsp[0] ); }
#line 1675 "y.tab.c"
    break;

  case 18: /* CMD_FUNC: FUNCTION ID $@1 '(' EMPILHA_TS LISTA_PARAMs ')' '{' CMDs '}'  */
#line 227 "mini_js.y"
           {
             in_func--;
             string lbl_endereco_funcao = gera_label( "func_" + yyvsp[-8].c[0] );
             string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
             
             yyval.c = yyvsp[-8].c + "&" + yyvsp[-8].c + "{}"  + "=" + "'&funcao'" +
                    lbl_endereco_funcao + "[=]" + "^";
             funcoes = funcoes + definicao_lbl_endereco_funcao + yyvsp[-4].c + yyvsp[-1].c +
                       "undefined" + "@" + "'&retorno'" + "@"+ "~";
             ts.pop_back();
           }
#line 1691 "y.tab.c"
    break;

  case 20: /* LISTA_PARAMs: %empty  */
#line 241 "mini_js.y"
             { yyval.c.clear(); }
#line 1697 "y.tab.c"
    break;

  case 21: /* PARAMs: PARAMs ',' PARAM  */
#line 245 "mini_js.y"
       { 
         yyval.c = yyvsp[-2].c + yyvsp[0].c + "&" + yyvsp[0].c + "arguments" + "@" + to_string( yyvsp[-2].n_args )
                + "[@]" + "=" + "^"; 
                
         if( yyvsp[0].valor_default.size() > 0 ) {
       
            string lbl_true = gera_label( "lbl_true" );
            string lbl_fim_if = gera_label( "lbl_fim_if" );
            string definicao_lbl_true = ":" + lbl_true;
            string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
           yyval.c = yyval.c + yyvsp[0].c + "@" + "undefined" + "@" + "==" +                   // Codigo da expressão
                   lbl_true + "?" +                                       // Código do IF
                   lbl_fim_if + "#" +                                     // Código do False
                   definicao_lbl_true + "<{" + yyvsp[0].c + yyvsp[0].valor_default + "=" + "^" + "}>" +   // Código do True
                   definicao_lbl_fim_if                                   // Fim do IF
                   ;
         }
         yyval.n_args = yyvsp[-2].n_args + yyvsp[0].n_args; 
       }
#line 1722 "y.tab.c"
    break;

  case 22: /* PARAMs: PARAM  */
#line 266 "mini_js.y"
       {  
         yyval.c = yyvsp[0].c + "&" + yyvsp[0].c + "arguments" + "@" + "0" + "[@]" + "=" + "^"; 
                
         if( yyvsp[0].valor_default.size() > 0 ) {
       
            string lbl_true = gera_label( "lbl_true" );
            string lbl_fim_if = gera_label( "lbl_fim_if" );
            string definicao_lbl_true = ":" + lbl_true; 
            string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
             yyval.c = yyval.c + yyvsp[0].c + "@" + "undefined" + "@" + "==" +                   // Codigo da expressão
                   lbl_true + "?" +                                       // Código do IF
                   lbl_fim_if + "#" +                                     // Código do False
                   definicao_lbl_true + "<{" + yyvsp[0].c + yyvsp[0].valor_default + "=" + "^" + "}>" +   // Código do True
                   definicao_lbl_fim_if                                   // Fim do IF
                   ;

         }
         yyval.n_args = yyvsp[0].n_args; 
       }
#line 1747 "y.tab.c"
    break;

  case 23: /* PARAM: ID  */
#line 289 "mini_js.y"
      { yyval.c = yyvsp[0].c;      
        yyval.n_args = 1;
        yyval.valor_default.clear();
        insere_tabela_de_simbolos( DeclLet, yyvsp[0] );
      }
#line 1757 "y.tab.c"
    break;

  case 24: /* PARAM: ID '=' E  */
#line 295 "mini_js.y"
      { 
        yyval.c = yyvsp[-2].c;
        yyval.n_args = 1;
        yyval.valor_default = yyvsp[0].c; 
        insere_tabela_de_simbolos( DeclLet, yyvsp[-2] );
      }
#line 1768 "y.tab.c"
    break;

  case 25: /* Lvalue: ID  */
#line 303 "mini_js.y"
              {yyval.c = yyvsp[0].c + "@";
                verificar_variavel(yyvsp[0], false);}
#line 1775 "y.tab.c"
    break;

  case 26: /* LvalueProp: E '[' E ']'  */
#line 307 "mini_js.y"
                          {yyval.c = yyvsp[-3].c + yyvsp[-1].c + "[@]";}
#line 1781 "y.tab.c"
    break;

  case 27: /* LvalueProp: E '.' ID  */
#line 308 "mini_js.y"
                          {yyval.c = yyvsp[-2].c + yyvsp[0].c + "[@]";}
#line 1787 "y.tab.c"
    break;

  case 28: /* CMD_DECL: LET LET_VARs  */
#line 311 "mini_js.y"
                        { yyval.c = yyvsp[0].c; }
#line 1793 "y.tab.c"
    break;

  case 29: /* CMD_DECL: CONST CONST_VARs  */
#line 312 "mini_js.y"
                           {yyval.c = yyvsp[0].c;}
#line 1799 "y.tab.c"
    break;

  case 30: /* CMD_DECL: VAR VAR_VARs  */
#line 313 "mini_js.y"
                        {yyval.c = yyvsp[0].c;}
#line 1805 "y.tab.c"
    break;

  case 31: /* LET_VARs: LET_VAR ',' LET_VARs  */
#line 316 "mini_js.y"
                                {yyval.c = yyvsp[-2].c + yyvsp[0].c;}
#line 1811 "y.tab.c"
    break;

  case 33: /* LET_VAR: ID  */
#line 320 "mini_js.y"
               {if(!insere_tabela_de_simbolos( DeclLet, yyvsp[0])) yyval.c = yyvsp[0].c + "&";}
#line 1817 "y.tab.c"
    break;

  case 34: /* LET_VAR: ID '=' E  */
#line 321 "mini_js.y"
                    {if(!insere_tabela_de_simbolos( DeclLet, yyvsp[-2] )) yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + yyvsp[0].c + "=" + "^";
                      else yyval.c = yyvsp[-2].c + yyvsp[0].c + "=" + "^"; }
#line 1824 "y.tab.c"
    break;

  case 35: /* LET_VAR: ID '=' OBJ  */
#line 323 "mini_js.y"
                     {if(!insere_tabela_de_simbolos( DeclLet, yyvsp[-2] )) yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + yyvsp[0].c + "=" + "^";
                      else yyval.c = yyvsp[-2].c + yyvsp[0].c + "=" + "^";}
#line 1831 "y.tab.c"
    break;

  case 36: /* CONST_VARs: CONST_VAR ',' CONST_VARs  */
#line 327 "mini_js.y"
                                      {yyval.c = yyvsp[-2].c + yyvsp[0].c;}
#line 1837 "y.tab.c"
    break;

  case 38: /* CONST_VAR: ID  */
#line 331 "mini_js.y"
                { if(!insere_tabela_de_simbolos( DeclConst, yyvsp[0])) yyval.c = yyvsp[0].c + "&";}
#line 1843 "y.tab.c"
    break;

  case 39: /* CONST_VAR: ID '=' E  */
#line 332 "mini_js.y"
                      {if(!insere_tabela_de_simbolos( DeclConst, yyvsp[-2] )) yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + yyvsp[0].c + "=" + "^";
                        else yyval.c = yyvsp[-2].c + yyvsp[0].c + "=" + "^"; }
#line 1850 "y.tab.c"
    break;

  case 40: /* VAR_VARs: VAR_VAR ',' VAR_VARs  */
#line 337 "mini_js.y"
                                {yyval.c = yyvsp[-2].c + yyvsp[0].c;}
#line 1856 "y.tab.c"
    break;

  case 42: /* VAR_VAR: ID  */
#line 341 "mini_js.y"
                { if(!insere_tabela_de_simbolos( DeclVar, yyvsp[0])) yyval.c = yyvsp[0].c + "&";}
#line 1862 "y.tab.c"
    break;

  case 43: /* VAR_VAR: ID '=' E  */
#line 342 "mini_js.y"
                   {if(!insere_tabela_de_simbolos( DeclVar, yyvsp[-2] )) yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + yyvsp[0].c + "=" + "^";
                     else yyval.c = yyvsp[-2].c + yyvsp[0].c + "=" + "^"; }
#line 1869 "y.tab.c"
    break;

  case 44: /* CMD_WHILE: WHILE '(' E ')' CMD  */
#line 347 "mini_js.y"
          {
            string inicio_while = gera_label("inicio_while");
            string fim_while = gera_label("fim_while");
            string definicao_inicio_while = ":" + inicio_while;
            string definicao_fim_while = ":" + fim_while;

            yyval.c = yyvsp[-2].c + 
                    inicio_while  + "?" +
                    fim_while + "#" +
                    definicao_inicio_while + 
                    yyvsp[0].c + yyvsp[-2].c + 
                    inicio_while + "?" +
                    definicao_fim_while;
          }
#line 1888 "y.tab.c"
    break;

  case 45: /* CMD_FOR: FOR '(' CMD E ';' E ')' CMD  */
#line 363 "mini_js.y"
        {
          string inicio_for = gera_label("inicio_for");
          string fim_for = gera_label("fim_for");
          string definicao_inicio_for = ":" + inicio_for;
          string definicao_fim_for = ":" + fim_for;

          yyval.c = yyvsp[-5].c + yyvsp[-4].c + 
              inicio_for + "?" +     //Entra no for?
              fim_for + "#" +
              definicao_inicio_for + 
              yyvsp[0].c + yyvsp[-2].c  + "^" + yyvsp[-4].c + 
              inicio_for + "?" +    //Executa comando e verifica
              definicao_fim_for;  
        }
#line 1907 "y.tab.c"
    break;

  case 46: /* CMD_IF: IF '(' E ')' CMD CMD_ELSE  */
#line 379 "mini_js.y"
         { string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
            yyval.c = yyvsp[-3].c +                       // Codigo da expressão
                   lbl_true + "?" +             // Código do IF
                   yyvsp[0].c + lbl_fim_if + "#" +    // Código do False
                   definicao_lbl_true + yyvsp[-1].c +  // Código do True
                   definicao_lbl_fim_if         // Fim do IF
                   ;
         }
#line 1924 "y.tab.c"
    break;

  case 47: /* CMD_ELSE: ELSE_IF '(' E ')' CMD CMD_ELSE  */
#line 393 "mini_js.y"
        { string lbl_true = gera_label( "lbl_true" );
           string lbl_fim_if = gera_label( "lbl_fim_if" );
           string definicao_lbl_true = ":" + lbl_true;
           string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
            yyval.c = yyvsp[-3].c +                       // Codigo da expressão
                   lbl_true + "?" +             // Código do IF
                   yyvsp[0].c + lbl_fim_if + "#" +    // Código do False
                   definicao_lbl_true + yyvsp[-1].c +  // Código do True
                   definicao_lbl_fim_if         // Fim do IF
                   ;
        }
#line 1941 "y.tab.c"
    break;

  case 48: /* CMD_ELSE: ELSE CMD  */
#line 405 "mini_js.y"
                    {yyval.c = yyvsp[0].c;}
#line 1947 "y.tab.c"
    break;

  case 49: /* CMD_ELSE: %empty  */
#line 406 "mini_js.y"
           {yyval.clear();}
#line 1953 "y.tab.c"
    break;

  case 50: /* E: Lvalue '=' OBJ  */
#line 410 "mini_js.y"
                   { yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[0].c + "="; verificar_variavel(yyvsp[-2], true);}
#line 1959 "y.tab.c"
    break;

  case 51: /* E: Lvalue '=' E  */
#line 411 "mini_js.y"
                {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[0].c + "="; verificar_variavel(yyvsp[-2], true);}
#line 1965 "y.tab.c"
    break;

  case 52: /* E: LvalueProp '=' E  */
#line 412 "mini_js.y"
                     {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[0].c + "[=]";}
#line 1971 "y.tab.c"
    break;

  case 53: /* E: Lvalue MAIS_IGUAL E  */
#line 413 "mini_js.y"
                        {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[-2].c + yyvsp[0].c + "+" + "=";}
#line 1977 "y.tab.c"
    break;

  case 54: /* E: LvalueProp MAIS_IGUAL E  */
#line 414 "mini_js.y"
                            {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[-2].c + yyvsp[0].c + "+" + "[=]";}
#line 1983 "y.tab.c"
    break;

  case 55: /* E: Lvalue MAIS_MAIS  */
#line 417 "mini_js.y"
                          {yyval.c = yyvsp[-1].c + limpAcesso(yyvsp[-1].c) + yyvsp[-1].c + "1" + "+" + "=" + "^";}
#line 1989 "y.tab.c"
    break;

  case 56: /* E: LvalueProp MAIS_MAIS  */
#line 418 "mini_js.y"
                          {yyval.c = yyvsp[-1].c + limpAcesso(yyvsp[-1].c) + yyvsp[-1].c + "1" + "+" + "[=]" + "^";}
#line 1995 "y.tab.c"
    break;

  case 57: /* E: E '<' E  */
#line 419 "mini_js.y"
             { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 2001 "y.tab.c"
    break;

  case 58: /* E: E '>' E  */
#line 420 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 2007 "y.tab.c"
    break;

  case 59: /* E: E '+' E  */
#line 421 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 2013 "y.tab.c"
    break;

  case 60: /* E: E '-' E  */
#line 422 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 2019 "y.tab.c"
    break;

  case 61: /* E: E '*' E  */
#line 423 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 2025 "y.tab.c"
    break;

  case 62: /* E: E '/' E  */
#line 424 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 2031 "y.tab.c"
    break;

  case 63: /* E: E '%' E  */
#line 425 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 2037 "y.tab.c"
    break;

  case 64: /* E: E IGUAL E  */
#line 426 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + "=="; }
#line 2043 "y.tab.c"
    break;

  case 65: /* E: E '(' LISTA_ARGs ')'  */
#line 428 "mini_js.y"
    {
      yyval.c = yyvsp[-1].c + to_string( yyvsp[-1].n_args ) + yyvsp[-3].c + "$";
    }
#line 2051 "y.tab.c"
    break;

  case 66: /* $@2: %empty  */
#line 431 "mini_js.y"
                       {insere_tabela_de_simbolos( DeclVar, yyvsp[-2] ); in_func++;}
#line 2057 "y.tab.c"
    break;

  case 67: /* E: ID SETA EMPILHA_TS $@2 E  */
#line 432 "mini_js.y"
      {
              in_func--;    
              string lbl_endereco_funcao = gera_label( "func_" + yyvsp[-4].c[0] );
              string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;

              yyval.c = vector<string>{"{}"} + "'&funcao'" + lbl_endereco_funcao + "[<=]";
              funcoes = funcoes + definicao_lbl_endereco_funcao + 
              yyvsp[-4].c + "&" + yyvsp[-4].c + "arguments" + "@" + "0" + "[@]" + "=" + "^" +   //Gera parametro
              yyvsp[0].c  + "'&retorno'" + "@"+ "~";                 //CMDs e retorno
              ts.pop_back();
      }
#line 2073 "y.tab.c"
    break;

  case 68: /* $@3: %empty  */
#line 443 "mini_js.y"
                       {insere_tabela_de_simbolos( DeclVar, yyvsp[-2] ); in_func++;}
#line 2079 "y.tab.c"
    break;

  case 69: /* E: ID SETA EMPILHA_TS $@3 '{' CMDs '}'  */
#line 444 "mini_js.y"
    { 
              in_func--;    
              string lbl_endereco_funcao = gera_label( "func_" + yyvsp[-6].c[0] );
              string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;

              yyval.c = vector<string>{"{}"} + "'&funcao'" + lbl_endereco_funcao + "[<=]";
              funcoes = funcoes + definicao_lbl_endereco_funcao + 
              yyvsp[-6].c + "&" + yyvsp[-6].c + "arguments" + "@" + "0" + "[@]" + "=" + "^" +  
              yyvsp[-1].c  + "'&retorno'" + "@"+ "~";                 
              ts.pop_back();
    }
#line 2095 "y.tab.c"
    break;

  case 70: /* E: '(' FARGS PARENTESES_FUNCAO SETA E  */
#line 458 "mini_js.y"
      {
        in_func--;
        string lbl_endereco_funcao = gera_label( "func_");
        string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
      
        yyval.c = vector<string>{"{}"} + "'&funcao'" + lbl_endereco_funcao + "[<=]";
        funcoes = funcoes + definicao_lbl_endereco_funcao + yyvsp[-3].c + yyvsp[0].c +
              "'&retorno'" + "@"+ "~";
        ts.pop_back();
      }
#line 2110 "y.tab.c"
    break;

  case 71: /* $@4: %empty  */
#line 469 "mini_js.y"
                 { in_func++;}
#line 2116 "y.tab.c"
    break;

  case 72: /* E: FUNCTION '(' $@4 EMPILHA_TS LISTA_PARAMs ')' '{' CMDs '}'  */
#line 470 "mini_js.y"
    {
      in_func--;
      string lbl_endereco_funcao = gera_label( "func_");
      string definicao_lbl_endereco_funcao = ":" + lbl_endereco_funcao;
      
      yyval.c = vector<string>{"{}"} + "'&funcao'" + lbl_endereco_funcao + "[<=]";
      funcoes = funcoes + definicao_lbl_endereco_funcao + yyvsp[-4].c + yyvsp[-1].c +
                "undefined" + "@" + "'&retorno'" + "@"+ "~";
      ts.pop_back();
    }
#line 2131 "y.tab.c"
    break;

  case 79: /* E: '-' E  */
#line 486 "mini_js.y"
          {yyval.c = "0" + yyvsp[0].c + "-";}
#line 2137 "y.tab.c"
    break;

  case 80: /* E: '[' ']'  */
#line 487 "mini_js.y"
            {yyval.clear(); yyval.c = yyval.c + "[]";}
#line 2143 "y.tab.c"
    break;

  case 81: /* E: '[' ELEMENTOS ']'  */
#line 488 "mini_js.y"
                      {yyval.c = "[]" + yyvsp[-1].c;}
#line 2149 "y.tab.c"
    break;

  case 82: /* E: '(' E ')'  */
#line 489 "mini_js.y"
              {yyval.c = yyvsp[-1].c;}
#line 2155 "y.tab.c"
    break;

  case 83: /* E: '(' OBJ ')'  */
#line 490 "mini_js.y"
                { yyval.c = yyvsp[-1].c;}
#line 2161 "y.tab.c"
    break;

  case 84: /* FARGS: FARGS ',' FARG  */
#line 494 "mini_js.y"
      { 
         yyval.c = yyvsp[-2].c + yyvsp[0].c + "&" + yyvsp[0].c + "arguments" + "@" + to_string( yyvsp[-2].n_args )
                + "[@]" + "=" + "^"; 
                
         if( yyvsp[0].valor_default.size() > 0 ) {
       
            string lbl_true = gera_label( "lbl_true" );
            string lbl_fim_if = gera_label( "lbl_fim_if" );
            string definicao_lbl_true = ":" + lbl_true;
            string definicao_lbl_fim_if = ":" + lbl_fim_if;
                    
           yyval.c = yyval.c + yyvsp[0].c + "@" + "undefined" + "@" + "==" +                   // Codigo da expressão
                   lbl_true + "?" +                                       // Código do IF
                   lbl_fim_if + "#" +                                     // Código do False
                   definicao_lbl_true + "<{" + yyvsp[0].c + yyvsp[0].valor_default + "=" + "^" + "}>" +   // Código do True
                   definicao_lbl_fim_if                                   // Fim do IF
                   ;
         }
         yyval.n_args = yyvsp[-2].n_args + yyvsp[0].n_args; 
       }
#line 2186 "y.tab.c"
    break;

  case 85: /* $@5: %empty  */
#line 515 "mini_js.y"
                       {in_func++;}
#line 2192 "y.tab.c"
    break;

  case 86: /* FARGS: FARG EMPILHA_TS $@5  */
#line 516 "mini_js.y"
      {  
          yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + "arguments" + "@" + "0" + "[@]" + "=" + "^"; 
                  
          if( yyvsp[-2].valor_default.size() > 0 ) {
        
              string lbl_true = gera_label( "lbl_true" );
              string lbl_fim_if = gera_label( "lbl_fim_if" );
              string definicao_lbl_true = ":" + lbl_true; 
              string definicao_lbl_fim_if = ":" + lbl_fim_if;
                      
              yyval.c = yyval.c + yyvsp[-2].c + "@" + "undefined" + "@" + "==" +                   // Codigo da expressão
                    lbl_true + "?" +                                       // Código do IF
                    lbl_fim_if + "#" +                                     // Código do False
                    definicao_lbl_true + "<{" + yyvsp[-2].c + yyvsp[-2].valor_default + "=" + "^" + "}>" +   // Código do True
                    definicao_lbl_fim_if                                   // Fim do IF
                    ;

          }
          yyval.n_args = yyvsp[-2].n_args; 
        }
#line 2217 "y.tab.c"
    break;

  case 87: /* FARG: ID  */
#line 539 "mini_js.y"
    { 
        yyval.c = yyvsp[0].c;      
        yyval.n_args = 1;
        yyval.valor_default.clear();
        insere_tabela_de_simbolos( DeclVar, yyvsp[0] );
    }
#line 2228 "y.tab.c"
    break;

  case 88: /* FARG: Lvalue '=' E  */
#line 546 "mini_js.y"
    { 
        yyval.c = limpAcesso(yyvsp[-2].c);
        yyval.n_args = 1;
        yyval.valor_default = yyvsp[0].c; 
        insere_tabela_de_simbolos( DeclLet, yyvsp[-2] );
    }
#line 2239 "y.tab.c"
    break;

  case 89: /* FARG: Lvalue '=' OBJ  */
#line 553 "mini_js.y"
    { 
        yyval.c = yyvsp[-2].c;
        yyval.n_args = 1;
        yyval.valor_default = yyvsp[0].c; 
    }
#line 2249 "y.tab.c"
    break;

  case 90: /* OBJ: '{' List_Campos '}'  */
#line 560 "mini_js.y"
                          {yyval.c = "{}" + yyvsp[-1].c;}
#line 2255 "y.tab.c"
    break;

  case 92: /* List_Campos: %empty  */
#line 564 "mini_js.y"
              {yyval.clear();}
#line 2261 "y.tab.c"
    break;

  case 93: /* Campos: Campo ',' Campos  */
#line 567 "mini_js.y"
                          {yyval.c = yyvsp[-2].c + yyvsp[0].c;}
#line 2267 "y.tab.c"
    break;

  case 95: /* Campo: ID ':' E  */
#line 571 "mini_js.y"
                  {yyval.c = yyvsp[-2].c + yyvsp[0].c + "[<=]";}
#line 2273 "y.tab.c"
    break;

  case 96: /* Campo: ID ':' OBJ  */
#line 572 "mini_js.y"
                   {yyval.c = yyvsp[-2].c + yyvsp[0].c + "[<=]";}
#line 2279 "y.tab.c"
    break;

  case 97: /* ELEMENTOS: ELEMENTOS ',' ELEMENTO  */
#line 577 "mini_js.y"
      {
          yyval.c = yyvsp[-2].c + to_string( yyvsp[-2].n_args ) + yyvsp[0].c + "[<=]"; 
          yyval.n_args = yyvsp[-2].n_args + yyvsp[0].n_args;
      }
#line 2288 "y.tab.c"
    break;

  case 98: /* ELEMENTOS: ELEMENTO  */
#line 582 "mini_js.y"
      {
          yyval.c = "0" + yyvsp[0].c + "[<=]"; 
          yyval.n_args = yyvsp[0].n_args;
      }
#line 2297 "y.tab.c"
    break;

  case 99: /* ELEMENTO: E  */
#line 588 "mini_js.y"
            {yyval.c = yyvsp[0].c;  yyval.n_args = 1;}
#line 2303 "y.tab.c"
    break;

  case 100: /* ELEMENTO: OBJ  */
#line 589 "mini_js.y"
              {yyval.c = yyvsp[0].c; yyval.n_args = 1;}
#line 2309 "y.tab.c"
    break;

  case 101: /* LISTA_ARGs: ARGs  */
#line 592 "mini_js.y"
                  {yyval.c = yyvsp[0].c; yyval.n_args = yyvsp[0].n_args;}
#line 2315 "y.tab.c"
    break;

  case 102: /* LISTA_ARGs: %empty  */
#line 593 "mini_js.y"
             { yyval.clear(); }
#line 2321 "y.tab.c"
    break;

  case 103: /* ARGs: ARGs ',' E  */
#line 597 "mini_js.y"
       { yyval.c = yyvsp[-2].c + yyvsp[0].c;
         yyval.n_args = yyvsp[-2].n_args + 1; 
        }
#line 2329 "y.tab.c"
    break;

  case 104: /* ARGs: E  */
#line 601 "mini_js.y"
       { yyval.c = yyvsp[0].c;
         yyval.n_args = 1; }
#line 2336 "y.tab.c"
    break;


#line 2340 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 605 "mini_js.y"


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
