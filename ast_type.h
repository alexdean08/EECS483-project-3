/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.  
 *
 * pp3: You will need to extend the Type classes to implement
 * the type system and rules for type equivalency and compatibility.
 */
 
#ifndef _H_ast_type
#define _H_ast_type

#include "ast.h"
#include "list.h"
#include <iostream>
#include <sstream>


class Type : public Node 
{
  protected:
    

  public :
    char *typeName;
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type(const char *str);
    virtual bool Check(bool reportError) {
      //printf("Type Check\n"); 
      return true;
      }
    virtual Decl * CheckHash(Identifier *i) {
      //printf("Type CheckHash %s\n", typeName);
      //printf("%d\n", this->GetParent() == NULL);
      return this->GetParent()->CheckHash(i);
    }
    
    virtual void PrintToStream(std::ostream& out) { out << typeName; }
    friend std::ostream& operator<<(std::ostream& out, Type *t) { t->PrintToStream(out); return out; }
    virtual bool IsEquivalentTo(Type *other) {  std::ostringstream l;
                                                l << this;
                                                std::ostringstream r;
                                                r << other;
                                                return l.str() == r.str(); }
};

class NamedType : public Type 
{
  protected:
    Identifier *id;
    
  public:
    NamedType(Identifier *i);
    bool Check(bool reportError);
    bool CheckNew(bool reportError);
    void PrintToStream(std::ostream& out) { out << id; }
    bool isType(NamedType* expected);
    Identifier *getIdentifier(){return id;}
    Decl * CheckHash(Identifier *i) { 
      //printf("NAMEDTYPE CHECK HASH\n"); 
      return this->GetParent()->CheckHash(i);
      }

};

class ArrayType : public Type 
{
  protected:


  public:
    Type *elemType;
    ArrayType(yyltype loc, Type *elemType);
    bool Check(bool reportError);
    void PrintToStream(std::ostream& out) { out << elemType << "[]"; }
};

 
#endif
