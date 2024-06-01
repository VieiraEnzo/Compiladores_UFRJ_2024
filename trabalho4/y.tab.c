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


#line 211 "y.tab.c"

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
    PRINT = 261,                   /* PRINT  */
    ELSE_IF = 262,                 /* ELSE_IF  */
    CDOUBLE = 263,                 /* CDOUBLE  */
    CSTRING = 264,                 /* CSTRING  */
    CINT = 265,                    /* CINT  */
    AND = 266,                     /* AND  */
    OR = 267,                      /* OR  */
    ME_IG = 268,                   /* ME_IG  */
    MA_IG = 269,                   /* MA_IG  */
    DIF = 270,                     /* DIF  */
    IGUAL = 271,                   /* IGUAL  */
    MAIS_IGUAL = 272,              /* MAIS_IGUAL  */
    MAIS_MAIS = 273,               /* MAIS_MAIS  */
    NEWOBJECT = 274,               /* NEWOBJECT  */
    NEWARRAY = 275,                /* NEWARRAY  */
    FOR = 276,                     /* FOR  */
    WHILE = 277,                   /* WHILE  */
    LET = 278,                     /* LET  */
    CONST = 279,                   /* CONST  */
    VAR = 280                      /* VAR  */
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
#define PRINT 261
#define ELSE_IF 262
#define CDOUBLE 263
#define CSTRING 264
#define CINT 265
#define AND 266
#define OR 267
#define ME_IG 268
#define MA_IG 269
#define DIF 270
#define IGUAL 271
#define MAIS_IGUAL 272
#define MAIS_MAIS 273
#define NEWOBJECT 274
#define NEWARRAY 275
#define FOR 276
#define WHILE 277
#define LET 278
#define CONST 279
#define VAR 280

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
  YYSYMBOL_PRINT = 6,                      /* PRINT  */
  YYSYMBOL_ELSE_IF = 7,                    /* ELSE_IF  */
  YYSYMBOL_CDOUBLE = 8,                    /* CDOUBLE  */
  YYSYMBOL_CSTRING = 9,                    /* CSTRING  */
  YYSYMBOL_CINT = 10,                      /* CINT  */
  YYSYMBOL_AND = 11,                       /* AND  */
  YYSYMBOL_OR = 12,                        /* OR  */
  YYSYMBOL_ME_IG = 13,                     /* ME_IG  */
  YYSYMBOL_MA_IG = 14,                     /* MA_IG  */
  YYSYMBOL_DIF = 15,                       /* DIF  */
  YYSYMBOL_IGUAL = 16,                     /* IGUAL  */
  YYSYMBOL_MAIS_IGUAL = 17,                /* MAIS_IGUAL  */
  YYSYMBOL_MAIS_MAIS = 18,                 /* MAIS_MAIS  */
  YYSYMBOL_NEWOBJECT = 19,                 /* NEWOBJECT  */
  YYSYMBOL_NEWARRAY = 20,                  /* NEWARRAY  */
  YYSYMBOL_FOR = 21,                       /* FOR  */
  YYSYMBOL_WHILE = 22,                     /* WHILE  */
  YYSYMBOL_LET = 23,                       /* LET  */
  YYSYMBOL_CONST = 24,                     /* CONST  */
  YYSYMBOL_VAR = 25,                       /* VAR  */
  YYSYMBOL_26_ = 26,                       /* '='  */
  YYSYMBOL_27_ = 27,                       /* '<'  */
  YYSYMBOL_28_ = 28,                       /* '>'  */
  YYSYMBOL_29_ = 29,                       /* '+'  */
  YYSYMBOL_30_ = 30,                       /* '-'  */
  YYSYMBOL_31_ = 31,                       /* '*'  */
  YYSYMBOL_32_ = 32,                       /* '/'  */
  YYSYMBOL_33_ = 33,                       /* '%'  */
  YYSYMBOL_34_ = 34,                       /* '['  */
  YYSYMBOL_35_ = 35,                       /* '('  */
  YYSYMBOL_36_ = 36,                       /* '.'  */
  YYSYMBOL_37_ = 37,                       /* ';'  */
  YYSYMBOL_38_ = 38,                       /* '{'  */
  YYSYMBOL_39_ = 39,                       /* '}'  */
  YYSYMBOL_40_ = 40,                       /* ']'  */
  YYSYMBOL_41_ = 41,                       /* ','  */
  YYSYMBOL_42_ = 42,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_S = 44,                         /* S  */
  YYSYMBOL_CMDs = 45,                      /* CMDs  */
  YYSYMBOL_CMD = 46,                       /* CMD  */
  YYSYMBOL_A = 47,                         /* A  */
  YYSYMBOL_Lvalue = 48,                    /* Lvalue  */
  YYSYMBOL_LvalueProp = 49,                /* LvalueProp  */
  YYSYMBOL_CMD_DECL = 50,                  /* CMD_DECL  */
  YYSYMBOL_LET_VARs = 51,                  /* LET_VARs  */
  YYSYMBOL_LET_VAR = 52,                   /* LET_VAR  */
  YYSYMBOL_CONST_VARs = 53,                /* CONST_VARs  */
  YYSYMBOL_CONST_VAR = 54,                 /* CONST_VAR  */
  YYSYMBOL_VAR_VARs = 55,                  /* VAR_VARs  */
  YYSYMBOL_VAR_VAR = 56,                   /* VAR_VAR  */
  YYSYMBOL_CMD_WHILE = 57,                 /* CMD_WHILE  */
  YYSYMBOL_CMD_FOR = 58,                   /* CMD_FOR  */
  YYSYMBOL_CMD_IF = 59,                    /* CMD_IF  */
  YYSYMBOL_CMD_ELSE = 60,                  /* CMD_ELSE  */
  YYSYMBOL_E = 61                          /* E  */
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
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   347

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   280


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
       2,     2,     2,     2,     2,     2,     2,    33,     2,     2,
      35,    42,    31,    29,    41,    30,    36,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    37,
      27,    26,    28,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    40,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   163,   163,   166,   167,   170,   171,   172,   173,   174,
     175,   176,   177,   180,   181,   182,   183,   187,   191,   192,
     195,   196,   197,   200,   201,   204,   205,   208,   209,   212,
     213,   217,   218,   221,   222,   225,   241,   257,   271,   284,
     285,   288,   289,   290,   291,   292,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312
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
  "PRINT", "ELSE_IF", "CDOUBLE", "CSTRING", "CINT", "AND", "OR", "ME_IG",
  "MA_IG", "DIF", "IGUAL", "MAIS_IGUAL", "MAIS_MAIS", "NEWOBJECT",
  "NEWARRAY", "FOR", "WHILE", "LET", "CONST", "VAR", "'='", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'['", "'('", "'.'", "';'", "'{'",
  "'}'", "']'", "','", "')'", "$accept", "S", "CMDs", "CMD", "A", "Lvalue",
  "LvalueProp", "CMD_DECL", "LET_VARs", "LET_VAR", "CONST_VARs",
  "CONST_VAR", "VAR_VARs", "VAR_VAR", "CMD_WHILE", "CMD_FOR", "CMD_IF",
  "CMD_ELSE", "E", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-43)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-17)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     148,   -43,   -31,   171,   -43,   -43,   -43,   171,   -43,   -43,
     -26,   -20,    14,    21,    24,   171,   171,   -43,   148,    34,
     148,   -43,    -9,   -15,   -12,     2,   -43,   -43,   -43,   301,
     171,     5,    12,   263,     5,    12,   148,   171,    16,   -43,
       3,    17,   -43,     7,    20,   -43,    19,    78,    25,   125,
     -43,   -43,   -43,   171,   -43,   171,   171,   -43,   171,   -43,
     171,   171,   171,   171,   171,   171,   171,   171,   171,    48,
     166,   171,   171,   171,   171,   -43,   171,   187,   171,    14,
     171,    21,   171,    24,   -43,   -43,    57,   301,    61,   301,
     311,   311,   311,    78,    78,   -24,   -24,   -24,   244,   -43,
     148,   -24,   301,   -24,   301,   282,   148,   301,   -43,   301,
     -43,   301,   -43,   -43,    28,   171,   -43,   148,    27,   -43,
     206,   -43,   171,   148,   225,   -43,   148,    28,   -43
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    17,     0,     0,    59,    61,    60,     0,    64,    63,
       0,     0,     0,     0,     0,     0,     0,    12,     0,     0,
       2,     4,     0,    57,    58,     0,    11,     9,     8,     0,
       0,    57,    58,     0,    45,    46,     0,     0,    25,    20,
      24,    29,    21,    28,    33,    22,    32,    62,     0,     0,
       1,     3,     7,     0,    47,     0,     0,    48,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,     0,     0,     0,     0,
       0,     0,     0,     0,    65,    10,    43,    13,    44,    14,
      56,    49,    50,    51,    52,    53,    54,    55,     0,    19,
       0,    43,    41,    44,    42,     0,     0,    26,    23,    30,
      27,    34,    31,    18,    40,     0,    35,     0,     0,    37,
       0,    39,     0,     0,     0,    36,     0,    40,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,    46,    -4,   -43,     0,     1,   -43,   -10,   -43,
      -2,   -43,    -3,   -43,   -43,   -43,   -43,   -42,    10
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    31,    32,    25,    39,    40,
      42,    43,    45,    46,    26,    27,    28,   119,    29
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      23,    24,    53,    54,    30,    56,    57,    34,    35,    36,
      68,    55,    69,    33,    58,    37,    51,    38,    23,    24,
      23,    24,    71,    54,    41,    47,    48,    44,    52,    73,
      57,    72,    76,   117,    50,   118,    23,    24,    74,    59,
      70,    60,    78,    80,    79,    51,    82,    77,    81,    23,
      24,    99,    61,    62,    63,    64,    65,    66,    67,    68,
      83,    69,   122,    86,    49,    87,    88,    84,    89,   108,
      90,    91,    92,    93,    94,    95,    96,    97,    98,   110,
     112,   101,   102,   103,   104,   128,   105,     0,   107,     0,
     109,    68,   111,    69,   -15,    68,   114,    69,   -16,     0,
      23,    24,   116,     0,     0,     0,    23,    24,     0,    65,
      66,    67,    68,   121,    69,     0,     0,    23,    24,   125,
       0,     0,   127,    23,    24,   120,    23,    24,     1,     2,
       0,     3,   124,     4,     5,     6,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     9,    10,    11,    12,    13,
      14,     1,     2,     0,     3,    15,     4,     5,     6,     0,
      16,     0,    17,    18,    85,     0,     7,     8,     9,    10,
      11,    12,    13,    14,     1,     0,     0,     0,    15,     4,
       5,     6,    60,    16,     0,    17,    18,     0,     0,     7,
       8,     9,     0,    61,    62,    63,    64,    65,    66,    67,
      68,    15,    69,    60,     0,     0,    16,     0,   100,     0,
       0,     0,     0,     0,    61,    62,    63,    64,    65,    66,
      67,    68,    60,    69,     0,     0,     0,     0,     0,   106,
       0,     0,     0,    61,    62,    63,    64,    65,    66,    67,
      68,    60,    69,     0,     0,     0,     0,     0,   123,     0,
       0,     0,    61,    62,    63,    64,    65,    66,    67,    68,
      60,    69,     0,     0,     0,     0,     0,   126,     0,     0,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    60,
      69,     0,     0,     0,   113,     0,     0,     0,     0,     0,
      61,    62,    63,    64,    65,    66,    67,    68,    60,    69,
      75,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      62,    63,    64,    65,    66,    67,    68,    60,    69,   115,
       0,     0,     0,     0,     0,     0,     0,   -17,    61,    62,
      63,    64,    65,    66,    67,    68,     0,    69,   -17,   -17,
      63,    64,    65,    66,    67,    68,     0,    69
};

static const yytype_int8 yycheck[] =
{
       0,     0,    17,    18,    35,    17,    18,     7,     7,    35,
      34,    26,    36,     3,    26,    35,    20,     3,    18,    18,
      20,    20,    17,    18,     3,    15,    16,     3,    37,    17,
      18,    26,    36,     5,     0,     7,    36,    36,    26,    37,
      30,    16,    26,    26,    41,    49,    26,    37,    41,    49,
      49,     3,    27,    28,    29,    30,    31,    32,    33,    34,
      41,    36,    35,    53,    18,    55,    56,    42,    58,    79,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    81,
      83,    71,    72,    73,    74,   127,    76,    -1,    78,    -1,
      80,    34,    82,    36,    37,    34,   100,    36,    37,    -1,
     100,   100,   106,    -1,    -1,    -1,   106,   106,    -1,    31,
      32,    33,    34,   117,    36,    -1,    -1,   117,   117,   123,
      -1,    -1,   126,   123,   123,   115,   126,   126,     3,     4,
      -1,     6,   122,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    18,    19,    20,    21,    22,    23,    24,
      25,     3,     4,    -1,     6,    30,     8,     9,    10,    -1,
      35,    -1,    37,    38,    39,    -1,    18,    19,    20,    21,
      22,    23,    24,    25,     3,    -1,    -1,    -1,    30,     8,
       9,    10,    16,    35,    -1,    37,    38,    -1,    -1,    18,
      19,    20,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    30,    36,    16,    -1,    -1,    35,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    27,    28,    29,    30,    31,    32,
      33,    34,    16,    36,    -1,    -1,    -1,    -1,    -1,    42,
      -1,    -1,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    16,    36,    -1,    -1,    -1,    -1,    -1,    42,    -1,
      -1,    -1,    27,    28,    29,    30,    31,    32,    33,    34,
      16,    36,    -1,    -1,    -1,    -1,    -1,    42,    -1,    -1,
      -1,    27,    28,    29,    30,    31,    32,    33,    34,    16,
      36,    -1,    -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,
      27,    28,    29,    30,    31,    32,    33,    34,    16,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      28,    29,    30,    31,    32,    33,    34,    16,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    16,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     6,     8,     9,    10,    18,    19,    20,
      21,    22,    23,    24,    25,    30,    35,    37,    38,    44,
      45,    46,    47,    48,    49,    50,    57,    58,    59,    61,
      35,    48,    49,    61,    48,    49,    35,    35,     3,    51,
      52,     3,    53,    54,     3,    55,    56,    61,    61,    45,
       0,    46,    37,    17,    18,    26,    17,    18,    26,    37,
      16,    27,    28,    29,    30,    31,    32,    33,    34,    36,
      61,    17,    26,    17,    26,    37,    46,    61,    26,    41,
      26,    41,    26,    41,    42,    39,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,     3,
      42,    61,    61,    61,    61,    61,    42,    61,    51,    61,
      53,    61,    55,    40,    46,    37,    46,     5,     7,    60,
      61,    46,    35,    42,    61,    46,    42,    46,    60
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    46,    46,
      46,    46,    46,    47,    47,    47,    47,    48,    49,    49,
      50,    50,    50,    51,    51,    52,    52,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    58,    59,    60,    60,
      60,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     3,     2,     1,     1,
       3,     1,     1,     3,     3,     3,     3,     1,     4,     3,
       2,     2,     2,     3,     1,     1,     3,     3,     1,     1,
       3,     3,     1,     1,     3,     5,     8,     6,     6,     2,
       0,     3,     3,     3,     3,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     1,     1,     1,
       1,     1,     2,     1,     1,     3
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
#line 163 "mini_js.y"
         { print( resolve_enderecos( yyvsp[0].c + "." ) ); }
#line 1466 "y.tab.c"
    break;

  case 3: /* CMDs: CMDs CMD  */
#line 166 "mini_js.y"
                 {yyval.c = yyvsp[-1].c + yyvsp[0].c;}
#line 1472 "y.tab.c"
    break;

  case 6: /* CMD: PRINT E ';'  */
#line 171 "mini_js.y"
                  { yyval.c = yyvsp[-1].c + "println" + "#"; }
#line 1478 "y.tab.c"
    break;

  case 10: /* CMD: '{' CMDs '}'  */
#line 175 "mini_js.y"
                   {yyval.c = yyvsp[-1].c;}
#line 1484 "y.tab.c"
    break;

  case 12: /* CMD: ';'  */
#line 177 "mini_js.y"
          {yyval.clear();}
#line 1490 "y.tab.c"
    break;

  case 13: /* A: Lvalue '=' E  */
#line 180 "mini_js.y"
                            {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[0].c + "=" + "^";}
#line 1496 "y.tab.c"
    break;

  case 14: /* A: LvalueProp '=' E  */
#line 181 "mini_js.y"
                            {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[0].c + "[=]" + "^";}
#line 1502 "y.tab.c"
    break;

  case 15: /* A: Lvalue MAIS_IGUAL E  */
#line 182 "mini_js.y"
                            {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[-2].c + yyvsp[0].c + "+" + "=" + "^";}
#line 1508 "y.tab.c"
    break;

  case 16: /* A: LvalueProp MAIS_IGUAL E  */
#line 183 "mini_js.y"
                            {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[-2].c + yyvsp[0].c + "+" + "[=]" + "^";}
#line 1514 "y.tab.c"
    break;

  case 17: /* Lvalue: ID  */
#line 187 "mini_js.y"
              {yyval.c = yyvsp[0].c + "@";
                verificar_variavel(yyvsp[0]);}
#line 1521 "y.tab.c"
    break;

  case 18: /* LvalueProp: E '[' E ']'  */
#line 191 "mini_js.y"
                          {yyval.c = yyvsp[-3].c + yyvsp[-1].c + "[@]";}
#line 1527 "y.tab.c"
    break;

  case 19: /* LvalueProp: E '.' ID  */
#line 192 "mini_js.y"
                          {yyval.c = yyvsp[-2].c + yyvsp[0].c + "[@]";}
#line 1533 "y.tab.c"
    break;

  case 20: /* CMD_DECL: LET LET_VARs  */
#line 195 "mini_js.y"
                        { yyval.c = yyvsp[0].c; }
#line 1539 "y.tab.c"
    break;

  case 21: /* CMD_DECL: CONST CONST_VARs  */
#line 196 "mini_js.y"
                           {yyval.c = yyvsp[0].c;}
#line 1545 "y.tab.c"
    break;

  case 22: /* CMD_DECL: VAR VAR_VARs  */
#line 197 "mini_js.y"
                        {yyval.c = yyvsp[0].c;}
#line 1551 "y.tab.c"
    break;

  case 23: /* LET_VARs: LET_VAR ',' LET_VARs  */
#line 200 "mini_js.y"
                                {yyval.c = yyvsp[-2].c + yyvsp[0].c;}
#line 1557 "y.tab.c"
    break;

  case 25: /* LET_VAR: ID  */
#line 204 "mini_js.y"
               { yyval.c = yyvsp[0].c + "&";  insere_tabela_de_simbolos( DeclLet, yyvsp[0] );}
#line 1563 "y.tab.c"
    break;

  case 26: /* LET_VAR: ID '=' E  */
#line 205 "mini_js.y"
                    {yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + yyvsp[0].c + "=" + "^"; insere_tabela_de_simbolos( DeclLet, yyvsp[-2] ); }
#line 1569 "y.tab.c"
    break;

  case 27: /* CONST_VARs: CONST_VAR ',' CONST_VARs  */
#line 208 "mini_js.y"
                                      {yyval.c = yyvsp[-2].c + yyvsp[0].c;}
#line 1575 "y.tab.c"
    break;

  case 29: /* CONST_VAR: ID  */
#line 212 "mini_js.y"
                { yyval.c = yyvsp[0].c + "&";  insere_tabela_de_simbolos( DeclConst, yyvsp[0] );}
#line 1581 "y.tab.c"
    break;

  case 30: /* CONST_VAR: ID '=' E  */
#line 213 "mini_js.y"
                      {yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + yyvsp[0].c + "=" + "^"; insere_tabela_de_simbolos( DeclConst, yyvsp[-2] ); }
#line 1587 "y.tab.c"
    break;

  case 31: /* VAR_VARs: VAR_VAR ',' VAR_VARs  */
#line 217 "mini_js.y"
                                {yyval.c = yyvsp[-2].c + yyvsp[0].c;}
#line 1593 "y.tab.c"
    break;

  case 33: /* VAR_VAR: ID  */
#line 221 "mini_js.y"
                  { yyval.c = yyvsp[0].c + "&";  insere_tabela_de_simbolos( DeclVar, yyvsp[0] );}
#line 1599 "y.tab.c"
    break;

  case 34: /* VAR_VAR: ID '=' E  */
#line 222 "mini_js.y"
                   {yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + yyvsp[0].c + "=" + "^"; insere_tabela_de_simbolos( DeclVar, yyvsp[-2] ); }
#line 1605 "y.tab.c"
    break;

  case 35: /* CMD_WHILE: WHILE '(' E ')' CMD  */
#line 226 "mini_js.y"
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
#line 1624 "y.tab.c"
    break;

  case 36: /* CMD_FOR: FOR '(' CMD E ';' E ')' CMD  */
#line 242 "mini_js.y"
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
#line 1643 "y.tab.c"
    break;

  case 37: /* CMD_IF: IF '(' E ')' CMD CMD_ELSE  */
#line 258 "mini_js.y"
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
#line 1660 "y.tab.c"
    break;

  case 38: /* CMD_ELSE: ELSE_IF '(' E ')' CMD CMD_ELSE  */
#line 272 "mini_js.y"
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
#line 1677 "y.tab.c"
    break;

  case 39: /* CMD_ELSE: ELSE CMD  */
#line 284 "mini_js.y"
                    {yyval.c = yyvsp[0].c;}
#line 1683 "y.tab.c"
    break;

  case 40: /* CMD_ELSE: %empty  */
#line 285 "mini_js.y"
           {yyval.clear();}
#line 1689 "y.tab.c"
    break;

  case 41: /* E: Lvalue '=' E  */
#line 288 "mini_js.y"
                 {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[0].c + "="; verificar_const(yyvsp[-2]);}
#line 1695 "y.tab.c"
    break;

  case 42: /* E: LvalueProp '=' E  */
#line 289 "mini_js.y"
                     {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[0].c + "[=]";}
#line 1701 "y.tab.c"
    break;

  case 43: /* E: Lvalue MAIS_IGUAL E  */
#line 290 "mini_js.y"
                        {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[-2].c + yyvsp[0].c + "+" + "=";}
#line 1707 "y.tab.c"
    break;

  case 44: /* E: LvalueProp MAIS_IGUAL E  */
#line 291 "mini_js.y"
                            {yyval.c = limpAcesso(yyvsp[-2].c) + yyvsp[-2].c + yyvsp[0].c + "+" + "[=]";}
#line 1713 "y.tab.c"
    break;

  case 45: /* E: MAIS_MAIS Lvalue  */
#line 292 "mini_js.y"
                          {yyval.c = limpAcesso(yyvsp[0].c) + yyvsp[0].c + "1" + "+" + "=";}
#line 1719 "y.tab.c"
    break;

  case 46: /* E: MAIS_MAIS LvalueProp  */
#line 293 "mini_js.y"
                          {yyval.c = limpAcesso(yyvsp[0].c) + yyvsp[0].c  + "1" + "+" + "[=]";}
#line 1725 "y.tab.c"
    break;

  case 47: /* E: Lvalue MAIS_MAIS  */
#line 294 "mini_js.y"
                          {yyval.c = yyvsp[-1].c + limpAcesso(yyvsp[-1].c) + yyvsp[-1].c + "1" + "+" + "=" + "^";}
#line 1731 "y.tab.c"
    break;

  case 48: /* E: LvalueProp MAIS_MAIS  */
#line 295 "mini_js.y"
                          {yyval.c = yyvsp[-1].c + limpAcesso(yyvsp[-1].c) + yyvsp[-1].c + "1" + "+" + "[=]" + "^";}
#line 1737 "y.tab.c"
    break;

  case 49: /* E: E '<' E  */
#line 296 "mini_js.y"
             { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1743 "y.tab.c"
    break;

  case 50: /* E: E '>' E  */
#line 297 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1749 "y.tab.c"
    break;

  case 51: /* E: E '+' E  */
#line 298 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1755 "y.tab.c"
    break;

  case 52: /* E: E '-' E  */
#line 299 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1761 "y.tab.c"
    break;

  case 53: /* E: E '*' E  */
#line 300 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1767 "y.tab.c"
    break;

  case 54: /* E: E '/' E  */
#line 301 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1773 "y.tab.c"
    break;

  case 55: /* E: E '%' E  */
#line 302 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1779 "y.tab.c"
    break;

  case 56: /* E: E IGUAL E  */
#line 303 "mini_js.y"
              { yyval.c = yyvsp[-2].c + yyvsp[0].c + "=="; }
#line 1785 "y.tab.c"
    break;

  case 62: /* E: '-' E  */
#line 309 "mini_js.y"
          {yyval.c = "0" + yyvsp[0].c + "-";}
#line 1791 "y.tab.c"
    break;

  case 65: /* E: '(' E ')'  */
#line 312 "mini_js.y"
              {yyval.c = yyvsp[-1].c;}
#line 1797 "y.tab.c"
    break;


#line 1801 "y.tab.c"

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

#line 316 "mini_js.y"


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
