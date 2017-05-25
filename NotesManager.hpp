#ifndef NotesManager_hpp
#define NotesManager_hpp

#include "Note.h"

#endif

class NotesManager{
private:
    Note** notes;
    unsigned int nbNote, nbMaxNote;
    string filename;
    NotesManager() : notes(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}
    //Duplication forbidden
    NotesManager(const NotesManager&);
    NotesManager& operator=(const NotesManager&);
    ~NotesManager();

    
    //HANDLER
    
    struct Handler {
        NotesManager* instance;
        Handler () : instance(nullptr) {}
        ~Handler() {if (instance) delete instance; instance=nullptr;};
    };
    
    
    //static attribute handler
    static Handler handler;
    
public:
    
    //static methods
    static NotesManager& getInstance();
    static void libererInstance();
    
    //Accessor
    unsigned int getNbNote() const {return nbNote;}
    
    //Methods
    Note& getNewNote(const string& id);
    Article& getArticle(const string& id);
    static NotesManager& getInstance();
    static void libererInstance();
    
    
    
};
