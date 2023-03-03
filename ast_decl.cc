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
    if(type->Check(reportError)){
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
    interfaces_not_implemented = new List<NamedType*>();
    functions_added_per_implement = new Hashtable<List<Identifier*>*>();
}

bool ClassDecl::Check(bool reportError) {
    
    

    for(int i = 0; i < members->NumElements(); ++i){
        members->Nth(i)->Check(false);
    }

    printf("BACK IN CLASS\n");

    if(implements->NumElements() > 0){
        for(int impl = 0; impl < implements->NumElements(); ++impl){
            bool error_reported = false;
            for(int i = 0; i < interfaces_not_implemented->NumElements(); ++i){
                if(interfaces_not_implemented->Nth(i)->isType(implements->Nth(impl))){
                    if(reportError)
                        ReportError::InterfaceNotImplemented(this, implements->Nth(impl));
                    error_reported = true;
                    break;
                }
            }
            if(!error_reported){
                int num_interface_elements = dynamic_cast<InterfaceDecl*>(this->GetParent()->CheckHash(implements->Nth(impl)->getIdentifier()))->GetMembers()->NumElements();
                if(this->functions_added_per_implement->Lookup(implements->Nth(impl)->getIdentifier()->getName()) == NULL 
                    || this->functions_added_per_implement->Lookup(implements->Nth(impl)->getIdentifier()->getName())->NumElements() != num_interface_elements){
                        if(reportError)
                            ReportError::InterfaceNotImplemented(this, implements->Nth(impl));
                    }
            }
        }
    }

    for(int i = 0; i < members->NumElements(); ++i){

        // if member already there, return error
        Decl* d = hash->Lookup(members->Nth(i)->getIdentifier()->getName());
        
        if (d == NULL) {
            // add to new hashmap
            hash->Enter(members->Nth(i)->getIdentifier()->getName(), members->Nth(i));
        }
        else {
            // ERROR
            if(reportError)
                ReportError::DeclConflict(members->Nth(i), d);
        }

        members->Nth(i)->Check(reportError);

    }

    return true;
}

Decl * ClassDecl::CheckHash(Identifier *id){
    printf("CLASS DECL CHECK HASH\n");
    
    Decl* members_i = NULL;
    for(int i = 0; i < members->NumElements(); ++i){
        if(strcmp(members->Nth(i)->getIdentifier()->getName(), id->getName()) == 0){
            printf("FOUND MEMBER IN %s\n", this->getIdentifier()->getName());
            members_i = members->Nth(i); 
        }
    }

    //printf("CANNoT FIND\n");

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
            
            if(h != NULL){// && !h->type->IsEquivalentTo(Type::errorType)){
                printf("Extends check found. Return\n");
                return h;
            }
            
        }

    }

    

    if(members_i == NULL){
        //did not find
    }
    // Return error did not find
    // Decl *temp = new Decl(id);
    // temp->type = Type::errorType;
    // return temp;
    
    return members_i;
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
    hash = new Hashtable<Decl*>();
}

bool InterfaceDecl::Check(bool reportError) {
    printf("INTERFACE CHECK\n");
    for(int i = 0; i < members->NumElements(); ++i){

        // if member already there, return error
        printf("%s\n", members->Nth(i)->getIdentifier()->getName());
        printf("SDFDSF\n");

        Decl* d = hash->Lookup(members->Nth(i)->getIdentifier()->getName());
        
        if (d == NULL) {
            // add to new hashmap
            hash->Enter(members->Nth(i)->getIdentifier()->getName(), members->Nth(i));
        }
        else {
            // ERROR
            if(reportError)
                ReportError::DeclConflict(members->Nth(i), d);
        }

    }
    printf("ADD ALL TO HASH\n");
    for(int i = 0; i < members->NumElements(); ++i){
        members->Nth(i)->Check(reportError);
    }
    return true;
}

Decl *InterfaceDecl::CheckHash(Identifier *id){
    for(int i = 0; i < this->GetMembers()->NumElements(); ++i){
        if(strcmp(this->GetMembers()->Nth(i)->getIdentifier()->getName(), id->getName()) == 0){
            printf("Found Fn in Interface\n");
            return this->GetMembers()->Nth(i);
        }
    }
    return NULL;
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

bool FnDecl::CompareFnDecls(FnDecl* fd){
    if(fd->GetFormals()->NumElements() != this->GetFormals()->NumElements()){
        return false;
    }
    else{
        bool error = false;
        for(int i = 0; i < this->GetFormals()->NumElements(); ++i){
            if(!this->GetFormals()->Nth(i)->type->IsEquivalentTo(fd->GetFormals()->Nth(i)->type)){
                return false;
                break;
            }
        }
        if(!fd->GetReturnType()->IsEquivalentTo(this->GetReturnType())){
            return false;
        }
    }
    return true;
}

bool FnDecl::Check(bool reportError) {

    printf("FnDecl Check\n");
    //check to see if inheriting function from somewhere
    returnType->Check(reportError);
    
    Node *parent = this->GetParent();
    if(dynamic_cast<ClassDecl*>(parent) != nullptr){
        printf("Functino is in Class\n");
        ClassDecl* cd = dynamic_cast<ClassDecl*>(parent);
        Decl* d = cd->CheckHash(this->getIdentifier()); //looks back in extends first, then current class
        if(d != NULL && d->GetParent() != this->GetParent()){
            if(dynamic_cast<FnDecl*>(d) == nullptr){
                // Error Declaration of '___' here conflicts with declaration on line ___
                if(reportError)
                    ReportError::DeclConflict(this, d);
                //printf("--------------------------------------------------------\n");
            }
            else{
                FnDecl* fd = dynamic_cast<FnDecl*>(d);
                //check return type and parameters
                if(!CompareFnDecls(fd)){
                    //report error
                    //printf("---------------------------------------------------------\n");
                    if(reportError)
                        ReportError::OverrideMismatch(this);
                }
                
            }
        }
        else{
            //Check implements
            printf("Implement Check\n");
            Node *program = parent->GetParent();
            
            for(int i = 0; i < cd->getImplements()->NumElements(); ++i){

                yyltype y;
                Identifier *temp_ident = new Identifier(y, strdup(cd->getImplements()->Nth(i)->typeName));
                Decl* idt = program->CheckHash(temp_ident);
                if(dynamic_cast<InterfaceDecl*>(idt) == nullptr){
                    //not an interface declaration
                }
                else{
                    FnDecl *fd = dynamic_cast<FnDecl *>(dynamic_cast<InterfaceDecl*>(idt)->CheckHash(this->getIdentifier()));
                    if(fd != NULL){
                        if(!CompareFnDecls(fd)){
                            //report error
                            
                            cd->entireinterfaceimplemented = false;
                            
                            cd->interfaces_not_implemented->Append(cd->getImplements()->Nth(i));
                            
                            //printf("---------------------------------------------------------\n");
                            if(reportError)
                                ReportError::OverrideMismatch(this);
                            break;
                        }
                        if(cd->functions_added_per_implement->Lookup(cd->getImplements()->Nth(i)->getIdentifier()->getName()) == NULL)
                            cd->functions_added_per_implement->Enter(cd->getImplements()->Nth(i)->getIdentifier()->getName(), new List<Identifier*>);
                        bool exists = false;
                        for(int ident = 0; ident < cd->functions_added_per_implement->Lookup(cd->getImplements()->Nth(i)->getIdentifier()->getName())->NumElements(); ++ident){
                            if(strcmp(this->id->getName(), cd->functions_added_per_implement->Lookup(cd->getImplements()->Nth(i)->getIdentifier()->getName())->Nth(ident)->getName()) == 0){
                                exists = true;
                                break;
                            }
                        }
                        if(!exists)
                            cd->functions_added_per_implement->Lookup(cd->getImplements()->Nth(i)->getIdentifier()->getName())->Append(this->id);
                    }
                }
            }
        }
    }
    if(!reportError)
        return true;

    printf("Out of class\n");

    // loop through formals
    
    for(int i = 0; i < formals->NumElements(); ++i){
        // TODO Check if overriding function
        
        // if formal already there, return error
        Decl* d = hash->Lookup(formals->Nth(i)->getIdentifier()->getName());
        
        if (d == NULL) {
            // add to new hashmap
            hash->Enter(formals->Nth(i)->getIdentifier()->getName(), formals->Nth(i));
        }
        else if(d!=formals->Nth(i)){
            // ERROR
            if(reportError)
                ReportError::DeclConflict(formals->Nth(i), d);
        }

        formals->Nth(i)->Check(reportError);

    }
    if(body != NULL)
        body->Check(reportError); // then go through body and ensure type correctness and such 
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

