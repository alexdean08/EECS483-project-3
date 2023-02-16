/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 11 "parser.y" /* yacc.c:339  */


/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine


#line 82 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_Void = 258,
    T_Bool = 259,
    T_Int = 260,
    T_Double = 261,
    T_String = 262,
    T_Class = 263,
    T_LessEqual = 264,
    T_GreaterEqual = 265,
    T_Equal = 266,
    T_NotEqual = 267,
    T_Dims = 268,
    T_And = 269,
    T_Or = 270,
    T_Null = 271,
    T_Extends = 272,
    T_This = 273,
    T_Interface = 274,
    T_Implements = 275,
    T_While = 276,
    T_For = 277,
    T_If = 278,
    T_Else = 279,
    T_Return = 280,
    T_Break = 281,
    T_New = 282,
    T_NewArray = 283,
    T_Print = 284,
    T_ReadInteger = 285,
    T_ReadLine = 286,
    T_Identifier = 287,
    T_StringConstant = 288,
    T_IntConstant = 289,
    T_DoubleConstant = 290,
    T_BoolConstant = 291,
    ArithmeticMinus = 292
  };
#endif
/* Tokens.  */
#define T_Void 258
#define T_Bool 259
#define T_Int 260
#define T_Double 261
#define T_String 262
#define T_Class 263
#define T_LessEqual 264
#define T_GreaterEqual 265
#define T_Equal 266
#define T_NotEqual 267
#define T_Dims 268
#define T_And 269
#define T_Or 270
#define T_Null 271
#define T_Extends 272
#define T_This 273
#define T_Interface 274
#define T_Implements 275
#define T_While 276
#define T_For 277
#define T_If 278
#define T_Else 279
#define T_Return 280
#define T_Break 281
#define T_New 282
#define T_NewArray 283
#define T_Print 284
#define T_ReadInteger 285
#define T_ReadLine 286
#define T_Identifier 287
#define T_StringConstant 288
#define T_IntConstant 289
#define T_DoubleConstant 290
#define T_BoolConstant 291
#define ArithmeticMinus 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 41 "parser.y" /* yacc.c:355  */

    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    Decl *decl;
    List<Decl*> *declList;
    
    VarDecl *vd;
    ClassDecl *cd;
    Decl *cc;
    List<Decl*> *lcc;

    InterfaceDecl *id;
    FnDecl *fd;
    Type *t;
    NamedType *nt;
    List<NamedType*> *ntl;
    ArrayType *at;
    StmtBlock *sb;
    StmtBlock *fc;
    Stmt *s;
    IfStmt *ifs;
    WhileStmt *ws;
    ForStmt *fs;
    BreakStmt *bs;
    ReturnStmt *rs;
    PrintStmt *ps;
    Expr *e;
    Call *c;
    LValue *lv;

    List<VarDecl*> *vl;
    List<Expr*> *el;
    List<Stmt*> *ls;
    List<VarDecl*> *vdl;
    Expr *con;
    EmptyExpr *ee;

    //CaseStmt* cs;
    //List<CaseStmt*>* lcs;
    //SwitchStmt* ss;
    //DefaultCaseStmt* de;

    List<Expr*>* act;

    List<Decl*>* pl;
    FnDecl* pro;

#line 247 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 278 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   734

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  56
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  228

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   292

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    45,     2,     2,     2,    44,     2,     2,
      53,    54,    42,    40,    52,    41,    48,    43,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    49,
      38,    37,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    47,     2,    55,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    50,     2,    51,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    46
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   184,   184,   196,   197,   200,   201,   202,   203,   206,
     210,   211,   212,   213,   216,   217,   218,   221,   222,   227,
     228,   231,   234,   235,   238,   239,   240,   243,   244,   247,
     250,   255,   258,   259,   262,   263,   266,   267,   268,   269,
     272,   273,   274,   275,   276,   277,   278,   280,   281,   284,
     285,   288,   291,   292,   293,   294,   297,   300,   301,   304,
     321,   324,   325,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   357,   358,
     361,   362,   363,   366,   367,   368,   375,   376,   377,   378,
     379,   382,   383,   384,   385,   386,   387,   390,   393
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_Void", "T_Bool", "T_Int", "T_Double",
  "T_String", "T_Class", "T_LessEqual", "T_GreaterEqual", "T_Equal",
  "T_NotEqual", "T_Dims", "T_And", "T_Or", "T_Null", "T_Extends", "T_This",
  "T_Interface", "T_Implements", "T_While", "T_For", "T_If", "T_Else",
  "T_Return", "T_Break", "T_New", "T_NewArray", "T_Print", "T_ReadInteger",
  "T_ReadLine", "T_Identifier", "T_StringConstant", "T_IntConstant",
  "T_DoubleConstant", "T_BoolConstant", "'='", "'<'", "'>'", "'+'", "'-'",
  "'*'", "'/'", "'%'", "'!'", "ArithmeticMinus", "'['", "'.'", "';'",
  "'{'", "'}'", "','", "'('", "')'", "']'", "$accept", "Program",
  "DeclList", "Decl", "VarDecl", "ClassDecl", "ListClassCode", "ClassCode",
  "NamedTypeList", "InterfaceDecl", "PrototypeList", "VariableList",
  "Prototype", "FnDecl", "FunctionCode", "ListVarDecl", "ListStmts",
  "StmtBlock", "Stmt", "IfStmt", "WhileStmt", "ForStmt", "BreakStmt",
  "ReturnStmt", "PrintStmt", "EmptyExpr", "ExprList", "Expr", "Call",
  "Actuals", "LValue", "Constant", "Type", "NamedType", "ArrayType", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    61,    60,    62,
      43,    45,    42,    47,    37,    33,   292,    91,    46,    59,
     123,   125,    44,    40,    41,    93
};
# endif

#define YYPACT_NINF -113

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-113)))

#define YYTABLE_NINF -108

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-108)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     241,   -13,  -113,  -113,  -113,  -113,     8,    18,  -113,    54,
     241,  -113,  -113,  -113,  -113,  -113,    10,  -113,  -113,     4,
      -6,    11,  -113,  -113,  -113,   -21,   110,    26,    26,    32,
    -113,  -113,   110,    51,    14,    -5,    57,  -113,  -113,    87,
    -113,  -113,   151,    58,   110,    15,  -113,    26,    32,    32,
      26,  -113,  -113,    50,  -113,  -113,    21,    15,    28,   146,
    -113,    70,   200,   205,  -113,    53,    65,  -113,  -113,  -113,
    -113,    79,    86,    91,   681,    72,   112,   117,   131,   132,
     133,    -1,  -113,  -113,  -113,  -113,   681,   681,  -113,   681,
    -113,  -113,   146,   657,    97,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,   415,  -113,   103,  -113,    68,    32,  -113,  -113,
     110,   110,   681,   681,   681,   135,   111,   456,  -113,   168,
     681,   681,    48,   109,   681,    49,    49,   243,  -113,   657,
    -113,  -113,   681,   681,   681,   681,   681,   681,   681,   681,
     681,   681,   681,   681,   681,   681,   169,  -113,   681,   176,
     210,    73,    77,   284,   177,   468,   301,  -113,  -113,   175,
     400,    89,   562,  -113,  -113,   562,    95,  -113,   180,   180,
     584,   584,   624,   573,   180,   180,   150,   150,    49,    49,
      49,   224,   178,   562,  -113,   181,   191,   657,   681,   681,
     657,  -113,   110,   681,   192,   681,  -113,  -113,   681,  -113,
    -113,  -113,   509,   521,   219,    -3,   562,  -113,   562,   107,
     681,   681,   657,  -113,  -113,   196,   342,   215,   359,  -113,
     657,   657,   657,   657,  -113,  -113,  -113,  -113
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,   105,   103,   106,   104,     0,     0,   107,     0,
       2,     4,     5,     6,     7,     8,     0,   101,   102,     0,
       0,     0,     1,     3,   108,     0,    26,     0,     0,    16,
      23,     9,    26,     0,     0,     0,     0,    20,    17,     0,
      15,    18,     0,     0,     0,     0,    25,     0,    16,    16,
       0,    10,    14,     0,    21,    22,     0,     0,     0,    39,
      30,     0,     0,     0,    19,     0,     0,    29,    24,   100,
      66,     0,     0,     0,    60,     0,     0,     0,     0,     0,
       0,    93,    99,    96,    97,    98,     0,     0,    48,     0,
      33,    46,    37,    38,     0,    35,    40,    41,    42,    43,
      44,    45,     0,    67,    65,    64,     0,    16,    11,    12,
      26,    26,     0,    60,     0,    93,     0,     0,    56,     0,
       0,     0,     0,     0,    92,    74,    83,     0,    32,    36,
      34,    31,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    47,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,    57,     0,
       0,     0,    62,    84,    85,    91,     0,    68,    76,    78,
      79,    80,    81,    82,    75,    77,    69,    70,    71,    72,
      73,     0,    94,    63,    13,     0,     0,     0,     0,     0,
       0,    86,     0,     0,     0,     0,    88,    95,    92,    28,
      27,    51,     0,     0,    49,     0,    61,    59,    90,     0,
      60,    60,     0,    87,    89,     0,     0,     0,     0,    50,
       0,     0,     0,     0,    55,    53,    54,    52
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -113,  -113,  -113,   249,     3,  -113,   -44,   -37,   223,  -113,
    -113,   -24,  -113,    20,   -28,  -113,   182,  -113,   -86,  -113,
    -113,  -113,  -113,  -113,  -113,  -112,  -113,   -65,  -113,    78,
    -113,  -113,   -26,    61,  -113
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     9,    10,    11,    38,    13,    39,    40,    36,    14,
      42,    33,    55,    41,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   116,   161,   102,   103,   166,
     104,   105,    16,    17,    18
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      34,   154,    52,    12,    62,    63,    34,   130,    43,   117,
      24,    27,  -107,    12,    28,    47,    56,    60,    58,    19,
      15,   125,   126,    24,   127,    52,    52,    24,    31,    67,
      15,  -107,    32,   106,    24,     1,     2,     3,     4,     5,
      20,    24,    25,   130,    29,    48,    46,   153,   155,   156,
      21,   213,   124,    66,    22,   160,   162,    26,     8,   165,
      68,    30,    90,   150,     8,    59,   106,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,    24,    65,   183,    34,    34,   151,   152,    35,    37,
       1,     2,     3,     4,     5,   128,   145,   146,   215,   217,
     149,   201,   163,    44,   204,    45,   110,    49,    37,    50,
      44,    64,    57,    52,     2,     3,     4,     5,   111,     8,
     107,   118,    50,   202,   203,    44,   219,   185,   206,    44,
     208,   186,   112,   165,   224,   225,   226,   227,    51,   113,
     148,   193,     8,   194,   114,   216,   218,   195,   131,   196,
       2,     3,     4,     5,    53,     2,     3,     4,     5,   195,
     157,   214,    69,   164,    70,   119,   205,    71,    72,    73,
     120,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,     8,   121,   122,   123,    86,   124,  -108,
    -108,    87,   142,   143,   144,    88,    59,   145,   146,    89,
     159,   182,    54,     1,     2,     3,     4,     5,     1,     2,
       3,     4,     5,     1,     2,     3,     4,     5,  -108,  -108,
     140,   141,   142,   143,   144,    31,   188,   145,   146,   191,
     199,   198,     8,   132,   133,   134,   135,     8,   136,   137,
     200,   207,     8,   212,     1,     2,     3,     4,     5,     6,
     220,   108,   132,   133,   134,   135,   109,   136,   137,    23,
       7,   184,   138,   139,   140,   141,   142,   143,   144,   222,
      61,   145,   146,     8,   129,     0,   209,     0,     0,   197,
       0,   138,   139,   140,   141,   142,   143,   144,     0,     0,
     145,   146,     0,   132,   133,   134,   135,   167,   136,   137,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     132,   133,   134,   135,     0,   136,   137,     0,     0,     0,
       0,     0,   138,   139,   140,   141,   142,   143,   144,     0,
       0,   145,   146,     0,     0,     0,     0,     0,   187,   138,
     139,   140,   141,   142,   143,   144,     0,     0,   145,   146,
       0,   132,   133,   134,   135,   190,   136,   137,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   132,   133,
     134,   135,     0,   136,   137,     0,     0,     0,     0,     0,
     138,   139,   140,   141,   142,   143,   144,     0,     0,   145,
     146,     0,     0,     0,     0,     0,   221,   138,   139,   140,
     141,   142,   143,   144,     0,     0,   145,   146,     0,   132,
     133,   134,   135,   223,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,   132,   133,   134,   135,     0,   136,
     137,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,   144,     0,     0,   145,   146,     0,
       0,     0,   192,   138,   139,   140,   141,   142,   143,   144,
       0,     0,   145,   146,   147,   132,   133,   134,   135,     0,
     136,   137,     0,     0,     0,     0,     0,   132,   133,   134,
     135,     0,   136,   137,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
     144,     0,     0,   145,   146,   158,   138,   139,   140,   141,
     142,   143,   144,     0,     0,   145,   146,   189,   132,   133,
     134,   135,     0,   136,   137,     0,     0,     0,     0,     0,
     132,   133,   134,   135,     0,   136,   137,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   138,   139,   140,
     141,   142,   143,   144,     0,     0,   145,   146,   210,   138,
     139,   140,   141,   142,   143,   144,     0,     0,   145,   146,
     211,   132,   133,   134,   135,     0,   136,   137,     0,     0,
       0,     0,   132,   133,   134,   135,     0,   136,     0,     0,
       0,     0,     0,   132,   133,  -108,  -108,     0,     0,     0,
     138,   139,   140,   141,   142,   143,   144,     0,     0,   145,
     146,   138,   139,   140,   141,   142,   143,   144,     0,     0,
     145,   146,   138,   139,   140,   141,   142,   143,   144,     0,
       0,   145,   146,   132,   133,   134,   135,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   138,   139,   140,   141,   142,   143,   144,     0,
       0,   145,   146,    69,     0,    70,     0,     0,    71,    72,
      73,     0,    74,    75,    76,    77,    78,    79,    80,   115,
      82,    83,    84,    85,     0,     0,     0,    69,    86,    70,
       0,     0,    87,     0,     0,     0,    88,    59,    76,    77,
      89,    79,    80,   115,    82,    83,    84,    85,     0,     0,
       0,     0,    86,     0,     0,     0,    87,     0,     0,     0,
       0,     0,     0,     0,    89
};

static const yytype_int16 yycheck[] =
{
      26,   113,    39,     0,    48,    49,    32,    93,    32,    74,
      13,    17,    13,    10,    20,    20,    42,    45,    44,    32,
       0,    86,    87,    13,    89,    62,    63,    13,    49,    57,
      10,    32,    53,    59,    13,     3,     4,     5,     6,     7,
      32,    13,    32,   129,    50,    50,    32,   112,   113,   114,
      32,    54,    53,    32,     0,   120,   121,    53,    32,   124,
      32,    50,    59,   107,    32,    50,    92,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,    13,    32,   148,   110,   111,   110,   111,    27,    28,
       3,     4,     5,     6,     7,    92,    47,    48,   210,   211,
      32,   187,    54,    52,   190,    54,    53,    50,    47,    52,
      52,    50,    54,   150,     4,     5,     6,     7,    53,    32,
      50,    49,    52,   188,   189,    52,   212,    54,   193,    52,
     195,    54,    53,   198,   220,   221,   222,   223,    51,    53,
      37,    52,    32,    54,    53,   210,   211,    52,    51,    54,
       4,     5,     6,     7,     3,     4,     5,     6,     7,    52,
      49,    54,    16,    54,    18,    53,   192,    21,    22,    23,
      53,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    32,    53,    53,    53,    41,    53,     9,
      10,    45,    42,    43,    44,    49,    50,    47,    48,    53,
      32,    32,    51,     3,     4,     5,     6,     7,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,    38,    39,
      40,    41,    42,    43,    44,    49,    49,    47,    48,    54,
      49,    53,    32,     9,    10,    11,    12,    32,    14,    15,
      49,    49,    32,    24,     3,     4,     5,     6,     7,     8,
      54,    51,     9,    10,    11,    12,    51,    14,    15,    10,
      19,    51,    38,    39,    40,    41,    42,    43,    44,    54,
      47,    47,    48,    32,    92,    -1,   198,    -1,    -1,    55,
      -1,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      47,    48,    -1,     9,    10,    11,    12,    54,    14,    15,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,    -1,    -1,    -1,    -1,    -1,    54,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    47,    48,
      -1,     9,    10,    11,    12,    54,    14,    15,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    10,
      11,    12,    -1,    14,    15,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    47,
      48,    -1,    -1,    -1,    -1,    -1,    54,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    47,    48,    -1,     9,
      10,    11,    12,    54,    14,    15,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     9,    10,    11,    12,    -1,    14,
      15,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    -1,    -1,    47,    48,    -1,
      -1,    -1,    52,    38,    39,    40,    41,    42,    43,    44,
      -1,    -1,    47,    48,    49,     9,    10,    11,    12,    -1,
      14,    15,    -1,    -1,    -1,    -1,    -1,     9,    10,    11,
      12,    -1,    14,    15,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    42,    43,
      44,    -1,    -1,    47,    48,    49,    38,    39,    40,    41,
      42,    43,    44,    -1,    -1,    47,    48,    49,     9,    10,
      11,    12,    -1,    14,    15,    -1,    -1,    -1,    -1,    -1,
       9,    10,    11,    12,    -1,    14,    15,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      41,    42,    43,    44,    -1,    -1,    47,    48,    49,    38,
      39,    40,    41,    42,    43,    44,    -1,    -1,    47,    48,
      49,     9,    10,    11,    12,    -1,    14,    15,    -1,    -1,
      -1,    -1,     9,    10,    11,    12,    -1,    14,    -1,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    -1,    -1,    -1,
      38,    39,    40,    41,    42,    43,    44,    -1,    -1,    47,
      48,    38,    39,    40,    41,    42,    43,    44,    -1,    -1,
      47,    48,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    42,    43,    44,    -1,
      -1,    47,    48,    16,    -1,    18,    -1,    -1,    21,    22,
      23,    -1,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    16,    41,    18,
      -1,    -1,    45,    -1,    -1,    -1,    49,    50,    27,    28,
      53,    30,    31,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,    19,    32,    57,
      58,    59,    60,    61,    65,    69,    88,    89,    90,    32,
      32,    32,     0,    59,    13,    32,    53,    17,    20,    50,
      50,    49,    53,    67,    88,    89,    64,    89,    60,    62,
      63,    69,    66,    67,    52,    54,    32,    20,    50,    50,
      52,    51,    63,     3,    51,    68,    88,    54,    88,    50,
      70,    64,    62,    62,    89,    32,    32,    70,    32,    16,
      18,    21,    22,    23,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    41,    45,    49,    53,
      60,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    83,    84,    86,    87,    88,    50,    51,    51,
      53,    53,    53,    53,    53,    32,    81,    83,    49,    53,
      53,    53,    53,    53,    53,    83,    83,    83,    60,    72,
      74,    51,     9,    10,    11,    12,    14,    15,    38,    39,
      40,    41,    42,    43,    44,    47,    48,    49,    37,    32,
      62,    67,    67,    83,    81,    83,    83,    49,    49,    32,
      83,    82,    83,    54,    54,    83,    85,    54,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    32,    83,    51,    54,    54,    54,    49,    49,
      54,    54,    52,    52,    54,    52,    54,    55,    53,    49,
      49,    74,    83,    83,    74,    88,    83,    49,    83,    85,
      49,    49,    24,    54,    54,    81,    83,    81,    83,    74,
      54,    54,    54,    54,    74,    74,    74,    74
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    56,    57,    58,    58,    59,    59,    59,    59,    60,
      61,    61,    61,    61,    62,    62,    62,    63,    63,    64,
      64,    65,    66,    66,    67,    67,    67,    68,    68,    69,
      69,    70,    71,    71,    72,    72,    73,    73,    73,    73,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    75,
      75,    76,    77,    77,    77,    77,    78,    79,    79,    80,
      81,    82,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    84,    84,
      85,    85,    85,    86,    86,    86,    87,    87,    87,    87,
      87,    88,    88,    88,    88,    88,    88,    89,    90
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     3,
       5,     7,     7,     9,     2,     1,     0,     1,     1,     3,
       1,     5,     2,     0,     4,     2,     0,     6,     6,     6,
       6,     3,     2,     1,     2,     1,     2,     1,     1,     0,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     5,
       7,     5,     9,     9,     9,     9,     2,     3,     3,     5,
       0,     3,     1,     3,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     3,     3,     4,     6,     4,     6,
       3,     1,     0,     1,     3,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 184 "parser.y" /* yacc.c:1646  */
    { 
                                      (yylsp[0]); 
                                      /* pp2: The @1 is needed to convince 
                                       * yacc to set up yylloc. You can remove 
                                       * it once you have other uses of @n*/
                                      Program *program = new Program((yyvsp[0].declList));
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0) 
                                          program->Check();
                                    }
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 196 "parser.y" /* yacc.c:1646  */
    { ((yyval.declList)=(yyvsp[-1].declList))->Append((yyvsp[0].decl)); }
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 197 "parser.y" /* yacc.c:1646  */
    { ((yyval.declList) = new List<Decl*>)->Append((yyvsp[0].decl)); }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 206 "parser.y" /* yacc.c:1646  */
    { (yyval.vd) = new VarDecl(new Identifier((yylsp[-1]), (yyvsp[-1].identifier)), (yyvsp[-2].t)); }
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 210 "parser.y" /* yacc.c:1646  */
    { (yyval.cd) = new ClassDecl(new Identifier((yylsp[-3]), (yyvsp[-3].identifier)), NULL, new List<NamedType*>, (yyvsp[-1].lcc));}
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 211 "parser.y" /* yacc.c:1646  */
    { (yyval.cd) = new ClassDecl(new Identifier((yylsp[-5]), (yyvsp[-5].identifier)), (yyvsp[-3].nt), new List<NamedType*>, (yyvsp[-1].lcc));}
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 212 "parser.y" /* yacc.c:1646  */
    { (yyval.cd) = new ClassDecl(new Identifier((yylsp[-5]), (yyvsp[-5].identifier)), NULL, (yyvsp[-3].ntl), (yyvsp[-1].lcc));}
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 213 "parser.y" /* yacc.c:1646  */
    { (yyval.cd) = new ClassDecl(new Identifier((yylsp[-7]), (yyvsp[-7].identifier)), (yyvsp[-5].nt), (yyvsp[-3].ntl), (yyvsp[-1].lcc));}
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 216 "parser.y" /* yacc.c:1646  */
    { ((yyval.lcc)=(yyvsp[-1].lcc))->Append((yyvsp[0].cc)); }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 217 "parser.y" /* yacc.c:1646  */
    { ((yyval.lcc) = new List<Decl*>)->Append((yyvsp[0].cc)); }
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 218 "parser.y" /* yacc.c:1646  */
    { (yyval.lcc) = new List<Decl*>;}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 227 "parser.y" /* yacc.c:1646  */
    { ((yyval.ntl)=(yyvsp[-2].ntl))->Append((yyvsp[0].nt)); }
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 228 "parser.y" /* yacc.c:1646  */
    { ((yyval.ntl) = new List<NamedType*>)->Append((yyvsp[0].nt)); }
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 231 "parser.y" /* yacc.c:1646  */
    { (yyval.id)= new InterfaceDecl(new Identifier((yylsp[-3]), (yyvsp[-3].identifier)), (yyvsp[-1].pl)); }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 234 "parser.y" /* yacc.c:1646  */
    { ((yyval.pl)=(yyvsp[-1].pl))->Append((yyvsp[0].pro)); }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 235 "parser.y" /* yacc.c:1646  */
    { ((yyval.pl)=new List<Decl*>);}
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 238 "parser.y" /* yacc.c:1646  */
    { ((yyval.vl)=(yyvsp[-3].vl))->Append(new VarDecl(new Identifier((yylsp[0]), (yyvsp[0].identifier)), (yyvsp[-1].t))); }
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 239 "parser.y" /* yacc.c:1646  */
    { ((yyval.vl) = new List<VarDecl*>)->Append(new VarDecl(new Identifier((yylsp[0]), (yyvsp[0].identifier)), (yyvsp[-1].t))); }
#line 1819 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 240 "parser.y" /* yacc.c:1646  */
    { (yyval.vl) = new List<VarDecl*>; }
#line 1825 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 243 "parser.y" /* yacc.c:1646  */
    { (yyval.pro) = new FnDecl(new Identifier((yylsp[-4]), (yyvsp[-4].identifier)), (yyvsp[-5].t), (yyvsp[-2].vl));}
#line 1831 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 244 "parser.y" /* yacc.c:1646  */
    { (yyval.pro) = new FnDecl(new Identifier((yylsp[-4]), (yyvsp[-4].identifier)), Type::voidType, (yyvsp[-2].vl));}
#line 1837 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 247 "parser.y" /* yacc.c:1646  */
    { FnDecl* fnd = new FnDecl(new Identifier((yylsp[-4]), (yyvsp[-4].identifier)), (yyvsp[-5].t), (yyvsp[-2].vl));
                                                                            fnd->SetFunctionBody((yyvsp[0].fc));
                                                                            (yyval.fd) = fnd;}
#line 1845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 250 "parser.y" /* yacc.c:1646  */
    { FnDecl* fnd = new FnDecl(new Identifier((yylsp[-4]), (yyvsp[-4].identifier)), Type::voidType, (yyvsp[-2].vl));
                                                                            fnd->SetFunctionBody((yyvsp[0].fc));
                                                                            (yyval.fd) = fnd;}
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 255 "parser.y" /* yacc.c:1646  */
    { (yyval.fc)=(yyvsp[-1].sb); }
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 258 "parser.y" /* yacc.c:1646  */
    {((yyval.vdl) = (yyvsp[-1].vdl))->Append((yyvsp[0].vd));}
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 259 "parser.y" /* yacc.c:1646  */
    {((yyval.vdl) = new List<VarDecl*>)->Append((yyvsp[0].vd));}
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 262 "parser.y" /* yacc.c:1646  */
    { ((yyval.ls) = (yyvsp[-1].ls))->Append((yyvsp[0].s));}
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 263 "parser.y" /* yacc.c:1646  */
    { ((yyval.ls) = new List<Stmt*>)->Append((yyvsp[0].s));}
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 266 "parser.y" /* yacc.c:1646  */
    { ((yyval.sb) = new StmtBlock((yyvsp[-1].vdl), (yyvsp[0].ls))); }
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 267 "parser.y" /* yacc.c:1646  */
    { ((yyval.sb) = new StmtBlock((yyvsp[0].vdl), new List<Stmt*>)); }
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 268 "parser.y" /* yacc.c:1646  */
    {((yyval.sb) = new StmtBlock(new List<VarDecl*>, (yyvsp[0].ls))); }
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 269 "parser.y" /* yacc.c:1646  */
    {((yyval.sb) = new StmtBlock(new List<VarDecl*>, new List<Stmt*>));}
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 284 "parser.y" /* yacc.c:1646  */
    { (yyval.ifs) = new IfStmt((yyvsp[-2].e), (yyvsp[0].s), NULL);}
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 285 "parser.y" /* yacc.c:1646  */
    { (yyval.ifs) = new IfStmt((yyvsp[-4].e), (yyvsp[-2].s), (yyvsp[0].s));}
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 288 "parser.y" /* yacc.c:1646  */
    { (yyval.ws) = new WhileStmt((yyvsp[-2].e), (yyvsp[0].s));}
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 291 "parser.y" /* yacc.c:1646  */
    { (yyval.fs) = new ForStmt((yyvsp[-6].e), (yyvsp[-4].e), (yyvsp[-2].e), (yyvsp[0].s));}
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 292 "parser.y" /* yacc.c:1646  */
    { (yyval.fs) = new ForStmt((yyvsp[-6].ee), (yyvsp[-4].e), (yyvsp[-2].e), (yyvsp[0].s));}
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 293 "parser.y" /* yacc.c:1646  */
    { (yyval.fs) = new ForStmt((yyvsp[-6].e), (yyvsp[-4].e), (yyvsp[-2].ee), (yyvsp[0].s));}
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 294 "parser.y" /* yacc.c:1646  */
    { (yyval.fs) = new ForStmt((yyvsp[-6].ee), (yyvsp[-4].e), (yyvsp[-2].ee), (yyvsp[0].s));}
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 297 "parser.y" /* yacc.c:1646  */
    { (yyval.bs) = new BreakStmt((yylsp[-1]));}
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 300 "parser.y" /* yacc.c:1646  */
    { (yyval.rs) = new ReturnStmt((yylsp[-1]), (yyvsp[-1].e)); }
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 301 "parser.y" /* yacc.c:1646  */
    { (yyval.rs) = new ReturnStmt((yylsp[-2]), (yyvsp[-1].ee)); }
#line 1967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 304 "parser.y" /* yacc.c:1646  */
    { (yyval.ps) = new PrintStmt((yyvsp[-2].el)); }
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 321 "parser.y" /* yacc.c:1646  */
    {(yyval.ee) = new EmptyExpr();}
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 324 "parser.y" /* yacc.c:1646  */
    { ((yyval.el) = (yyvsp[-2].el))->Append((yyvsp[0].e)); }
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 325 "parser.y" /* yacc.c:1646  */
    { ((yyval.el) = new List<Expr*>)->Append((yyvsp[0].e)); }
#line 1991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 328 "parser.y" /* yacc.c:1646  */
    { (yyval.e) = new AssignExpr((yyvsp[-2].lv), new Operator((yylsp[-1]), "="), (yyvsp[0].e));}
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 331 "parser.y" /* yacc.c:1646  */
    { (yyval.e) = new This((yylsp[0]));}
#line 2003 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 333 "parser.y" /* yacc.c:1646  */
    { (yyval.e) = (yyvsp[-1].e);}
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 334 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new ArithmeticExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "+"), (yyvsp[0].e));}
#line 2015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 335 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new ArithmeticExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "-"), (yyvsp[0].e));}
#line 2021 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 336 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new ArithmeticExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "*"), (yyvsp[0].e));}
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 337 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new ArithmeticExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "/"), (yyvsp[0].e));}
#line 2033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 338 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new ArithmeticExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "%"), (yyvsp[0].e));}
#line 2039 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 339 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new ArithmeticExpr(new Operator((yylsp[0]), "-"), (yyvsp[0].e));}
#line 2045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 340 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new RelationalExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "<"), (yyvsp[0].e));}
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 341 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new RelationalExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "<="), (yyvsp[0].e));}
#line 2057 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 342 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new RelationalExpr((yyvsp[-2].e), new Operator((yylsp[-1]), ">"), (yyvsp[0].e));}
#line 2063 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 343 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new RelationalExpr((yyvsp[-2].e), new Operator((yylsp[-1]), ">="), (yyvsp[0].e));}
#line 2069 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 344 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new EqualityExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "=="), (yyvsp[0].e));}
#line 2075 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 345 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new EqualityExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "!="), (yyvsp[0].e));}
#line 2081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 346 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new LogicalExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "&&"), (yyvsp[0].e));}
#line 2087 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 347 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new LogicalExpr((yyvsp[-2].e), new Operator((yylsp[-1]), "||"), (yyvsp[0].e));}
#line 2093 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 348 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new LogicalExpr(new Operator((yylsp[-1]), "!"), (yyvsp[0].e));}
#line 2099 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 349 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new ReadIntegerExpr(Join((yylsp[-2]), (yylsp[0])));}
#line 2105 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 350 "parser.y" /* yacc.c:1646  */
    {(yyval.e) = new ReadLineExpr(Join((yylsp[-2]), (yylsp[0])));}
#line 2111 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 351 "parser.y" /* yacc.c:1646  */
    { (yyval.e) = new NewExpr(Join((yylsp[-3]), (yylsp[-2])), new NamedType(new Identifier((yylsp[-1]), (yyvsp[-1].identifier))));}
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 352 "parser.y" /* yacc.c:1646  */
    { (yyval.e) = new NewArrayExpr(Join((yylsp[-5]), (yylsp[0])), (yyvsp[-3].e), (yyvsp[-1].t));}
#line 2123 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 357 "parser.y" /* yacc.c:1646  */
    { (yyval.c) = new Call(Join((yylsp[-3]), (yylsp[0])), NULL, new Identifier((yylsp[-3]), (yyvsp[-3].identifier)), (yyvsp[-1].act));}
#line 2129 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 358 "parser.y" /* yacc.c:1646  */
    { (yyval.c) = new Call(Join((yylsp[-5]), (yylsp[0])), (yyvsp[-5].e), new Identifier((yylsp[-3]), (yyvsp[-3].identifier)), (yyvsp[-1].act));}
#line 2135 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 361 "parser.y" /* yacc.c:1646  */
    {((yyval.act) = (yyvsp[-2].act))->Append((yyvsp[0].e));}
#line 2141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 362 "parser.y" /* yacc.c:1646  */
    { ((yyval.act) = new List<Expr*>)->Append((yyvsp[0].e)); }
#line 2147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 363 "parser.y" /* yacc.c:1646  */
    { ((yyval.act) = new List<Expr*>);}
#line 2153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 366 "parser.y" /* yacc.c:1646  */
    {(yyval.lv)=new FieldAccess(NULL, new Identifier((yylsp[0]), (yyvsp[0].identifier)));}
#line 2159 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 367 "parser.y" /* yacc.c:1646  */
    {(yyval.lv)=new FieldAccess((yyvsp[-2].e), new Identifier((yylsp[0]), (yyvsp[0].identifier)));}
#line 2165 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 368 "parser.y" /* yacc.c:1646  */
    { (yyval.lv)= new ArrayAccess(Join((yylsp[-3]), (yylsp[0])), (yyvsp[-3].e), (yyvsp[-1].e));}
#line 2171 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 375 "parser.y" /* yacc.c:1646  */
    { (yyval.con) = new IntConstant((yylsp[0]), (yyvsp[0].integerConstant)); }
#line 2177 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 376 "parser.y" /* yacc.c:1646  */
    { (yyval.con) = new DoubleConstant((yylsp[0]), (yyvsp[0].doubleConstant)); }
#line 2183 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 377 "parser.y" /* yacc.c:1646  */
    { (yyval.con) = new BoolConstant((yylsp[0]), (yyvsp[0].boolConstant)); }
#line 2189 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 378 "parser.y" /* yacc.c:1646  */
    { (yyval.con) = new StringConstant((yylsp[0]), (yyvsp[0].stringConstant)); }
#line 2195 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 379 "parser.y" /* yacc.c:1646  */
    { (yyval.con) = new NullConstant((yylsp[0])); }
#line 2201 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 384 "parser.y" /* yacc.c:1646  */
    { (yyval.t) = Type::intType;}
#line 2207 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 385 "parser.y" /* yacc.c:1646  */
    { (yyval.t) = Type::stringType;}
#line 2213 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 386 "parser.y" /* yacc.c:1646  */
    {(yyval.t) = Type::boolType;}
#line 2219 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 387 "parser.y" /* yacc.c:1646  */
    {(yyval.t) = Type::doubleType;}
#line 2225 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 390 "parser.y" /* yacc.c:1646  */
    { (yyval.nt) = new NamedType(new Identifier((yylsp[0]), (yyvsp[0].identifier))); }
#line 2231 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 393 "parser.y" /* yacc.c:1646  */
    { (yyval.at) = new ArrayType((yylsp[-1]), (yyvsp[-1].t)); }
#line 2237 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2241 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 396 "parser.y" /* yacc.c:1906  */


/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}
