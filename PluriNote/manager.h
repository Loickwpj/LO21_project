#ifndef manager_hpp
#define manager_hpp
#include "singleton.h"
#include "note.h"
#include "noteediteur.h"
#include "relation.h"
#include <map>

/***************************************
**          NOTESMANAGER              **
***************************************/

class NotesManager : public Singleton<NotesManager>{
    friend class Singleton<NotesManager>;
private:
    Note** notes;
    unsigned int nbNote, nbMaxNote;
    QString filename;
    //Duplication forbidden
    NotesManager(const NotesManager&);
    ~NotesManager() {for (unsigned int i=0; i<nbNote; i++) delete notes[i]; delete [] notes;};
    NotesManager() : Singleton<NotesManager>(), notes(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}


public:

    //FACTORY
    static std::map<QString,Note*> m_map;

    //Fonction qui associe clé <=> prototype
    static void Register(const QString& key,Note* obj);

    //Celle qui va créer les objets
    Note* Create(const QString& key) const;

    //Accessor
    unsigned int getNbNote() const {return nbNote;}

    //methods
    virtual Note* getNewNote(const QString&);
    Note& getNote(const QString& id);
    void editNote(Note*,const QString&);
    void supprimerNote(int);
    void addNote(Note*);
/*
    /// Class SearchIterator
    class SearchIterator{
        friend class NotesManager;
        Note** currentN;
        int nbRemain;
        std::string toFind;
        SearchIterator(Note** n, int nb, std::string tf): currentN(n), nbRemain(nb), toFind(tf){
            while(nbRemain > 0 && (**currentN).getTitle().find(toFind) == std::string::npos){
                currentN++;
                nbRemain--;
            }
        }
    public:
        bool isDone()const {return nbRemain == 0;}
        const Note& current() const{ return **currentN;}
        void next(){
            if(isDone())
                throw NotesException("ERROR : fin de la collection");
            currentN++;
            nbRemain--;
            while(nbRemain > 0 && (**currentN).getTitle().find(toFind) == std::string::npos){
                currentN++;
                nbRemain--;
            }
        }
    };

    SearchIterator getSearchIterator(std::string tf) const{
        return SearchIterator(notes, nbNote, tf);

    }

*/


};


/***************************************
 **         RELATIONSMANAGER          **
 ***************************************/

class RelationsManager : public Singleton<RelationsManager>{
        friend class Singleton<RelationsManager>;
private:
    Relation** relations;
    unsigned int nbRelation, nbMaxRelation;
    QString filename;
    RelationsManager() : relations(nullptr), nbRelation(0), nbMaxRelation(0), filename("tmp.dat") {}
    //Duplication forbidden
    RelationsManager(const NotesManager&);
    ~RelationsManager() {for (unsigned int i=0; i<nbRelation; i++) delete relations[i]; delete [] relations;};
public:
    //Accessor
    unsigned int getNbRelation() const {return nbRelation;}

    //Methods
    Relation& getNewRelation(const QString&, const QString&);
    void addRelation(Relation*);
    Relation& getRelation(const QString&);
};



/***************************************
 **            CORBEILLE              **
 ***************************************/

class Corbeille : public Singleton<Corbeille>{
    friend class Singleton<Corbeille>;
private:
    Note** notesSuppr;
    unsigned int nbNote;
    unsigned int nbMaxNote;
    QString filename;
    Corbeille() : notesSuppr(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}
    //Duplication forbidden
    Corbeille(const NotesManager&);
    ~Corbeille() {for (unsigned int i=0; i<nbNote; i++) delete notesSuppr[i]; delete [] notesSuppr;};
public:
    Note* getNote(Note*);
    Note* getNote(int);
    void addNoteCorbeille(Note*);
    void deleteNote(const QString&);
    void deleteAll();
    void restaurer(int);
    unsigned int getNbNote(){return nbNote;}
    void supprimerNote(int id);
};



#endif
