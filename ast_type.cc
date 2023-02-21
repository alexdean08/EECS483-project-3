/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
 
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
} 

bool NamedType::Check() {
    printf("NAMED CHECK\n");
    Type * CheckedHash = this->GetParent()->CheckHash(id);
    //printf("\n\n%c\n\n\n\n", *(CheckedHash->typeName));
    if(CheckedHash == Type::nullType || CheckedHash == Type::intType || CheckedHash == Type::stringType || CheckedHash == Type::boolType
         || CheckedHash == Type::boolType || CheckedHash == Type::doubleType || CheckedHash == Type::errorType) {

        ReportError::IdentifierNotDeclared(id, LookingForType);
        
        return false;
    }
    return true;
}


ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
    Assert(et != NULL);
    (elemType=et)->SetParent(this);
}


