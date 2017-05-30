#include "Note.h"
#include <iostream>

using namespace std;
/*
NotesManager::Handler NotesManager::handler = Handler();

NotesManager& NotesManager::getInstance(){
    if(!handler.instance) handler.instance = new NotesManager();
    return *handler.instance;
}
void NotesManager::libererInstance(){
    if(handler.instance) delete handler.instance;
    handler.instance = nullptr;
}

*/



/*********************************************************************
***                       Memento Article                         ***
**********************************************************************/


Article& Article::addMemento() {
        if(nbMemento == nbMax){
        MementoA** oldCareTaker = careTaker;
        nbMax += 5;
        careTaker = new MementoA*[nbMax];
        for(unsigned int i =0; i < nbMemento; i++)
            careTaker[i] = oldCareTaker[i];
        delete[] oldCareTaker;
    }
    careTaker[nbMemento++]= createMemento(); // crée un memento et l'ajoute au tableau des mementos
    return *this;
}

Article& Article::getPreviousMemento() {
    unsigned int i=nbMemento-1;
    setText(careTaker[i]->text);
    SetTitle(careTaker[i]->title);
    SetArchive(careTaker[i]->archive);
    SetDateCreation(careTaker[i]->dateCreation);
    setDateLastModif(careTaker[i]->dateLastModif);
    delete careTaker[i];
    nbMemento--;
    return *this;
}



/*********************************************************************
***                       Memento Tache                             ***
**********************************************************************/


Tache& Tache::addMemento() {
        if(nbMemento == nbMax){
        MementoT** oldCareTaker = careTaker;
        nbMax += 5;
        careTaker = new MementoT*[nbMax];
        for(unsigned int i =0; i < nbMemento; i++)
            careTaker[i] = oldCareTaker[i];
        delete[] oldCareTaker;
    }
    careTaker[nbMemento++]= createMemento(); // crée un memento et l'ajoute au tableau des mementos
    return *this;
}

Tache& Tache::getPreviousMemento() {
    unsigned int i=nbMemento-1;
    SetTitle(careTaker[i]->title);
    SetArchive(careTaker[i]->archive);
    SetDateCreation(careTaker[i]->dateCreation);
    setDateLastModif(careTaker[i]->dateLastModif);
    setAction(careTaker[i]->action);
    setPriority(careTaker[i]->priority);
    setDeadline(careTaker[i]->deadline);
    delete careTaker[i];
    nbMemento--;
    return *this;
}


/*********************************************************************
***                       Memento Multimedia                       ***
**********************************************************************/


Multimedia& Multimedia::addMemento() {
        if(nbMemento == nbMax){
        MementoM** oldCareTaker = careTaker;
        nbMax += 5;
        careTaker = new MementoM*[nbMax];
        for(unsigned int i =0; i < nbMemento; i++)
            careTaker[i] = oldCareTaker[i];
        delete[] oldCareTaker;
    }
    careTaker[nbMemento++]= createMemento(); // crée un memento et l'ajoute au tableau des mementos
    return *this;
}

Multimedia& Multimedia::getPreviousMemento() {
    unsigned int i=nbMemento-1;
    SetTitle(careTaker[i]->title);
    SetArchive(careTaker[i]->archive);
    SetDateCreation(careTaker[i]->dateCreation);
    setDateLastModif(careTaker[i]->dateLastModif);
    setDescription(careTaker[i]->description);
    setImage(careTaker[i]->image );
    delete careTaker[i];
    nbMemento--;
    return *this;
}



