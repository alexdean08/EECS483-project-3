/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
#include "ast_stmt.h"
 
/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type *Type::intType    = new Type("int");
Type *Type::doubleType = new Type("double");
Type *Type::voidType   = new Type("void");
Type *Type::boolType   = new Type("bool");
Type *Type::nullType   = new Type("null");
Type *Type::stringType = new Type("string");
Type *Type::errorType  = new Type("error");

Type::Type(const char *n) {
    Assert(n);
    typeName = strdup(n);
}



	
NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) {
    Assert(i != NULL);
    (id=i)->SetParent(this);
    typeName = strdup(i->name);
} 

bool NamedType::Check(bool reportError) {
    printf("NAMED CHECK\n");
    Type * CheckedHash = this->GetParent()->CheckHash(id)->type;
    //printf("\n\n%c\n\n\n\n", *(CheckedHash->typeName));
    if(CheckedHash == Type::nullType || CheckedHash == Type::intType || CheckedHash == Type::stringType || CheckedHash == Type::boolType
         || CheckedHash == Type::boolType || CheckedHash == Type::doubleType || CheckedHash == Type::errorType) {

        ReportError::IdentifierNotDeclared(id, LookingForType);
        
        return false;
    }
    return true;
}

bool NamedType::isType(NamedType* expected) {
    if(this->IsEquivalentTo(expected))
        return true;
    
    Node* parent = this->GetParent();
    while(dynamic_cast<Program*>(parent) == nullptr){
        parent = parent->GetParent();
    }
    Program* p = dynamic_cast<Program*>(parent);
    Decl* d = p->CheckHash(this->id);
    if(dynamic_cast<ClassDecl*>(d) == nullptr){
        //error not a class
        return false;
    }

    ClassDecl *class_decl = dynamic_cast<ClassDecl*>(d);
    for(int i = 0; i < class_decl->getImplements()->NumElements(); i++){
        if (class_decl->getImplements()->Nth(i)->isType(expected)) {
            return true;
        }
    }

    if (class_decl->getExtends() == NULL) {
        return false;
    }

    return class_decl->getExtends()->isType(expected);


    /*ClassDecl *class_decl = dynamic_cast<ClassDecl*>(d);
    while(class_decl->getExtends() != NULL){
        if(class_decl->getExtends()->IsEquivalentTo(expected)){
            return true;
        }
        else{
            
        }
    }*/

}


ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
    Assert(et != NULL);
    (elemType=et)->SetParent(this);

    typeName = strdup(et->typeName);
    strcat(typeName, "[]");
}


