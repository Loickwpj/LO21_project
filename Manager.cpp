#ifndef notesmanager_cpp
#define notesmanager_cpp

#include "Manager.hpp"


#endif


/**********************************************
**               NOTESMANAGER                **
***********************************************/



/**********************************************
**             RELATIONSMAANGER              **
***********************************************/


Relation& RelationsManager::getNewRelation(const string& id,const string& desc){
    
    Relation *r = new Relation(id,desc);
    addRelation(r);
    return *r;
}

void RelationsManager::addRelation(Relation* r){
    for(int i = 0; i < nbRelation; i++){
        if(r->getTitle() == relations[i]->getTitle())
            throw NotesException("Relation existe deja");
    }
    if(nbRelation == nbMaxRelation){
        Relation** newRelation = new Relation* [nbMaxRelation+5];
        for (unsigned int i=0; i<nbMaxRelation; i++){
            newRelation[i]= new Relation (*relations[i]);
        }
        Relation** oldRelations = relations;
        relations = newRelation;
        for (unsigned int i=0; i<nbMaxRelation; i++){
            delete oldRelations[i];
        }
        delete [] oldRelations;
        nbMaxRelation+=5;
        }
    relations[nbRelation++]=r;
}

Relation& RelationsManager::getRelation(const string& title){
    for(int i = 0; i <nbRelation; i++){
        if( relations[i]->getTitle() == title) return *relations[i];
    }
    throw NotesException("Relation n existe pas");
}

/**********************************************
 **                 CORBEILLE                **
 ***********************************************/

void Corbeille::deleteNote(const string & id){
    unsigned int i=0;
    while (i<nbNote && notesSuppr[i]->getId() != id) i++;
    if (i==nbNote) throw NotesException("Cette note n'est pas dans la corbeille");
    delete notesSuppr[i];
    notesSuppr[i]=notesSuppr[nbNote-1];
    nbNote--;
}

void Corbeille::delete_all(){
    for (unsigned int i=0; i<nbMaxNote; i++){
        delete notesSuppr[i];
    }
    delete [] notesSuppr;
    notesSuppr = nullptr;
}
/*
void Corbeille::restore(const string& id){
    for (unsigned int i =0;i<nbNote; i++){
        if (notesSuppr[i]->getId() == id ){
            ..
        }
    }
}
*/


