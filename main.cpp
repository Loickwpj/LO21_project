#include "Manager.hpp"
#include "Note.hpp"
#include <iostream>

int main(){
    
    NotesManager::Register("Article", new Article ());
    NotesManager& n = NotesManager::getInstance();
    n.getNewNote("Article")->setId("id1").setTitle("\{id2}");
    n.getNewNote("Article")->setId("id2");
    
    for (Note::Iterator it = Note::getIterator(); !it.isDone(); it.next()){
        for(NotesManager::SearchIterator sit= n.getSearchIterator("\{"+it.current()+"}"); !sit.isDone(); sit.next())
        {
            cout<<sit.current().getId()<<"\n";
        }
        
    }
    
    return 0;
    
}
