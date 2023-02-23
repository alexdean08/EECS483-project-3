/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"


Program::Program(List<Decl*> *d) {
    //printf("a\n");
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);

    hash = new Hashtable<Decl*>();
}

bool Program::Check() {
    /* pp3: here is where the semantic analyzer is kicked off.
     *      The general idea is perform a tree traversal of the
     *      entire program, examining all constructs for compliance
     *      with the semantic rules.  Each node can have its own way of
     *      checking itself, which makes for a great use of inheritance
     *      and polymorphism in the node classes.
     */

    //printf("hello\n");
    for(int i = 0; i < decls->NumElements(); ++i){
        
        Decl* d = hash->Lookup(decls->Nth(i)->getIdentifier()->getName());
        if (d == NULL) {
            hash->Enter(decls->Nth(i)->getIdentifier()->getName(), decls->Nth(i));
        }
        else {
            // ERROR
            ReportError::DeclConflict(decls->Nth(i), d);
        }
        
    }
    
    for(int i = 0; i < decls->NumElements(); ++i){
        decls->Nth(i)->Check();
    }
    return true;
}

Decl * Program::CheckHash(Identifier *i){
    printf("PROGRAM CHECK HASH\n");
    for(int in = 0; in < decls->NumElements(); ++in){
        if(strcmp(decls->Nth(in)->getIdentifier()->getName(), (i)->getName() ) == 0) {
            //printf("%d\n", decls->Nth(in)->type->GetLocation()->first_line);
            printf("FIUND\n");
            return decls->Nth(in);
        }
    }
    //printf("NULL VAL \n");
    Decl *temp = new Decl(i);
    temp->type = Type::errorType;
    return temp;
}

bool Stmt::Check() {
    printf("stmt\n");
   return true;
   //printf("Stmt Check running\n");
}

Decl * Stmt::CheckHash(Identifier *i){
    //printf("running CheckHash in Stmt\n");
    return this->GetParent()->CheckHash(i);
}

bool StmtBlock::Check() {
    printf("stmt block check \n");
    //printf(this->GetParent()->);
    //printf("\n");

    // Check variable declarations
    for(int i = 0; i < decls->NumElements(); ++i){

        decls->Nth(i)->Check();
        
        // if member already there, return error
        Decl* d = hash->Lookup(decls->Nth(i)->getIdentifier()->getName());
        
        if (d == NULL) {
            // add to new hashmap
            //d->SetParent(this);
            hash->Enter(decls->Nth(i)->getIdentifier()->getName(), decls->Nth(i));
        }
        else {
            // ERROR
            ReportError::DeclConflict(decls->Nth(i), d);
        }
    }
   
    for(int i = 0; i < stmts->NumElements(); ++i) {
        Stmt* s = stmts->Nth(i);
        if(dynamic_cast<This*>(stmts->Nth(i)) != nullptr){
            printf("Running this check\n");
            dynamic_cast<This*>(s)->Check();
        }
        else{
            s->Check();
        }
        
        printf("done check\n");
    }
    return true;
}

Decl *StmtBlock::CheckHash(Identifier *i) {
    
    for(int in = 0; in < decls->NumElements(); ++in){

        if(strcmp(decls->Nth(in)->getIdentifier()->getName(), (i)->getName() ) == 0) {
            
            return decls->Nth(in);
        }
    }
    
    return this->GetParent()->CheckHash(i);

}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
    hash = new Hashtable<Decl*>();
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}


bool ConditionalStmt::Check() {
    printf("Conditional check\n");
    test->Check();
    //printf("%d\n", test->GetLocation()->first_line);
    
    if(!test->type->IsEquivalentTo(Type::boolType)){
        ReportError::TestNotBoolean(test);
    }
    

    body->Check();
    return true;
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

bool IfStmt::Check() {
    test->Check();
    //printf("%d\n", test->GetLocation()->first_line);
    if(!test->type->IsEquivalentTo(Type::boolType)){
        ReportError::TestNotBoolean(test);
    }

    
    
    body->Check();
    if(elseBody)
        elseBody->Check();
    return true;
}


Decl *IfStmt::CheckHash(Identifier *i) {
    return this->GetParent()->CheckHash(i);
}

/*bool LoopStmt::Check() {
    printf("LoopStmt check\n");
    return true;
}*/

bool WhileStmt::Check() {
    printf("While check\n");
    test->Check();
    //printf("%d\n", test->GetLocation()->first_line);
    
    if(!test->type->IsEquivalentTo(Type::boolType)){
        ReportError::TestNotBoolean(test);
    }
    

    body->Check();
    return true;
}


Decl *WhileStmt::CheckHash(Identifier *i) {
    
    return this->GetParent()->CheckHash(i);
}


ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}
  
PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

bool PrintStmt::Check(){
    for(int i = 0; i < args->NumElements(); ++i) {
        args->Nth(i)->Check();
    }
    return true;
}


