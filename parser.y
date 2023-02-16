/* File: parser.y
 * --------------
 * Yacc input file to generate the parser for the compiler.
 *
 * pp2: your job is to write a parser that will construct the parse tree
 *      and if no parse errors were found, print it.  The parser should 
 *      accept the language as described in specification, and as augmented 
 *      in the pp2 handout.
 */

%{

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

%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */
 
/* yylval 
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser. 
 *
 * pp2: You will need to add new fields to this union as you add different 
 *      attributes to your non-terminal symbols.
 */
%union {
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
}


/* Tokens
 * ------
 * Here we tell yacc about all the token types that we are using.
 * Yacc will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */
%token   T_Void T_Bool T_Int T_Double T_String T_Class 
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine

%token   <identifier> T_Identifier
%token   <stringConstant> T_StringConstant 
%token   <integerConstant> T_IntConstant
%token   <doubleConstant> T_DoubleConstant
%token   <boolConstant> T_BoolConstant

//%token   T_Increm T_Decrem T_Switch T_Case T_Default


/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "declList" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList ore reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 * pp2: You'll need to add many of these of your own.
 */
%type <declList>  DeclList 
%type <decl>      Decl
%type <vd>   VarDecl
%type <cd>  ClassDecl
%type <lcc> ListClassCode

%type <cc>  ClassCode
%type <id>   InterfaceDecl
%type <fd>   FnDecl
%type <t>    Type
%type <nt> NamedType
%type <ntl> NamedTypeList
%type <at> ArrayType
%type <sb> StmtBlock
%type <s> Stmt
%type <ifs> IfStmt 
%type <ws> WhileStmt
%type <fs> ForStmt
%type <bs> BreakStmt
%type <rs> ReturnStmt
%type <ps> PrintStmt
%type <e> Expr
%type <c> Call
%type <lv> LValue

%type <vl> VariableList
%type <ls> ListStmts
%type <el> ExprList
%type <vdl> ListVarDecl
%type <con> Constant
%type <fc> FunctionCode
%type <ee> EmptyExpr
//%type <cs> CaseStmt
//%type <lcs> CaseList
//%type <ss> SwitchStmt
//%type <de> Default

%type <act> Actuals
%type <pl> PrototypeList
%type <pro> Prototype

//precedence and associativity stuff
%nonassoc   '='
%left       T_Or
%left       T_And
%nonassoc   T_Equal T_NotEqual
%nonassoc   '<' '>' T_LessEqual T_GreaterEqual
%left       '+' '-'
%left       '*' '/' '%'
%nonassoc   '!' ArithmeticMinus
%nonassoc   '[' '.'

%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.
	 
 */
Program   :    DeclList            { 
                                      @1; 
                                      /* pp2: The @1 is needed to convince 
                                       * yacc to set up yylloc. You can remove 
                                       * it once you have other uses of @n*/
                                      Program *program = new Program($1);
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0) 
                                          program->Check();
                                    }
          ;

DeclList  :    DeclList Decl        { ($$=$1)->Append($2); }
          |    Decl                 { ($$ = new List<Decl*>)->Append($1); }
          ;

Decl      :    VarDecl
          |    ClassDecl
          |    InterfaceDecl
          |    FnDecl
          ;

VarDecl     : Type T_Identifier ';' { $$ = new VarDecl(new Identifier(@2, $2), $1); }
            ;


ClassDecl   : T_Class T_Identifier '{' ListClassCode '}' { $$ = new ClassDecl(new Identifier(@2, $2), NULL, new List<NamedType*>, $4);}
            | T_Class T_Identifier T_Extends NamedType '{' ListClassCode '}' { $$ = new ClassDecl(new Identifier(@2, $2), $4, new List<NamedType*>, $6);}
            | T_Class T_Identifier T_Implements NamedTypeList '{' ListClassCode '}' { $$ = new ClassDecl(new Identifier(@2, $2), NULL, $4, $6);}
            | T_Class T_Identifier T_Extends NamedType T_Implements NamedTypeList '{' ListClassCode '}' { $$ = new ClassDecl(new Identifier(@2, $2), $4, $6, $8);}
            ;

ListClassCode   : ListClassCode ClassCode      { ($$=$1)->Append($2); }
                | ClassCode                { ($$ = new List<Decl*>)->Append($1); }
                | /* epsilon */             { $$ = new List<Decl*>;}
                ;

ClassCode       : VarDecl 
                | FnDecl
                ;



NamedTypeList       : NamedTypeList ',' NamedType   { ($$=$1)->Append($3); }
                    | NamedType                     { ($$ = new List<NamedType*>)->Append($1); }
                    ;

InterfaceDecl   : T_Interface T_Identifier '{' PrototypeList '}' { $$= new InterfaceDecl(new Identifier(@2, $2), $4); }
                ;

PrototypeList   :   PrototypeList Prototype { ($$=$1)->Append($2); }
                |   /* epsilon */           { ($$=new List<Decl*>);}
                ;

VariableList    :   VariableList ',' Type T_Identifier { ($$=$1)->Append(new VarDecl(new Identifier(@4, $4), $3)); }
                |   Type T_Identifier   { ($$ = new List<VarDecl*>)->Append(new VarDecl(new Identifier(@2, $2), $1)); }
                |   /* epsilon */       { $$ = new List<VarDecl*>; }
                ;

Prototype       :   Type T_Identifier '(' VariableList ')' ';'      { $$ = new FnDecl(new Identifier(@2, $2), $1, $4);}
                |   T_Void T_Identifier '(' VariableList ')' ';'    { $$ = new FnDecl(new Identifier(@2, $2), Type::voidType, $4);}
                ;

FnDecl          : Type T_Identifier '(' VariableList ')' FunctionCode   { FnDecl* fnd = new FnDecl(new Identifier(@2, $2), $1, $4);
                                                                            fnd->SetFunctionBody($6);
                                                                            $$ = fnd;}
                | T_Void T_Identifier '(' VariableList ')' FunctionCode   { FnDecl* fnd = new FnDecl(new Identifier(@2, $2), Type::voidType, $4);
                                                                            fnd->SetFunctionBody($6);
                                                                            $$ = fnd;}
                ;

FunctionCode    :   '{' StmtBlock '}' { $$=$2; }
                ;

ListVarDecl     :   ListVarDecl VarDecl {($$ = $1)->Append($2);}
                |   VarDecl             {($$ = new List<VarDecl*>)->Append($1);}
                ;

ListStmts       :   ListStmts Stmt { ($$ = $1)->Append($2);}
                |   Stmt           { ($$ = new List<Stmt*>)->Append($1);}
                ;

StmtBlock       :   ListVarDecl ListStmts { ($$ = new StmtBlock($1, $2)); }
                |   ListVarDecl { ($$ = new StmtBlock($1, new List<Stmt*>)); }
                |   ListStmts   {($$ = new StmtBlock(new List<VarDecl*>, $1)); }
                |   /* epsilon */ {($$ = new StmtBlock(new List<VarDecl*>, new List<Stmt*>));}
                ;

Stmt            :   IfStmt
                |   WhileStmt
                |   ForStmt
                |   BreakStmt
                |   ReturnStmt
                |   PrintStmt
                |   FunctionCode
//                |   SwitchStmt
                |   Expr ';'
                |   ';'
                ;

IfStmt          : T_If '(' Expr ')' Stmt                { $$ = new IfStmt($3, $5, NULL);}
                | T_If '(' Expr ')' Stmt T_Else Stmt    { $$ = new IfStmt($3, $5, $7);}
                ;

WhileStmt       : T_While '(' Expr ')' Stmt     { $$ = new WhileStmt($3, $5);}
                ;

ForStmt         : T_For '(' Expr ';' Expr ';' Expr ')' Stmt             { $$ = new ForStmt($3, $5, $7, $9);}
                | T_For '(' EmptyExpr ';' Expr ';' Expr ')' Stmt        { $$ = new ForStmt($3, $5, $7, $9);}
                | T_For '(' Expr ';' Expr ';' EmptyExpr ')' Stmt        { $$ = new ForStmt($3, $5, $7, $9);}
                | T_For '(' EmptyExpr ';' Expr ';' EmptyExpr ')' Stmt   { $$ = new ForStmt($3, $5, $7, $9);}
                ;

BreakStmt       : T_Break ';' { $$ = new BreakStmt(@1);}
                ;

ReturnStmt      : T_Return Expr ';' { $$ = new ReturnStmt(@2, $2); }
                | T_Return EmptyExpr ';'  { $$ = new ReturnStmt(@1, $2); }
                ;
    
PrintStmt       : T_Print '(' ExprList ')' ';' { $$ = new PrintStmt($3); }
                ;

//SwitchStmt      : T_Switch '(' Expr ')' '{' CaseList Default '}' { $$ = new SwitchStmt($3, $6, $7);}
//                | T_Switch '(' Expr ')' '{' CaseList '}' { $$ = new SwitchStmt($3, $6, NULL);}
//                ;
//
//CaseList        : CaseList CaseStmt     { ($$ = $1)->Append($2);}
//                | CaseStmt              { ($$ = new List<CaseStmt*>)->Append($1);}
//                ;
//
//CaseStmt        : T_Case T_IntConstant ':' StmtBlock { $$ = new CaseStmt(new IntConstant(@2, $2), $4);}
//                ;
//
//Default         : T_Default ':' StmtBlock { $$ = new DefaultCaseStmt($3); }
//                ;

EmptyExpr       : /* epsion */ {$$ = new EmptyExpr();}
                ;

ExprList        : ExprList ',' Expr { ($$ = $1)->Append($3); }
                | Expr              { ($$ = new List<Expr*>)->Append($1); }
                ;

Expr            :   LValue '=' Expr { $$ = new AssignExpr($1, new Operator(@2, "="), $3);}
                |   Constant        
                |   LValue
                |   T_This          { $$ = new This(@1);}
                |   Call            
                |   '(' Expr ')'    { $$ = $2;}
                |   Expr '+' Expr                       {$$ = new ArithmeticExpr($1, new Operator(@2, "+"), $3);}
                |   Expr '-' Expr                       {$$ = new ArithmeticExpr($1, new Operator(@2, "-"), $3);} 
                |   Expr '*' Expr                       {$$ = new ArithmeticExpr($1, new Operator(@2, "*"), $3);}
                |   Expr '/' Expr                       {$$ = new ArithmeticExpr($1, new Operator(@2, "/"), $3);}
                |   Expr '%' Expr                       {$$ = new ArithmeticExpr($1, new Operator(@2, "%"), $3);}
                |   '-' Expr %prec ArithmeticMinus      {$$ = new ArithmeticExpr(new Operator(@2, "-"), $2);}
                |   Expr '<' Expr               {$$ = new RelationalExpr($1, new Operator(@2, "<"), $3);}
                |   Expr T_LessEqual Expr       {$$ = new RelationalExpr($1, new Operator(@2, "<="), $3);}
                |   Expr '>' Expr               {$$ = new RelationalExpr($1, new Operator(@2, ">"), $3);}
                |   Expr T_GreaterEqual Expr    {$$ = new RelationalExpr($1, new Operator(@2, ">="), $3);}
                |   Expr T_Equal Expr           {$$ = new EqualityExpr($1, new Operator(@2, "=="), $3);}
                |   Expr T_NotEqual Expr        {$$ = new EqualityExpr($1, new Operator(@2, "!="), $3);}
                |   Expr T_And Expr         {$$ = new LogicalExpr($1, new Operator(@2, "&&"), $3);}
                |   Expr T_Or Expr          {$$ = new LogicalExpr($1, new Operator(@2, "||"), $3);}
                |   '!' Expr                {$$ = new LogicalExpr(new Operator(@1, "!"), $2);}
                |   T_ReadInteger '(' ')'   {$$ = new ReadIntegerExpr(Join(@1, @3));}
                |   T_ReadLine '(' ')'      {$$ = new ReadLineExpr(Join(@1, @3));}
                |   T_New '(' T_Identifier ')'          { $$ = new NewExpr(Join(@1, @2), new NamedType(new Identifier(@3, $3)));}
                |   T_NewArray '(' Expr ',' Type ')'    { $$ = new NewArrayExpr(Join(@1, @6), $3, $5);}
//                |   LValue T_Increm           { $$ = new PostfixExpr(new Operator(@2, "++"), $1, Join(@1, @2));}
//                |   LValue T_Decrem           { $$ = new PostfixExpr(new Operator(@2, "--"), $1, Join(@1, @2));}
                ;

Call            : T_Identifier '(' Actuals ')' { $$ = new Call(Join(@1, @4), NULL, new Identifier(@1, $1), $3);}
                | Expr '.' T_Identifier '(' Actuals ')' { $$ = new Call(Join(@1, @6), $1, new Identifier(@3, $3), $5);}
                ;

Actuals         : Actuals ',' Expr  {($$ = $1)->Append($3);}
                | Expr              { ($$ = new List<Expr*>)->Append($1); }
                | /* epsilon */     { ($$ = new List<Expr*>);}
                ;

LValue          : T_Identifier {$$=new FieldAccess(NULL, new Identifier(@1, $1));}
                | Expr '.' T_Identifier {$$=new FieldAccess($1, new Identifier(@3, $3));}
                | Expr '[' Expr ']' { $$= new ArrayAccess(Join(@1, @4), $1, $3);}
                ;

//ArrayIndexList  : '[' Expr ']' ArrayIndexList
//                | '[' Expr ']'
//                ;

Constant        :   T_IntConstant       { $$ = new IntConstant(@1, $1); }
                |   T_DoubleConstant    { $$ = new DoubleConstant(@1, $1); }
                |   T_BoolConstant      { $$ = new BoolConstant(@1, $1); }
                |   T_StringConstant    { $$ = new StringConstant(@1, $1); }
                |   T_Null              { $$ = new NullConstant(@1); }
                ;

Type        : NamedType         
            | ArrayType
            | T_Int             { $$ = Type::intType;}
            | T_String          { $$ = Type::stringType;}
            | T_Bool            {$$ = Type::boolType;}
            | T_Double          {$$ = Type::doubleType;}
            ;

NamedType   : T_Identifier      { $$ = new NamedType(new Identifier(@1, $1)); }
            ;

ArrayType   : Type T_Dims   { $$ = new ArrayType(@1, $1); }
            ;

%%

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