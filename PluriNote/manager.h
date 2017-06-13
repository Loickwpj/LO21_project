#ifndef manager_hpp
#define manager_hpp
#include <QXmlStreamReader>

#include "singleton.h"
//#include "noteediteur.h"
#include "relation.h"

class Relation;
class Note;

/***************************************
**          NOTESMANAGER              **
***************************************/

class NotesManager : public Singleton<NotesManager>{
    friend class Singleton<NotesManager>;
private:
    Note** notes;
    unsigned int nbNote, nbMaxNote;
    mutable QString filename;

    ///CONSTRUCTEUR
    NotesManager(const NotesManager&);
    NotesManager() : Singleton<NotesManager>(), notes(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}

    ///DESTRUCTEUR
    ~NotesManager() {}

public:

    ///FACTORY
    static std::map<QString,Note*> m_map;
    static void Register(const QString& key,Note* obj);
    Note* Create(const QString& key) const;

    ///ACCESSEUR
    unsigned int getNbNote() {return nbNote;}
    Note& getNote(const QString& id);
    Note* getNote( int i);


    ///MANIPULATION DES NOTES
    virtual Note* getNewNote(const QString&);
    void supprimerNote(int);
    void addNote(Note*);

    
    
    ///MANIPULAITON FICHIER
    QString getFilename() const { return filename; }
    void setFilename(const QString& f) { filename=f; }
    void load(); // load notes from file filename
    void loadArticle(QXmlStreamReader &xml);
    void loadTask(QXmlStreamReader &xml);
    void loadMultimedia(QXmlStreamReader &xml, QString type);
    void save() const; // save notes in file filename
    
    ///ITERATOR
    class iterator{
        friend class NotesManager;

        Note** currentN;

        iterator(Note**n): currentN(n){}

    public:
        bool operator!=(iterator it) const {return currentN != it.currentN;}
        Note* value() const {return *currentN;}
        iterator& operator++() {currentN++; return *this;}

    };

    iterator begin() const{ return iterator(notes); }
    iterator end() const{return iterator(notes + nbNote);}



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

    ///CONSTRUCTEURS
    RelationsManager() : relations(nullptr), nbRelation(0), nbMaxRelation(0), filename("tmp.dat") {}
    RelationsManager(const NotesManager&);

    ///DESTRUCTEUR
    ~RelationsManager() {}

public:
    ///ACCESSEUR
    unsigned int getNbRelation() const {return nbRelation;}
    Relation& getRelation(const QString&);
    Relation& getRelation(unsigned int);

    ///MANIPULATION RELATIONS
    Relation& getNewRelation(const QString&, const QString&);
    void addRelation(Relation*);
    void chercherCouple(Note*);

    ///METHOD FICHIER XML
     QString getFilename() const { return filename; }
     void setFilename(const QString& f) { filename=f; }
     void load(); // load notes from file filename

     void saveRelation() const; // save relation in file filename
     void loadRelations();
     Relation* loadRelation(QXmlStreamReader &xml);
     void loadCouple(QXmlStreamReader &xml, Relation* r);


    ///ITERATOR
    class iterator{
        friend class RelationsManager;
        Relation** currentN;

        iterator(Relation**n): currentN(n){}

    public:
        bool operator!=(iterator it) const {return currentN != it.currentN;}
        Relation* value() const {return *currentN;}
        iterator& operator++() {currentN++; return *this;}

    };

    iterator begin() const{ return iterator(relations); }
    iterator end() const{return iterator(relations + nbRelation);}


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

    ///CONSTRUCTEURS
    Corbeille() : notesSuppr(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}
    Corbeille(const NotesManager&);

    ///DESTRUCTEUR
    ~Corbeille() {};

public:

    ///ACCESSEURS
    Note* getNote(Note*);
    Note* getNote(int);
    unsigned int getNbNote(){return nbNote;}

    ///MANIPULATION NOTES
    void addNoteCorbeille(Note*);
    void deleteNote(const QString&);
    void deleteAll();
    void restaurer(unsigned int);
    void supprimerNote(unsigned int id);

    ///ITERATOR
    class iterator{
        friend class Corbeille;
        Note** currentN;

        iterator(Note**n): currentN(n){}

    public:
        bool operator!=(iterator it) const {return currentN != it.currentN;}
        Note* value() const {return *currentN;}
        iterator& operator++() {currentN++; return *this;}

    };

    iterator begin() const{ return iterator(notesSuppr); }
    iterator end() const{return iterator(notesSuppr + nbNote);}

};



#endif
