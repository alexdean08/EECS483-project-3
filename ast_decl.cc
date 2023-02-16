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
void Decl::Check(){
    printf("here\n");
    return;
}


VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}
  

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
    hash = new Hashtable<Decl*>();
}

void ClassDecl::Check() {
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

void FnDecl::Check() {
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
    
    body->Check(); // then go through body and ensure tyoe correctness and such 
}

// bool FnDecl::isPresent(char* name){
//     // see if name is in hashmap
//     // if name is in hashmap, return the thing here
//     // else look in parent
// }