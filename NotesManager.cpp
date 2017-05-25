#ifndef notesmanager_cpp
#define notesmanager_cpp

#include "NotesManager.hpp"


#endif


NotesManager::Handler NotesManager::handler = Handler();

NotesManager& NotesManager::getInstance(){
    if(!handler.instance) handler.instance = new NotesManager();
    return *handler.instance;
}
void NotesManager::libererInstance(){
    if(handler.instance) delete handler.instance;
    handler.instance = nullptr;
}


Note& NotesManager::getNewNote(){
    
}
