#ifndef notesmanager_hpp
#define notesmanager_hpp
#include "Singleton.hpp"

/***************************************
**          NOTESMANAGER              **
***************************************/

class NotesManager : public Singleton<NotesManager>{
    friend class Singleton<NotesManager>;
private:
    Note** notes;
    unsigned int nbNote, nbMaxNote;
    string filename;
    //Duplication forbidden
    NotesManager(const NotesManager&);
    ~NotesManager() {for (unsigned int i=0; i<nbNote; i++) delete notes[i]; delete [] notes;};
    NotesManager() : Singleton<NotesManager>(), notes(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}
    
public:
    //Accessor
    unsigned int getNbNote() const {return nbNote;}
    
    //Methods
    Note& getNewNote(const string& id);
    Note& getNote(const string& id);
};


/***************************************
 **         RELATIONSMANAGER          **
 ***************************************/

class RelationsManager : public Singleton<RelationsManager>{
        friend class Singleton<RelationsManager>;
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



/***************************************
 **            CORBEILLE              **
 ***************************************/

class Corbeille : public Singleton<Corbeille>{
    friend class Singleton<Corbeille>;
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



#endif
