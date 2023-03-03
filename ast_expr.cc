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


bool Expr::Check(bool reportError){
    printf("Expr check\n");
    if(dynamic_cast<NullConstant*>(this) != nullptr){
      type = Type::nullType;
    }
    return true;
}

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

bool ArrayAccess::Check(bool reportError){
    printf("array access check\n");
    base->Check(reportError);
    
    if(dynamic_cast<ArrayType*>(base->type) == nullptr){
        if(reportError)
            ReportError::BracketsOnNonArray(base);
        type = Type::errorType;
    }
    else{
        type = dynamic_cast<ArrayType*>(base->type)->elemType;
    }

    subscript->Check(reportError);
    if(!subscript->type->IsEquivalentTo(Type::intType) && !subscript->type->IsEquivalentTo(Type::boolType)){
        if(reportError)
            ReportError::SubscriptNotInteger(subscript);
    }
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

bool FieldAccess::Check(bool reportError) {
    //printf(typeid(this->GetParent()).name());
    
    if(base==NULL){
        printf("field access \n");
        Type *t;
        Decl* d = this->GetParent()->CheckHash(field);
        if(dynamic_cast<FnDecl*>(d) != nullptr){
            
            if(reportError)
                ReportError::IdentifierNotDeclared(field, LookingForVariable);
            t = Type::errorType;
        }
        else{
            if(d == NULL) {
                ReportError::IdentifierNotDeclared(field, LookingForVariable);
                type = Type::errorType;
                return false;
            }
            
            t = d->type;

            // if(t == Type::errorType) {
            //     if(reportError) {
            //         ReportError::IdentifierNotDeclared(field, LookingForVariable);
            //     }
                    

            //     //std::cout << "type not found\n";
            // }
        }
            
        
        type = t;
        
        return true;
    }
    else{
        base->Check(reportError);
        
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
                    if(reportError)
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
                    if(reportError)
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
                if(reportError)
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

bool Call::Check(bool reportError) {

    //TODO: test a function call that can't be accessed AND has incorrect formals. Is this really possible?
    if(base==NULL){
        Decl *d = this->GetParent()->CheckHash(field);
        if(dynamic_cast<FnDecl*>(d) != nullptr){
            FnDecl *fn = dynamic_cast<FnDecl*>(d);
            validateFormals(field, fn->GetFormals(), actuals, reportError);
            type = fn->GetReturnType();
            return true;
            
        }
        if(reportError)
            ReportError::IdentifierNotDeclared(field, LookingForFunction);
        checkActuals(reportError);
        return false;
    }
    else{
        base->Check(reportError);
        
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
                    if(reportError)
                        ReportError::FieldNotFoundInBase(field, base->type);
                    type=Type::errorType;
                    return false;
                }
                printf("Found Class\n");
                
                ClassDecl* cl = dynamic_cast<ClassDecl*>(temp_cl);

                Decl *temp_fn_decl = cl->CheckHash(field);
                if(dynamic_cast<FnDecl*>(temp_fn_decl) == nullptr){
                    //ERROR found class but did not find function
                    if(reportError)
                        ReportError::FieldNotFoundInBase(field, base->type);
                    type=Type::errorType;
                    checkActuals(reportError);
                    return false;
                }
                
                //Found function

                FnDecl *fn_decl = dynamic_cast<FnDecl*>(temp_fn_decl);
                validateFormals(field, fn_decl->GetFormals(), actuals, reportError);
                type = fn_decl->GetReturnType();
                return true;
    
                
            }
            else{
                parent = parent->GetParent();
            }
        }
    }
    
}

void Call::validateFormals(Identifier *FnIdentifier, List<VarDecl*> *decl_formals, List<Expr*> *call_actuals, bool reportError){
    if(decl_formals->NumElements() != call_actuals->NumElements()){
        if(reportError)
            ReportError::NumArgsMismatch(FnIdentifier, decl_formals->NumElements(), call_actuals->NumElements());
    }

    checkActuals(reportError);

    int min_elements = decl_formals->NumElements();
    if(call_actuals->NumElements() < min_elements)
        min_elements = call_actuals->NumElements();

    for(int i = 0; i < min_elements; ++i){
        call_actuals->Nth(i)->type->IsEquivalentTo(Type::errorType);
        
        if( !( decl_formals->Nth(i)->type->IsEquivalentTo(call_actuals->Nth(i)->type) || decl_formals->Nth(i)->type->IsEquivalentTo(Type::errorType) || call_actuals->Nth(i)->type->IsEquivalentTo(Type::errorType)) ){
            if(reportError)
                ReportError::ArgMismatch(call_actuals->Nth(i), i+1, call_actuals->Nth(i)->type, decl_formals->Nth(i)->type);
        }
    }
}

void Call::checkActuals(bool reportError){
    for(int i = 0; i < actuals->NumElements(); ++i){
        actuals->Nth(i)->Check(reportError);
    }
}
 

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

bool NewExpr::Check(bool reportError){
    printf("NewExpr check\n");
    bool valid = cType->Check(reportError);
    if(!valid){
        type = Type::errorType;
    }
    else{
        type = cType;
    }
    return true;
}


NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

bool NewArrayExpr::Check(bool reportError) {
    type=Type::errorType;
    printf("new array expression check\n");
    //printf("sdfds\n");
    size->Check(reportError);
    printf("new array size check done\n");
    if(!size->type->IsEquivalentTo(Type::intType) && !size->type->IsEquivalentTo(Type::errorType)) {
        if(reportError)
            ReportError::NewArraySizeNotInteger(size);
    }
    printf("new array size is correct type\n");
    bool valid = elemType->Check(reportError);
    if(!valid){
        type=Type::errorType;    
    }
    else{
        if(dynamic_cast<NamedType*>(elemType) != nullptr){
            NamedType* temp_type = new NamedType(dynamic_cast<NamedType*>(elemType)->getIdentifier());
            type=new ArrayType(*location, temp_type);
        }
        else{
            type=new ArrayType(*location, elemType);
        }
                
    }
    
    return true;
}

Decl * NewArrayExpr::CheckHash(Identifier *i){
    printf("NewArrayExpr CHECK HASH\n");

    return this->GetParent()->CheckHash(i);
}

bool bothType(Expr* left, Expr* right, Type* type) {
    return left->type->IsEquivalentTo(type) && right->type->IsEquivalentTo(type);
}

bool ArithmeticExpr::Check(bool reportError){
    printf("arithmetic expression check\n");

    left->Check(reportError);
    right->Check(false);
    
    if(left->type->IsEquivalentTo(Type::errorType) || right->type->IsEquivalentTo(Type::errorType)) {
        type = Type::errorType;
    }
    else if(!bothType(left, right, Type::intType) && !bothType(left, right, Type::doubleType)) {
        if(reportError)
            ReportError::IncompatibleOperands(op, left->type, right->type);
        type = Type::errorType;
    }
    else{
        type = left->type;
    }
    right->Check(reportError);
     
    return true;
}

bool RelationalExpr::Check(bool reportError) {
    printf("relational expression check\n");
    
    left->Check(reportError);
    right->Check(false);

    if(left->type->IsEquivalentTo(Type::errorType) || right->type->IsEquivalentTo(Type::errorType)) {
        type = Type::boolType; //change to boolType???
    }
    else if(!bothType(left, right, Type::intType) && !bothType(left, right, Type::doubleType)) {
        if(reportError)
            ReportError::IncompatibleOperands(op, left->type, right->type);
        type = Type::boolType; //changed from errorType (correct????)
    }
    else{
        type = Type::boolType;
    }
    right->Check(reportError);
    return true;
}

bool EqualityExpr::Check(bool reportError) {
    printf("equality expression check\n");
    
    left->Check(reportError);
    right->Check(false);
    if(left->type->IsEquivalentTo(Type::errorType) || right->type->IsEquivalentTo(Type::errorType)) {
        type = Type::boolType;
    }
    else if(!left->type->IsEquivalentTo(right->type)) {
        NamedType* leftNamed = dynamic_cast<NamedType*>(left->type);
        NamedType* rightNamed = dynamic_cast<NamedType*>(right->type);

        if ((leftNamed != nullptr && right->type->IsEquivalentTo(Type::nullType)) || (rightNamed != nullptr && left->type->IsEquivalentTo(Type::nullType))) {
            // Do nothing. No error
        }
        else if(leftNamed != nullptr && rightNamed != nullptr){
            
            if(! (leftNamed->isType(rightNamed) || rightNamed->isType(leftNamed)) ){
                if(reportError)
                    ReportError::IncompatibleOperands(op, left->type, right->type);
            }
        }
        else{
            if(reportError)
                ReportError::IncompatibleOperands(op, left->type, right->type);
        }
        type = Type::boolType;
    }
    else{
        type = Type::boolType;
    }
    right->Check(reportError);
    return true;
}


bool LogicalExpr::Check(bool reportError) {
    printf("logical expression check\n");
    if(left == NULL){
        right->Check(false);
        if(! (right->type->IsEquivalentTo(Type::boolType) || right->type->IsEquivalentTo(Type::errorType))){
            if(reportError)
                ReportError::IncompatibleOperand(op, right->type);
        }
        type = Type::boolType;
        right->Check(reportError);
        return true;
    }
    else{
        left->Check(reportError);
        right->Check(false);
        if(left->type->IsEquivalentTo(Type::errorType) || right->type->IsEquivalentTo(Type::errorType)) {
            type = Type::boolType;
        }
        else if(!bothType(left, right, Type::boolType)) {
            if(reportError)
                ReportError::IncompatibleOperands(op, left->type, right->type);
            type = Type::boolType;
        }
        else {
            type = Type::boolType;
        }
        right->Check(reportError);
        return true;
    }
}

bool AssignExpr::Check(bool reportError) {
    
    printf("assign expression check\n");

    left->Check(reportError);
    
    printf("right assign check report error false\n");
    right->Check(false);
    if(dynamic_cast<NullConstant*>(right) != nullptr) 
        dynamic_cast<NullConstant*>(right)->Check(false);
    printf("BEFORE\n");
    right->type->IsEquivalentTo(Type::nullType);
    printf("SDFDS\n");

    if(!left->type->IsEquivalentTo(right->type) && !right->type->IsEquivalentTo(Type::errorType) && !left->type->IsEquivalentTo(Type::errorType)) {
        
        NamedType* leftNamed = dynamic_cast<NamedType*>(left->type);
        NamedType* rightNamed = dynamic_cast<NamedType*>(right->type);
        

        if (leftNamed != nullptr && right->type->IsEquivalentTo(Type::nullType)) {
            // Do nothing. No error
        }
        else if(leftNamed != nullptr && rightNamed != nullptr){
            
            if(! rightNamed->isType(leftNamed) ){
                if(reportError)
                    ReportError::IncompatibleOperands(op, left->type, right->type);
            }
        }
        else{
        
            if(reportError)
                ReportError::IncompatibleOperands(op, left->type, right->type);
        }
    }

    printf("right assign check report error true\n");
    right->Check(reportError);

    type = left->type;
    return true;
}



bool This::Check(bool reportError){
    std::cerr << "This Check()\n" << std::endl;
    Node* parent = this->GetParent();
    while(true) {
        if (dynamic_cast<ClassDecl*>(parent) != nullptr) {
            type = dynamic_cast<ClassDecl*>(parent)->type;
            return true;

        }
        else if(dynamic_cast<Program*>(parent) != nullptr) {
            //error
            if(reportError)
                ReportError::ThisOutsideClassScope(this);
            type = Type::errorType;
            return false;
        }
        parent = parent->GetParent();
        
    }

    return true;

}