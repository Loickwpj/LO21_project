#ifndef NotesManager_hpp
#define NotesManager_hpp

#include "Note.h"

#endif


template<class T> class Singleton{
private:
    //HANDLER
    
    struct Handler {
        T* instance;
        Handler () : instance(nullptr) {}
        ~Handler() {if (instance) delete instance; instance=nullptr;};
    };
    
    //static attribute handler
    static Handler handler;
    
    //Duplication forbidden
    T& operator=(const T&);

public:
    
    //static methods
    static T& getInstance();
    static void libererInstance();
    
};

class NotesManager : public Singleton<NotesManager>{
private:
    Note** notes;
    unsigned int nbNote, nbMaxNote;
    string filename;
    NotesManager() : notes(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}
    //Duplication forbidden
    NotesManager(const NotesManager&);
    ~NotesManager() {for (unsigned int i=0; i<nbNote; i++) delete notes[i]; delete [] notes;};
public:
    //Accessor
    unsigned int getNbNote() const {return nbNote;}
    
    //Methods
    Note& getNewNote(const string& id);
    Note& getNote(const string& id);
};

class RelationsManager : public Singleton<RelationsManager>{
private:
    Relation** relations;
    unsigned int nbRelation, nbMaxRelation;
    string filename;
    RelationsManager() : relations(nullptr), nbRelation(0), nbMaxRelation(0), filename("tmp.dat") {}
    //Duplication forbidden
    RelationsManager(const NotesManager&);
    ~RelationsManager() {for (unsigned int i=0; i<nbRelation; i++) delete relations[i]; delete [] relations;};
public:
    //Accessor
    unsigned int getNbRelation() const {return nbRelation;}
    
    //Methods
    Relation& getNewRelation(const string&, const string&);
    void addRelation(Relation*);
    Relation& getRelation(const string&);
};

class Corbeille : public Singleton<Corbeille>{
private:
    Note** notesSuppr;
    unsigned int nbNote, nbMaxNote;
    string filename;
    Corbeille() : notesSuppr(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}
    //Duplication forbidden
    Corbeille(const NotesManager&);
    ~Corbeille() {for (unsigned int i=0; i<nbNote; i++) delete notesSuppr[i]; delete [] notesSuppr;};
public:
    void deleteNote(const string&);
    void delete_all();
    void restore(const string&);
};



/*class NotesManager{
private:
    Note** notes;
    unsigned int nbNote, nbMaxNote;
    string filename;
    NotesManager() : notes(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}
    //Duplication forbidden
    NotesManager(const NotesManager&);
    NotesManager& operator=(const NotesManager&);
    ~NotesManager() {for (unsigned int i=0; i<nbNote; i++) delete notes[i]; delete [] notes;  };

    
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
    Note& getNote(const string& id);
    
    
    
};
*/
