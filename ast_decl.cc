/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "errors.h"
        
         
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
}

// TODO
bool Decl::Check(bool reportError){
    printf("Decl check\n");
    return true;
}


VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}

bool VarDecl::Check(bool reportError){
    printf("VarDecl check\n");
    if(type->Check(true)){
        return true;
    }
    else {
        type = Type::errorType;
        return false;
    }
}

Decl *VarDecl::CheckHash(Identifier *i) {
    printf("VarDecl CheckHash\n");
    return this->GetParent()->CheckHash(i);
}

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
    hash = new Hashtable<Decl*>();
    type = new NamedType(n);
}

bool ClassDecl::Check(bool reportError) {
    
    for(int i = 0; i < members->NumElements(); ++i){
        // TODO Check if overriding function

        // if member already there, return error
        Decl* d = hash->Lookup(members->Nth(i)->getIdentifier()->getName());
        
        if (d == NULL) {
            // add to new hashmap
            hash->Enter(members->Nth(i)->getIdentifier()->getName(), members->Nth(i));
        }
        else {
            // ERROR
            ReportError::DeclConflict(members->Nth(i), d);
        }

    }

    for(int i = 0; i < members->NumElements(); ++i){
        members->Nth(i)->Check(true);
    }
    return true;
}

Decl * ClassDecl::CheckHash(Identifier *id){
    printf("CLASS DECL CHECK HASH\n");
    for(int i = 0; i < members->NumElements(); ++i){
        if(strcmp(members->Nth(i)->getIdentifier()->getName(), id->getName()) == 0){
            printf("FOUND MEMBER\n");
            return members->Nth(i);
        }
    }

    printf("CANNoT FIND\n");

    //HERE CHECK EXTENDS
    if(extends != NULL){
        printf("EXTENDS CHECK\n");
        Node *parent = this->GetParent();
        if(dynamic_cast<Program*>(parent) == nullptr){
            //error. somehow class is in some function or something instead of directly in program? Don't think this is even possible. Probably syntax error.
            printf("Error: ClassDecl parent is not program\n");
        }

        yyltype y;
        Identifier *i = new Identifier(y, strdup(extends->typeName));
        Decl* d = parent->CheckHash(i);
        //d->Check(false);
        if(d->type->IsEquivalentTo(Type::errorType) || dynamic_cast<ClassDecl*>(d) == nullptr){
            printf("Extends check did not find class\n");
            
            /*Decl *temp = new Decl(id);
            temp->type = Type::errorType;
            return temp;*/
        }
        else{
            printf("Extends check found class\n");
            ClassDecl *cd = dynamic_cast<ClassDecl*>(d);
            Decl *h = cd->CheckHash(id);
            if(! h->type->IsEquivalentTo(Type::errorType)){
                printf("Extends check found. Return\n");
                return h;
            }
            
        }

    }

    //THEN HERE CHECK IMPLEMENTS
    

    // Return error did not find
    // Decl *temp = new Decl(id);
    // temp->type = Type::errorType;
    // return temp;
    return NULL;
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

	
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
    hash = new Hashtable<Decl*>();
}

void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}

bool FnDecl::Check(bool reportError) {
    // loop through formals
    
    for(int i = 0; i < formals->NumElements(); ++i){
        // TODO Check if overriding function
        
        // if formal already there, return error
        Decl* d = hash->Lookup(formals->Nth(i)->getIdentifier()->getName());
        
        if (d == NULL) {
            // add to new hashmap
            hash->Enter(formals->Nth(i)->getIdentifier()->getName(), formals->Nth(i));
        }
        else {
            // ERROR
            ReportError::DeclConflict(formals->Nth(i), d);
        }

    }
    
    body->Check(true); // then go through body and ensure type correctness and such 
    return true;
}

Decl *FnDecl::CheckHash(Identifier *i) {
    printf("FnDecl CheckHash\n");
    for(int in = 0; in < formals->NumElements(); ++in){
        if(strcmp(formals->Nth(in)->getIdentifier()->getName(), (i)->getName() ) == 0) {
            
            return formals->Nth(in);
        }
    }
    
    return this->GetParent()->CheckHash(i);
}

