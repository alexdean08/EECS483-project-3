/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
#include "errors.h"


/*void Expr::Check(){
    printf("5\n");
    return
}*/

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    type = Type::intType;
    value = val;
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    type = Type::doubleType;
    value = val;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    type = Type::boolType;
    value = val;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    type = Type::stringType;
    value = strdup(val);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}
CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}
   
  
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}

bool ArrayAccess::Check(){
    base->Check();
    
    if(dynamic_cast<ArrayType*>(base->type) == nullptr){
        ReportError::BracketsOnNonArray(base);
        type = Type::errorType;
    }
    else{
        type = dynamic_cast<ArrayType*>(base->type)->elemType;
    }

    subscript->Check();
    if(!subscript->type->IsEquivalentTo(Type::intType) && !subscript->type->IsEquivalentTo(Type::boolType))
        ReportError::SubscriptNotInteger(subscript);
    return true;
    //if(base->type != Type::a)
}
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}


Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}
 

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}


NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

bool NewArrayExpr::Check() {
    //printf("sdfds\n");
    size->Check();
    if(!size->type->IsEquivalentTo(Type::intType) && !size->type->IsEquivalentTo(Type::errorType)) {
        ReportError::NewArraySizeNotInteger(size);
    }
    elemType->Check();
    type=new ArrayType(*location, elemType);
    return true;
}

bool bothType(Expr* left, Expr* right, Type* type) {
    return left->type->IsEquivalentTo(type) && right->type->IsEquivalentTo(type);
}

bool ArithmeticExpr::Check(){

    left->Check();
    right->Check();
    
    if(left->type->IsEquivalentTo(Type::errorType) || right->type->IsEquivalentTo(Type::errorType)) {
        type = Type::errorType;
    }
    else if(!bothType(left, right, Type::intType) && !bothType(left, right, Type::doubleType)) {
        ReportError::IncompatibleOperands(op, left->type, right->type);
        type = Type::errorType;
    }
    else{
        type = left->type;
    }
     
    return true;
}

bool RelationalExpr::Check() {
    
    left->Check();
    right->Check();

    if(left->type->IsEquivalentTo(Type::errorType) || right->type->IsEquivalentTo(Type::errorType)) {
        type = Type::errorType; //change to boolType???
    }
    else if(!bothType(left, right, Type::intType) && !bothType(left, right, Type::doubleType)) {
        ReportError::IncompatibleOperands(op, left->type, right->type);
        type = Type::boolType; //changed from errorType (correct????)
    }
    else{
        type = Type::boolType;
    }
    return true;
}

bool EqualityExpr::Check() {
    
    left->Check();
    right->Check();
    if(left->type->IsEquivalentTo(Type::errorType) || right->type->IsEquivalentTo(Type::errorType)) {
        type = Type::errorType;
    }
    else if(!left->type->IsEquivalentTo(right->type)) {
        ReportError::IncompatibleOperands(op, left->type, right->type);
        type = Type::boolType;
    }
    else{
        type = Type::boolType;
    }
    return true;
}


bool LogicalExpr::Check() {
    left->Check();
    right->Check();
    if(left->type->IsEquivalentTo(Type::errorType) || right->type->IsEquivalentTo(Type::errorType)) {
        type = Type::errorType;
    }
    else if(!bothType(left, right, Type::boolType)) {
        ReportError::IncompatibleOperands(op, left->type, right->type);
        type = Type::boolType;
    }
    else {
        type = Type::boolType;
    }
    return true;
}

bool AssignExpr::Check() {
    
    left->Check();
    
    right->Check();
    

    if(!left->type->IsEquivalentTo(right->type) && !right->type->IsEquivalentTo(Type::errorType) && !left->type->IsEquivalentTo(Type::errorType)) {
        ReportError::IncompatibleOperands(op, left->type, right->type);
    }

    type = left->type;
    return true;
}

bool FieldAccess::Check() {
    //printf(typeid(this->GetParent()).name());
    //printf("\n");
    Type *t = this->GetParent()->CheckHash(field);
    if(t == Type::nullType) {
        ReportError::IdentifierNotDeclared(field, LookingForVariable);
        //std::cout << "type not found\n";
    }
        
    
    type = t;
    
    return true;
    /*

    if(base==NULL){

    }
    else{
        
    }*/
}