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
            cout << "Erro: a variável " << nome <<" já foi declarada na linha " << ts[nome].linha;
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



#line 195 "mini_js.tab.c"

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
  YYSYMBOL_34_ = 34,                       /* ';'  */
  YYSYMBOL_35_ = 35,                       /* '{'  */
  YYSYMBOL_36_ = 36,                       /* '}'  */
  YYSYMBOL_37_ = 37,                       /* '.'  */
  YYSYMBOL_38_ = 38,                       /* '['  */
  YYSYMBOL_39_ = 39,                       /* ']'  */
  YYSYMBOL_40_ = 40,                       /* ','  */
  YYSYMBOL_41_ = 41,                       /* '('  */
  YYSYMBOL_42_ = 42,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_S = 44,                         /* S  */
  YYSYMBOL_CMDs = 45,                      /* CMDs  */
  YYSYMBOL_CMD = 46,                       /* CMD  */
  YYSYMBOL_A = 47,                         /* A  */
  YYSYMBOL_IDls = 48,                      /* IDls  */
  YYSYMBOL_CAMPO = 49,                     /* CAMPO  */
  YYSYMBOL_CMD_DECL = 50,                  /* CMD_DECL  */
  YYSYMBOL_LET_VAR = 51,                   /* LET_VAR  */
  YYSYMBOL_CONST_VAR = 52,                 /* CONST_VAR  */
  YYSYMBOL_VAR_VAR = 53,                   /* VAR_VAR  */
  YYSYMBOL_CMD_WHILE = 54,                 /* CMD_WHILE  */
  YYSYMBOL_CMD_FOR = 55,                   /* CMD_FOR  */
  YYSYMBOL_CMD_IF = 56,                    /* CMD_IF  */
  YYSYMBOL_CMD_ELSE = 57,                  /* CMD_ELSE  */
  YYSYMBOL_E = 58                          /* E  */
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
#define YYFINAL  52
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   283

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
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
      41,    42,    31,    29,    40,    30,    37,    32,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    34,
      27,    26,    28,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    38,     2,    39,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    35,     2,    36,     2,     2,     2,     2,
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
       0,   143,   143,   146,   147,   150,   151,   152,   153,   154,
     155,   156,   157,   160,   161,   162,   163,   164,   165,   166,
     167,   170,   171,   174,   175,   176,   179,   180,   181,   184,
     185,   186,   189,   190,   191,   193,   194,   195,   198,   214,
     230,   244,   257,   258,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281
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
  "'+'", "'-'", "'*'", "'/'", "'%'", "';'", "'{'", "'}'", "'.'", "'['",
  "']'", "','", "'('", "')'", "$accept", "S", "CMDs", "CMD", "A", "IDls",
  "CAMPO", "CMD_DECL", "LET_VAR", "CONST_VAR", "VAR_VAR", "CMD_WHILE",
  "CMD_FOR", "CMD_IF", "CMD_ELSE", "E", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-41)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-37)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     126,   120,   -40,    70,    19,    -8,    -5,    45,    49,    61,
     -41,   126,    66,   126,   -41,    50,    57,    51,   -41,   -41,
     -41,    70,   -41,    70,    65,    70,   -41,    70,    44,   -41,
     -41,   -41,    73,   -41,   -41,    70,    70,    17,   189,    34,
     -41,   126,    70,    60,    52,   -24,    56,   -41,    12,    58,
     -41,   118,   -41,   -41,   -41,    70,   -41,    70,   -41,   243,
     243,    34,   171,    -2,   -41,    24,    34,   -41,   -12,   139,
     -41,    70,    70,    70,    70,    70,    70,    70,    70,    70,
     -41,    70,   146,    70,    45,    70,    45,    70,    45,   -41,
     243,   243,   -41,    34,   126,   -41,   243,   250,   250,   250,
     -12,   -12,   -41,   -41,   -41,   197,   126,   243,    52,   216,
      52,   224,    52,   -41,    42,     5,   -41,   126,    62,   -41,
      55,   -41,    70,   126,   164,   -41,   126,    42,   -41
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      12,     0,     0,     2,     4,     0,     0,     0,    11,     9,
       8,     0,    19,     0,     0,     0,    21,     0,    25,    58,
      60,    59,     0,    63,    62,     0,     0,     0,     0,    17,
      18,     0,     0,    29,    26,    29,     0,    27,    29,     0,
      28,     0,     1,     3,     7,     0,    20,     0,     5,    15,
      13,    25,     0,     0,    56,    53,    22,    55,    61,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       6,     0,     0,     0,     0,     0,     0,     0,     0,    10,
      16,    14,    23,    25,     0,    64,    52,    51,    44,    45,
      46,    47,    48,    49,    50,     0,     0,    30,    31,    30,
      34,    30,    37,    24,    43,     0,    38,     0,     0,    40,
       0,    42,     0,     0,     0,    39,     0,    43,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -41,   -41,    90,    -7,   -13,     0,   -16,   -41,     7,   -41,
     -41,   -41,   -41,   -41,   -22,   -18
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    37,    26,    17,    44,    47,
      50,    18,    19,    20,   119,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      16,    27,    85,    59,    40,    60,    53,    62,     1,    63,
     -32,    16,    65,    16,    72,    46,    49,    68,    69,    77,
      78,    79,    39,     4,    82,    73,    74,    75,    76,    77,
      78,    79,    67,    41,    81,    70,    42,    90,    87,    91,
      94,    16,   -21,    71,    53,    92,   -35,   117,    43,   118,
     -21,    16,    45,    96,    97,    98,    99,   100,   101,   102,
     103,   104,    64,   105,    48,   107,    52,   109,    61,   111,
     -22,    24,    25,    28,    55,    56,    66,   113,    29,    30,
      31,    24,    25,    57,    54,    58,    83,   114,    32,    33,
      34,   108,    84,   110,    16,   112,    86,   123,    88,   116,
      35,    51,   120,   122,   124,   128,    16,     0,     0,     0,
     121,    36,     0,     0,     0,    16,   125,    16,     0,   127,
       0,     1,     2,    16,     3,     0,    16,     0,     0,     1,
       2,     0,     3,     0,     0,     0,     4,    21,    22,     5,
       6,     7,     8,     9,     4,     0,    23,     5,     6,     7,
       8,     9,    10,    11,    89,    72,     0,    24,    25,     0,
      10,    11,    72,     0,     0,     0,    73,    74,    75,    76,
      77,    78,    79,    73,    74,    75,    76,    77,    78,    79,
      72,    95,     0,     0,     0,     0,     0,    72,   106,     0,
       0,    73,    74,    75,    76,    77,    78,    79,    73,    74,
      75,    76,    77,    78,    79,    72,   126,     0,     0,     0,
      93,     0,     0,    72,     0,     0,    73,    74,    75,    76,
      77,    78,    79,    80,    73,    74,    75,    76,    77,    78,
      79,   115,    72,     0,     0,     0,     0,     0,     0,     0,
      72,     0,     0,    73,    74,    75,    76,    77,    78,    79,
     -33,    73,    74,    75,    76,    77,    78,    79,   -36,    72,
       0,     0,     0,     0,     0,     0,   -37,     0,     0,     0,
      73,    74,    75,    76,    77,    78,    79,   -37,   -37,    75,
      76,    77,    78,    79
};

static const yytype_int8 yycheck[] =
{
       0,    41,    26,    21,     4,    23,    13,    25,     3,    27,
      34,    11,    28,    13,    16,     8,     9,    35,    36,    31,
      32,    33,     3,    18,    42,    27,    28,    29,    30,    31,
      32,    33,    32,    41,    41,    18,    41,    55,    26,    57,
      42,    41,    18,    26,    51,    61,    34,     5,     3,     7,
      26,    51,     3,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    18,    81,     3,    83,     0,    85,     3,    87,
      26,    37,    38,     3,    17,    18,     3,    93,     8,     9,
      10,    37,    38,    26,    34,    34,    26,    94,    18,    19,
      20,    84,    40,    86,    94,    88,    40,    42,    40,   106,
      30,    11,   115,    41,   122,   127,   106,    -1,    -1,    -1,
     117,    41,    -1,    -1,    -1,   115,   123,   117,    -1,   126,
      -1,     3,     4,   123,     6,    -1,   126,    -1,    -1,     3,
       4,    -1,     6,    -1,    -1,    -1,    18,    17,    18,    21,
      22,    23,    24,    25,    18,    -1,    26,    21,    22,    23,
      24,    25,    34,    35,    36,    16,    -1,    37,    38,    -1,
      34,    35,    16,    -1,    -1,    -1,    27,    28,    29,    30,
      31,    32,    33,    27,    28,    29,    30,    31,    32,    33,
      16,    42,    -1,    -1,    -1,    -1,    -1,    16,    42,    -1,
      -1,    27,    28,    29,    30,    31,    32,    33,    27,    28,
      29,    30,    31,    32,    33,    16,    42,    -1,    -1,    -1,
      39,    -1,    -1,    16,    -1,    -1,    27,    28,    29,    30,
      31,    32,    33,    34,    27,    28,    29,    30,    31,    32,
      33,    34,    16,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    -1,    -1,    27,    28,    29,    30,    31,    32,    33,
      34,    27,    28,    29,    30,    31,    32,    33,    34,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    -1,    -1,
      27,    28,    29,    30,    31,    32,    33,    27,    28,    29,
      30,    31,    32,    33
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     6,    18,    21,    22,    23,    24,    25,
      34,    35,    44,    45,    46,    47,    48,    50,    54,    55,
      56,    17,    18,    26,    37,    38,    49,    41,     3,     8,
       9,    10,    18,    19,    20,    30,    41,    48,    58,     3,
      48,    41,    41,     3,    51,     3,    51,    52,     3,    51,
      53,    45,     0,    46,    34,    17,    18,    26,    34,    58,
      58,     3,    58,    58,    18,    49,     3,    48,    58,    58,
      18,    26,    16,    27,    28,    29,    30,    31,    32,    33,
      34,    46,    58,    26,    40,    26,    40,    26,    40,    36,
      58,    58,    49,    39,    42,    42,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    42,    58,    51,    58,
      51,    58,    51,    49,    46,    34,    46,     5,     7,    57,
      47,    46,    41,    42,    58,    46,    42,    46,    57
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    46,    46,
      46,    46,    46,    47,    47,    47,    47,    47,    47,    47,
      47,    48,    48,    49,    49,    49,    50,    50,    50,    51,
      51,    51,    52,    52,    52,    53,    53,    53,    54,    55,
      56,    57,    57,    57,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     3,     2,     1,     1,
       3,     1,     1,     3,     3,     3,     3,     2,     2,     2,
       2,     2,     1,     3,     4,     0,     2,     2,     2,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     5,     8,
       6,     6,     2,     0,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     1,     1,
       1,     2,     1,     1,     3
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
#line 143 "mini_js.y"
         { print( resolve_enderecos( yyvsp[0].c + "." ) ); }
#line 1406 "mini_js.tab.c"
    break;

  case 3: /* CMDs: CMDs CMD  */
#line 146 "mini_js.y"
                 {yyval.c = yyvsp[-1].c + yyvsp[0].c;}
#line 1412 "mini_js.tab.c"
    break;

  case 6: /* CMD: PRINT E ';'  */
#line 151 "mini_js.y"
                  { yyval.c = yyvsp[-1].c + "println" + "#"; }
#line 1418 "mini_js.tab.c"
    break;

  case 10: /* CMD: '{' CMDs '}'  */
#line 155 "mini_js.y"
                   {yyval.c = yyvsp[-1].c;}
#line 1424 "mini_js.tab.c"
    break;

  case 12: /* CMD: ';'  */
#line 157 "mini_js.y"
          {yyval.clear();}
#line 1430 "mini_js.tab.c"
    break;

  case 13: /* A: ID '=' E  */
#line 160 "mini_js.y"
                      {yyval.c = yyvsp[-2].c + yyvsp[0].c + "=" + "^";}
#line 1436 "mini_js.tab.c"
    break;

  case 14: /* A: IDls '=' E  */
#line 161 "mini_js.y"
                      {yyval.c = yyvsp[-2].c + yyvsp[0].c + "[=]" + "^";}
#line 1442 "mini_js.tab.c"
    break;

  case 15: /* A: ID MAIS_IGUAL E  */
#line 162 "mini_js.y"
                      {yyval.c = yyvsp[-2].c + yyvsp[-2].c + "@" + yyvsp[0].c + "+" + "=" + "^";}
#line 1448 "mini_js.tab.c"
    break;

  case 16: /* A: IDls MAIS_IGUAL E  */
#line 163 "mini_js.y"
                       {yyval.c = yyvsp[-2].c + yyvsp[-2].c + "[@]" + yyvsp[0].c + "+" + "[=]" + "^";}
#line 1454 "mini_js.tab.c"
    break;

  case 17: /* A: MAIS_MAIS ID  */
#line 164 "mini_js.y"
                       {yyval.c = yyvsp[0].c + yyvsp[0].c + "@" + "1" + "+" + "=" + "^";}
#line 1460 "mini_js.tab.c"
    break;

  case 18: /* A: MAIS_MAIS IDls  */
#line 165 "mini_js.y"
                       {yyval.c = yyvsp[0].c + yyvsp[0].c + "[@]" + "1" + "+" + "[=]" + "^";}
#line 1466 "mini_js.tab.c"
    break;

  case 19: /* A: ID MAIS_MAIS  */
#line 166 "mini_js.y"
                       {yyval.c = yyvsp[-1].c + yyvsp[-1].c + "@" + "1" + "+" + "=" + "^";}
#line 1472 "mini_js.tab.c"
    break;

  case 20: /* A: IDls MAIS_MAIS  */
#line 167 "mini_js.y"
                       {yyval.c = yyvsp[-1].c + yyvsp[-1].c + "[@]" + "1" + "+" + "[=]" + "^";}
#line 1478 "mini_js.tab.c"
    break;

  case 21: /* IDls: ID CAMPO  */
#line 170 "mini_js.y"
                 {yyval.c = yyvsp[-1].c + "@" + limpAcesso(yyvsp[0].c); }
#line 1484 "mini_js.tab.c"
    break;

  case 23: /* CAMPO: '.' ID CAMPO  */
#line 174 "mini_js.y"
                     {yyval.c = yyvsp[-1].c + "[@]" + yyvsp[0].c; }
#line 1490 "mini_js.tab.c"
    break;

  case 24: /* CAMPO: '[' E ']' CAMPO  */
#line 175 "mini_js.y"
                         {yyval.c = yyvsp[-2].c + "[@]" + yyvsp[0].c;}
#line 1496 "mini_js.tab.c"
    break;

  case 25: /* CAMPO: %empty  */
#line 176 "mini_js.y"
        {yyval.clear();}
#line 1502 "mini_js.tab.c"
    break;

  case 26: /* CMD_DECL: LET LET_VAR  */
#line 179 "mini_js.y"
                       { yyval.c = yyvsp[0].c; }
#line 1508 "mini_js.tab.c"
    break;

  case 27: /* CMD_DECL: CONST CONST_VAR  */
#line 180 "mini_js.y"
                          {yyval.c = yyvsp[0].c;}
#line 1514 "mini_js.tab.c"
    break;

  case 28: /* CMD_DECL: VAR VAR_VAR  */
#line 181 "mini_js.y"
                       {yyval.c = yyvsp[0].c;}
#line 1520 "mini_js.tab.c"
    break;

  case 29: /* LET_VAR: ID  */
#line 184 "mini_js.y"
              { yyval.c = yyvsp[0].c + "&";  insere_tabela_de_simbolos( DeclLet, yyvsp[0] );}
#line 1526 "mini_js.tab.c"
    break;

  case 30: /* LET_VAR: ID '=' E  */
#line 185 "mini_js.y"
                   {yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + yyvsp[0].c + "=" + "^"; insere_tabela_de_simbolos( DeclLet, yyvsp[-2] ); }
#line 1532 "mini_js.tab.c"
    break;

  case 31: /* LET_VAR: LET_VAR ',' LET_VAR  */
#line 186 "mini_js.y"
                              {yyval.c = yyvsp[-2].c + yyvsp[0].c;}
#line 1538 "mini_js.tab.c"
    break;

  case 32: /* CONST_VAR: ID  */
#line 189 "mini_js.y"
                { yyval.c = yyvsp[0].c + "&";  insere_tabela_de_simbolos( DeclConst, yyvsp[0] );}
#line 1544 "mini_js.tab.c"
    break;

  case 33: /* CONST_VAR: ID '=' E  */
#line 190 "mini_js.y"
                   {yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + yyvsp[0].c + "=" + "^"; insere_tabela_de_simbolos( DeclConst, yyvsp[-2] ); }
#line 1550 "mini_js.tab.c"
    break;

  case 34: /* CONST_VAR: LET_VAR ',' LET_VAR  */
#line 191 "mini_js.y"
                              {yyval.c = yyvsp[-2].c + yyvsp[0].c;}
#line 1556 "mini_js.tab.c"
    break;

  case 35: /* VAR_VAR: ID  */
#line 193 "mini_js.y"
              { yyval.c = yyvsp[0].c + "&";  insere_tabela_de_simbolos( DeclVar, yyvsp[0] );}
#line 1562 "mini_js.tab.c"
    break;

  case 36: /* VAR_VAR: ID '=' E  */
#line 194 "mini_js.y"
                   {yyval.c = yyvsp[-2].c + "&" + yyvsp[-2].c + yyvsp[0].c + "=" + "^"; insere_tabela_de_simbolos( DeclVar, yyvsp[-2] ); }
#line 1568 "mini_js.tab.c"
    break;

  case 37: /* VAR_VAR: LET_VAR ',' LET_VAR  */
#line 195 "mini_js.y"
                              {yyval.c = yyvsp[-2].c + yyvsp[0].c;}
#line 1574 "mini_js.tab.c"
    break;

  case 38: /* CMD_WHILE: WHILE '(' E ')' CMD  */
#line 199 "mini_js.y"
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
#line 1593 "mini_js.tab.c"
    break;

  case 39: /* CMD_FOR: FOR '(' CMD E ';' A ')' CMD  */
#line 215 "mini_js.y"
        {
          string inicio_for = gera_label("inicio_for");
          string fim_for = gera_label("fim_for");
          string definicao_inicio_for = ":" + inicio_for;
          string definicao_fim_for = ":" + fim_for;

          yyval.c = yyvsp[-5].c + yyvsp[-4].c + 
              inicio_for + "?" +     //Entra no for?
              fim_for + "#" +
              definicao_inicio_for + 
              yyvsp[0].c + yyvsp[-2].c + yyvsp[-4].c + 
              inicio_for + "?" +    //Executa comando e verifica
              definicao_fim_for;  
        }
#line 1612 "mini_js.tab.c"
    break;

  case 40: /* CMD_IF: IF '(' E ')' CMD CMD_ELSE  */
#line 231 "mini_js.y"
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
#line 1629 "mini_js.tab.c"
    break;

  case 41: /* CMD_ELSE: ELSE_IF '(' E ')' CMD CMD_ELSE  */
#line 245 "mini_js.y"
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
#line 1646 "mini_js.tab.c"
    break;

  case 42: /* CMD_ELSE: ELSE CMD  */
#line 257 "mini_js.y"
                    {yyval.c = yyvsp[0].c;}
#line 1652 "mini_js.tab.c"
    break;

  case 43: /* CMD_ELSE: %empty  */
#line 258 "mini_js.y"
           {yyval.clear();}
#line 1658 "mini_js.tab.c"
    break;

  case 44: /* E: E '<' E  */
#line 261 "mini_js.y"
            { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1664 "mini_js.tab.c"
    break;

  case 45: /* E: E '>' E  */
#line 262 "mini_js.y"
            { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1670 "mini_js.tab.c"
    break;

  case 46: /* E: E '+' E  */
#line 263 "mini_js.y"
            { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c; }
#line 1676 "mini_js.tab.c"
    break;

  case 47: /* E: E '-' E  */
#line 264 "mini_js.y"
            { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c;}
#line 1682 "mini_js.tab.c"
    break;

  case 48: /* E: E '*' E  */
#line 265 "mini_js.y"
            { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c;}
#line 1688 "mini_js.tab.c"
    break;

  case 49: /* E: E '/' E  */
#line 266 "mini_js.y"
            { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c;}
#line 1694 "mini_js.tab.c"
    break;

  case 50: /* E: E '%' E  */
#line 267 "mini_js.y"
            { yyval.c = yyvsp[-2].c + yyvsp[0].c + yyvsp[-1].c;}
#line 1700 "mini_js.tab.c"
    break;

  case 51: /* E: E IGUAL E  */
#line 268 "mini_js.y"
              {yyval.c = yyvsp[-2].c + yyvsp[0].c + "==";}
#line 1706 "mini_js.tab.c"
    break;

  case 52: /* E: IDls '=' E  */
#line 269 "mini_js.y"
               {yyval.c = yyvsp[-2].c + yyvsp[0].c + "=";}
#line 1712 "mini_js.tab.c"
    break;

  case 53: /* E: ID CAMPO  */
#line 270 "mini_js.y"
             {yyval.c = yyvsp[-1].c + "@" + yyvsp[0].c ; }
#line 1718 "mini_js.tab.c"
    break;

  case 54: /* E: MAIS_MAIS ID  */
#line 271 "mini_js.y"
                  {yyval.c = yyvsp[0].c + yyvsp[0].c + "@" + "1" + "+" + "=";}
#line 1724 "mini_js.tab.c"
    break;

  case 55: /* E: MAIS_MAIS IDls  */
#line 272 "mini_js.y"
                    {yyval.c = yyvsp[0].c + yyvsp[0].c + "[@]" + "1" + "+" + "[=]";}
#line 1730 "mini_js.tab.c"
    break;

  case 56: /* E: ID MAIS_MAIS  */
#line 273 "mini_js.y"
                 {yyval.c = yyvsp[-1].c + yyvsp[-1].c + "@" + "1" + "+" + "=" + "1"  + "-";}
#line 1736 "mini_js.tab.c"
    break;

  case 57: /* E: IDls MAIS_MAIS  */
#line 274 "mini_js.y"
                    {yyval.c = yyvsp[0].c + yyvsp[-1].c + "[@]" + "1" + "+" + "[=]" + "1"  + "-";}
#line 1742 "mini_js.tab.c"
    break;

  case 61: /* E: '-' E  */
#line 278 "mini_js.y"
          {yyval.c = "0" + yyvsp[0].c + "-";}
#line 1748 "mini_js.tab.c"
    break;

  case 64: /* E: '(' E ')'  */
#line 281 "mini_js.y"
              {yyval.c = yyvsp[-1].c;}
#line 1754 "mini_js.tab.c"
    break;


#line 1758 "mini_js.tab.c"

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

#line 285 "mini_js.y"


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
