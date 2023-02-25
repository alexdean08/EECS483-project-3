/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. 
 *
 * pp3: You will need to extend the Stmt classes to implement
 * semantic analysis for rules pertaining to statements.
 */


#ifndef _H_ast_stmt
#define _H_ast_stmt

#include "list.h"
#include "ast.h"
#include "hashtable.h"
#include "errors.h"

class Decl;
class VarDecl;
class Expr;
  
class Program : public Node
{
  protected:
     
     
  private:
     Hashtable<Decl*>* hash;
     
  public:
     List<Decl*> *decls;
     Program(List<Decl*> *declList);
     bool Check(bool reportError);
     bool containsIdent(const char* ident);
     Decl * CheckHash(Identifier *i);
};

class Stmt : public Node
{
  public:
     Stmt() : Node() {}
     Stmt(yyltype loc) : Node(loc) {}
     virtual bool Check(bool reportError);
     virtual Decl *CheckHash(Identifier *i);
};

class StmtBlock : public Stmt 
{
  protected:
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;
  
  private:
    Hashtable<Decl *> *hash;
    
  public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
    Decl *CheckHash(Identifier *i);
    
    virtual bool Check(bool reportError);
};

  
class ConditionalStmt : public Stmt
{
  protected:
    Expr *test;
    Stmt *body;
  
  public:
    ConditionalStmt(Expr *testExpr, Stmt *body);
    virtual bool Check(bool reportError);
    
};

class LoopStmt : public ConditionalStmt 
{
  private:
    bool loopstmt;
  public:
    LoopStmt(Expr *testExpr, Stmt *body)
            : ConditionalStmt(testExpr, body) {}
    //virtual bool Check(bool reportError);
};

class ForStmt : public LoopStmt 
{
  protected:
    Expr *init, *step;
  
  public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
    bool Check(bool reportError);
};

class WhileStmt : public LoopStmt 
{
  public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
    bool Check(bool reportError);
    Decl *CheckHash(Identifier *i);
};

class IfStmt : public ConditionalStmt 
{
  protected:
    Stmt *elseBody;
  
  public:
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
    bool Check(bool reportError);
    Decl *CheckHash(Identifier *i);
};

class BreakStmt : public Stmt 
{
  protected:
    double breaks;
  public:
    BreakStmt(yyltype loc);
    bool Check(bool reportError) override;
};

class ReturnStmt : public Stmt  
{
  protected:
    Expr *expr;
  
  public:
    ReturnStmt(yyltype loc, Expr *expr);
    bool Check(bool reportError);
};

class PrintStmt : public Stmt
{
  protected:
    List<Expr*> *args;
    
  public:
    PrintStmt(List<Expr*> *arguments);
    bool Check(bool reportError);
};


#endif
