#ifndef manager_cpp
#define manager_cpp

#include "manager.h"
#include <QDebug>


#endif

/**********************************************
 **             NOTESMANAGER                 **
 **********************************************/

std::map<QString,Note*> NotesManager::m_map= std::map<QString,Note*>();

void NotesManager::Register(const QString& key,Note* obj)
{
    //si la clé n'est pas déjà présente
    if(m_map.find(key)==m_map.end())
    {
        //on ajoute le type d'objet dans le map
        m_map[key]=obj;
    }

}

Note* NotesManager::Create(const QString& key) const
{
    Note* tmp=0;
    std::map<QString, Note*>::const_iterator it=m_map.find(key);

    //si l'itérateur ne vaut pas map.end(), cela signifie que la clé à été trouvée
    if(it!=m_map.end())
    {
        tmp=((*it).second)->clone();
    }
    tmp->setId();
    return tmp;
}

void NotesManager::editNote(Note* n, const QString& type){
    if (type == "Task"){
        Task* t =(dynamic_cast<Task*>(n));
        TaskEditeur* te = new TaskEditeur(t);
        te->show();
    }

    if (type == "Article"){
        Article* a =(dynamic_cast<Article*>(n));
        ArticleEditeur* ae = new ArticleEditeur(a);
        ae->show();
    }

    if (type == "Image"){
        Image* i =(dynamic_cast<Image*>(n));
        ImageEditeur* ie = new ImageEditeur(i);
        ie->show();
    }

    if (type == "Video"){
        Video* v =(dynamic_cast<Video*>(n));
        VideoEditeur* ve = new VideoEditeur(v);
        ve->show();
    }

    if (type == "Audio"){
        Audio* au =(dynamic_cast<Audio*>(n));
        AudioEditeur* aue = new AudioEditeur(au);
        aue->show();
    }

}

 Note* NotesManager::getNewNote(const QString& type){
    Note* n = Create(type);
    addNote(n);
    editNote(n,type);
    return n;
}


void NotesManager::addNote(Note* n){
  /*  for(unsigned int i = 0; i < nbNote; i++){
        if(notes[i]->getId() == n->getId())
            throw NotesException("Article existe deja");
    }*/
    if(nbNote == nbMaxNote){
        Note ** old_notes = notes;
        notes = new Note*[nbMaxNote+5];
        for(unsigned int i = 0; i < nbNote; i++){
            notes[i] = old_notes[i];
        }
        nbMaxNote += 5;
        delete[] old_notes;
    }

    notes[nbNote++] = n;

}

void NotesManager::supprimerNote(int id){
    notes[id]=notes[--nbNote];

}



/**********************************************
**             RELATIONSMAANGER              **
***********************************************/


Relation& RelationsManager::getNewRelation(const QString& id,const QString& desc){

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

Relation& RelationsManager::getRelation(const QString& title){
    for(int i = 0; i <nbRelation; i++){
        if( relations[i]->getTitle() == title) return *relations[i];
    }
    throw NotesException("Relation n existe pas");
}



/**********************************************
 **                 CORBEILLE                **
 ***********************************************/


void Corbeille::addNoteCorbeille(Note* n){

    if(nbNote == nbMaxNote){
        Note ** old_notes = notesSuppr;
        notesSuppr = new Note*[nbMaxNote+5];
        for(unsigned int i = 0; i < nbNote; i++){
            notesSuppr[i] = old_notes[i];
        }
        nbMaxNote += 5;
        delete[] old_notes;
    }
    notesSuppr[nbNote++]=n;

}

Note* Corbeille::getNote(Note* n){
    for (unsigned int i=0; i<nbNote; i++){
        if (notesSuppr[i]->getId() == n->getId() ) return notesSuppr[i];
    }
    throw NotesException("Error");
}

Note* Corbeille::getNote(int i){
    return notesSuppr[i];
}

void Corbeille::deleteNote(const QString & id){
    unsigned int i=0;
    while (i<nbNote && notesSuppr[i]->getId() != id) i++;
    if (i==nbNote) throw NotesException("Cette note n'est pas dans la corbeille");
    delete notesSuppr[i];
    notesSuppr[i]=notesSuppr[nbNote-1];
    nbNote--;

}

void Corbeille::deleteAll(){

    for (unsigned int i=0; i<nbNote; i++)delete notesSuppr[i];
    delete [] notesSuppr;
    notesSuppr=nullptr;
    nbNote=0;
    nbMaxNote=0;
}

void Corbeille::supprimerNote(int id){
    /*if (nbNote == 1 || id == nbNote-1 ) notesSuppr[--nbNote] = nullptr;
    else{*/


        for (unsigned int i =0; i<nbNote;i++){
           if (notesSuppr[i]->getId() == id){

               if (nbNote-1 == i){ notesSuppr[i]=nullptr; nbNote--;}
               else{
                   if (nbNote == 1) {notesSuppr[--nbNote]=nullptr;}
                   else {notesSuppr[i]=notesSuppr[--nbNote];}
               }
        }
    }
}


void Corbeille::restaurer(int id){
    for (unsigned int i=0; i<nbNote; i++){
        if (notesSuppr[i]->getId() == id ) NotesManager::getInstance().addNote(notesSuppr[i]);
    }
    supprimerNote(id);
}

/*
void Corbeille::restore(const QString& id){
    for (unsigned int i =0;i<nbNote; i++){
        if (notesSuppr[i]->getId() == id ){
            ..
        }
    }
}
*/


