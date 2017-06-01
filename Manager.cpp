#ifndef notesmanager_cpp
#define notesmanager_cpp

#include "Manager.hpp"


#endif

/**********************************************
 **             NOTESMANAGER                 **
 **********************************************/

std::map<string,Note*> NotesManager::m_map= std::map<string,Note*>();

void NotesManager::Register(const string& key,Note* obj)
{
    //si la clé n'est pas déjà présente
    if(m_map.find(key)==m_map.end())
    {
        //on ajoute le type d'objet dans le map
        m_map[key]=obj;
    }

}

Note* NotesManager::Create(const std::string& key) const
{
    Note* tmp=0;
    std::map<string, Note*>::const_iterator it=m_map.find(key);
    
    //si l'itérateur ne vaut pas map.end(), cela signifie que que la clé à été trouvée
    if(it!=m_map.end())
    {
        tmp=((*it).second)->clone();
    }
    
    return tmp;
}

Note* NotesManager::getNewNote(const string& type){
    Note* n = Create(type);
    addNote(n);
    return n;
}

void NotesManager::addNote(Note* n){
    for(int i = 0; i < nbNote; i++){
        if(notes[i]->getId() == n->getId())
            throw NotesException("Article existe deja");
    }
    if(nbNote == nbMaxNote){
        Note ** old_notes = notes;
        notes = new Note*[nbMaxNote+5];
        for(int i = 0; i < nbNote; i++){
            notes[i] = old_notes[i];
        }
        nbMaxNote += 5;
        delete[] old_notes;
    }
    
    notes[nbNote++] = n;
}



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


