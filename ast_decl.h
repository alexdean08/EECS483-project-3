/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp3: You will need to extend the Decl classes to implement 
 * semantic processing including detection of declaration conflicts 
 * and managing scoping issues.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
#include "ast_type.h"
#include "list.h"
#include "hashtable.h"
#include "errors.h"

class Identifier;
class Stmt;

class Decl : public Node 
{
  protected:
    Identifier *id;
  
  public:
    Type *type;
    Decl(Identifier *name);
    virtual bool Check();
    friend std::ostream& operator<<(std::ostream& out, Decl *d) { return out << d->id; }
    Identifier* getIdentifier() { return id; }
};

class VarDecl : public Decl 
{
  protected:
    
    
  public:
    //Type *type;
    VarDecl(Identifier *name, Type *type);
    bool Check();
    Type *CheckHash(Identifier *i);
};

class ClassDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;
  
  private:
    Hashtable<Decl*>* hash;

  public:
    ClassDecl(Identifier *name, NamedType *extends, 
              List<NamedType*> *implements, List<Decl*> *members);
    bool Check();
};

class InterfaceDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
};

class FnDecl : public Decl 
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
  
  private:
    Hashtable<Decl*> *hash;
    
  public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
    bool Check();
    Type *CheckHash(Identifier *i);
};

#endif
