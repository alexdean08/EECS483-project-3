/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
#include "errors.h"
#include <iostream>
#include <sstream>


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
    printf("array access check\n");
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

bool FieldAccess::Check() {
    //printf(typeid(this->GetParent()).name());
    
    if(base==NULL){
        printf("field access \n");
        Type *t = this->GetParent()->CheckHash(field)->type;
        if(t == Type::errorType) {
            ReportError::IdentifierNotDeclared(field, LookingForVariable);
            
            //std::cout << "type not found\n";
        }
            
        
        type = t;
        
        return true;
    }
    else{
        base->Check();
        
        printf("class field access\n");
        bool found = false;
        Node* parent = this->GetParent();
        ClassDecl* class_in = nullptr;
        
        printf("IsEquivalentTo\n");
        if(base->type->IsEquivalentTo(Type::errorType)){
            return true;
        }

        printf("about to run while\n");

        while(true) {
            
            if(dynamic_cast<Program*>(parent) != nullptr) {
                
                //Identifier *i = new Identifier()
                if(dynamic_cast<FieldAccess*>(base) == nullptr){
                    //there's some error here. probably syntax error. like doing "(1+2).a"
                    type=Type::errorType;
                    return false;
                }
                yyltype y;
                if(base->type->typeName == nullptr){
                    printf("SdfDS\n");
                }
                Identifier *temp_id = new Identifier(y, strdup(base->type->typeName));                
                printf("%s\n", temp_id->name);
                
                Decl *temp_cl = dynamic_cast<Program*>(parent)->CheckHash(temp_id);
                if(dynamic_cast<ClassDecl*>(temp_cl) == nullptr){
                    // ERROR did not find class
                    ReportError::FieldNotFoundInBase(field, base->type);
                    type=Type::errorType;
                    return false;
                }
                printf("ERSIDFS\n");
                
                ClassDecl* cl = dynamic_cast<ClassDecl*>(temp_cl);

                Decl *temp_var_decl = cl->CheckHash(field);
                //printf("DONE CLASS CHECKHASH\n");
                if(dynamic_cast<VarDecl*>(temp_var_decl) == nullptr){
                    //ERROR found class but did not find variable
                    ReportError::FieldNotFoundInBase(field, base->type);
                    type=Type::errorType;
                    return false;
                }
                
                VarDecl *var_decl = dynamic_cast<VarDecl*>(temp_var_decl);
                //printf("%s\n", class_in->getIdentifier()->getName());
                if(class_in != nullptr && strcmp(class_in->getIdentifier()->getName(), cl->getIdentifier()->getName()) == 0) {
                    //valid. no error
                    type=var_decl->type;
                    return true;
                }
                
                //ERROR found variable but cannot access it
                ReportError::InaccessibleField(field, base->type);
                type=Type::errorType;
                return false;
            }
            else if(dynamic_cast<ClassDecl*>(parent) != nullptr){
                class_in = dynamic_cast<ClassDecl*>(parent);
                parent = parent->GetParent();
                printf("sdfDS\n");
            }
            else{
                parent = parent->GetParent();
            }
        }
    }
}


Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

bool Call::Check() {

    //TODO: test a function call that can't be accessed AND has incorrect formals. Is this really possible?
    if(base==NULL){
        Decl *d = this->GetParent()->CheckHash(field);
        if(dynamic_cast<FnDecl*>(d) != nullptr){
            FnDecl *fn = dynamic_cast<FnDecl*>(d);
            validateFormals(field, fn->GetFormals(), actuals);
            type = fn->type;
            return true;
            
        }
        ReportError::IdentifierNotDeclared(field, LookingForFunction);
        checkActuals();
        return false;
    }
    else{
        base->Check();
        
        printf("class field access\n");
        bool found = false;
        Node* parent = this->GetParent();
        
        printf("IsEquivalentTo\n");
        if(base->type->IsEquivalentTo(Type::errorType)){
            return true;
        }

        printf("about to run while\n");

        while(true) {
            
            if(dynamic_cast<Program*>(parent) != nullptr) {
                
                
                if(dynamic_cast<FieldAccess*>(base) == nullptr){
                    //there's some error here. probably syntax error. like doing "(1+2).a()"
                    type=Type::errorType;
                    return false;
                }

                yyltype y;
                Identifier *temp_id = new Identifier(y, strdup(base->type->typeName));                
                Decl *temp_cl = dynamic_cast<Program*>(parent)->CheckHash(temp_id);

                if(dynamic_cast<ClassDecl*>(temp_cl) == nullptr){
                    // ERROR did not find class
                    ReportError::FieldNotFoundInBase(field, base->type);
                    type=Type::errorType;
                    return false;
                }
                printf("Found Class\n");
                
                ClassDecl* cl = dynamic_cast<ClassDecl*>(temp_cl);

                Decl *temp_fn_decl = cl->CheckHash(field);
                if(dynamic_cast<FnDecl*>(temp_fn_decl) == nullptr){
                    //ERROR found class but did not find function
                    ReportError::FieldNotFoundInBase(field, base->type);
                    type=Type::errorType;
                    checkActuals();
                    return false;
                }
                
                //Found function

                FnDecl *fn_decl = dynamic_cast<FnDecl*>(temp_fn_decl);
                validateFormals(field, fn_decl->GetFormals(), actuals);
                type = fn_decl->type;
                return true;
    
                
            }
            else{
                parent = parent->GetParent();
            }
        }
    }
    
}

void Call::validateFormals(Identifier *FnIdentifier, List<VarDecl*> *decl_formals, List<Expr*> *call_actuals){
    if(decl_formals->NumElements() != call_actuals->NumElements()){
        ReportError::NumArgsMismatch(FnIdentifier, decl_formals->NumElements(), call_actuals->NumElements());
    }

    checkActuals();

    int min_elements = decl_formals->NumElements();
    if(call_actuals->NumElements() < min_elements)
        min_elements = call_actuals->NumElements();

    for(int i = 0; i < min_elements; ++i){
        call_actuals->Nth(i)->type->IsEquivalentTo(Type::errorType);
        
        if( !( decl_formals->Nth(i)->type->IsEquivalentTo(call_actuals->Nth(i)->type) || decl_formals->Nth(i)->type->IsEquivalentTo(Type::errorType) || call_actuals->Nth(i)->type->IsEquivalentTo(Type::errorType)) ){
            ReportError::ArgMismatch(call_actuals->Nth(i), i+1, call_actuals->Nth(i)->type, decl_formals->Nth(i)->type);
        }
    }
}

void Call::checkActuals(){
    for(int i = 0; i < actuals->NumElements(); ++i){
        actuals->Nth(i)->Check();
    }
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
    printf("new array expression check\n");
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
    printf("arithmetic expression check\n");

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
    printf("relational expression check\n");
    
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
    printf("equality expression check\n");
    
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
    printf("logical expression check\n");
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
    
    printf("assign expression check\n");

    left->Check();
    
    right->Check();
    

    if(!left->type->IsEquivalentTo(right->type) && !right->type->IsEquivalentTo(Type::errorType) && !left->type->IsEquivalentTo(Type::errorType)) {
        
        ReportError::IncompatibleOperands(op, left->type, right->type);
    }

    

    type = left->type;
    return true;
}



bool This::Check(){
    std::cerr << "This Check()\n" << std::endl;
    Node* parent = this->GetParent();
    while(true) {
        if (dynamic_cast<ClassDecl*>(parent) != nullptr) {
            type = dynamic_cast<ClassDecl*>(parent)->type;
            return true;

        }
        else if(dynamic_cast<Program*>(parent) != nullptr) {
            //error
            ReportError::ThisOutsideClassScope(this);
            type = Type::errorType;
            return false;
        }
        parent = parent->GetParent();
        
    }

    return true;

}