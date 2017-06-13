#ifndef manager_hpp
#define manager_hpp
#include <QXmlStreamReader>

/** @file manager.h
 */

#include "singleton.h"
//#include "noteediteur.h"
#include "relation.h"

class Relation;
class Note;

/***************************************
**          NOTESMANAGER              **
***************************************/

/**
 * @class NotesManager
 * @brief classe qui hérite de la classe Singleton et qui va nous permettre
 * d'une part de créer tout types de notes et d'autre part
 * d'être responsable du cycle de vie des notes qu'il créé
 *
 */

class NotesManager : public Singleton<NotesManager>{
    friend class Singleton<NotesManager>;
private:
    Note** notes;
    unsigned int nbNote, nbMaxNote;
    mutable QString filename;

    ///CONSTRUCTEUR

    /**
     * @fn NotesManager
     * @param référence sur NotesManager
     * @brief constructeur de recopie rendu privé
     *
     */
    NotesManager(const NotesManager&);

    /**
     * @fn NotesManager
     *@brief constructeur par défaut dont le tableau de couple est réduit
     * au pointeur nul
    */
    NotesManager() : Singleton<NotesManager>(), notes(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}

    ///DESTRUCTEUR
    ~NotesManager() {}

public:

    ///FACTORY

    /**
     * @brief m_map
     * attribut static qui va nous permettre d'associer un prototype de création
     * de note à un mot clé (exemples : "Article" est le mot-clé qui nous permet de créer un nouvel article)
     */
    static std::map<QString,Note*> m_map;

    /**
     * @fn Register
     * @param key : mot clé
     * @param obj : prototype
     * @brief
     * fonction qui nous permet d'associer un mot clé à un prototype
     */
    static void Register(const QString& key,Note* obj);

    /**
     * @fn Create
     * @param key : mot clé
     *@brief  fonction qui nous permet de créer une note en fonction
     * du mot clé qu'on a rentré en paramètre
     *
     * @return pointeur sur la note que l'on vient de créer
     */
    Note* Create(const QString& key) const;

    ///ACCESSEUR

    /**
     * @fn getNbNote
     *
     * @return nombre de note dans le Notesmanager
     */
    unsigned int getNbNote() {return nbNote;}

    /**
     * @fn getNote
     * @param id : string correspondant à l'id de la note qu'on cherche
     *
     * @return la note dont l'id a été passé en paramètre
     */
    Note& getNote(const QString& id);

    /**
     * @fn getNote
     * @param i : entier qui va prendre la valeur de tous les ids du notesmanager afin de parcourir les notes de celui-ci
     * @return la note située à la ième position dans le tableau de note de notesmanager
     */
    Note* getNote( int i);


    ///MANIPULATION DES NOTES

    /**
     * @fn getNewNote
     * @param mot clé qui indique quel type de note on souhaite créer
     * @return pointeur sur la note créée
     */
    virtual Note* getNewNote(const QString&);

    /**
     * @fn supprimerNote
     * @param entier qui correpond à l'id de la note que l'on souhaite supprimer du notesmanager
     */

    void supprimerNote(int);

    /**
     * @fn addNote
     * @param note que l'on vient de créer et qu'on souhaite ajouter au notesmanager
     */

    void addNote(Note*);

    
    
    ///MANIPULAITON FICHIER

    /**
     * @fn getFilename
     * @return le fichier associé au notesmanager dans lequel on sauve les données
     */
    QString getFilename() const { return filename; }


    /**
     * @fn setFilename
     * @param f : nouveau fichier
     */
    void setFilename(const QString& f) { filename=f; }

    /**
     * @fn load
     * @return les notes présentent dans le fichier correspondant à filename
     */
    void load(); // load notes from file filename

    /**
     * @fn loadArticle
     * @param xml
     *@brief  charge les articles présents dans filename
     */
    void loadArticle(QXmlStreamReader &xml);

    /**
     * @fn loadTask
     * @param xml
     *@brief  charge les tâches présentes dans filename
     */
    void loadTask(QXmlStreamReader &xml);

    /**
     * @fn loadMultimedia
     * @param xml
     * @param type
     *@brief  charge les différents types de multimédia (vidéo, audio, image) présents filename
     */

    void loadMultimedia(QXmlStreamReader &xml, QString type);

    /**
     * @fn save
     * @brief
     * permet de sauver les notes du notesmanager dans le fichier filename
     */
    void save() const; // save notes in file filename
    
    ///ITERATOR

    /**
     * @class iterator
     * @brief
     * permet de parcourir séquentiellement l'ensemble des notes présentent dans le notesmanager
     */
    class iterator{
        friend class NotesManager;

        Note** currentN;

        iterator(Note**n): currentN(n){}

    public:
        bool operator!=(iterator it) const {return currentN != it.currentN;}
        Note* value() const {return *currentN;}
        iterator& operator++() {currentN++; return *this;}

    };


    /**
     * @fn begin
     * @return  un iterateur pointant sur la première note du notesmanager
     */
    iterator begin() const{ return iterator(notes); }

    /**
     * @fn end
     * @return un iterateur pointant sur la dernière notes du notesmanager
     */
    iterator end() const{return iterator(notes + nbNote);}



};




/***************************************
 **         RELATIONSMANAGER          **
 ***************************************/
/**
 * @class RelationsManager
 * @brief
 * Cette classe hérite de la classe Singleton et permet d'une part de créer des relations (excepté Référence)
 * et est responsable du cycle de vie de celles-ci.
 */
class RelationsManager : public Singleton<RelationsManager>{
    friend class Singleton<RelationsManager>;
private:
    Relation** relations;
    unsigned int nbRelation, nbMaxRelation;
    QString filename;

    ///CONSTRUCTEURS
    /**
     * @fn RelationsManager
     *@brief  constructeur par défaut dont le tableau de relation est réduit au pointeur nul
     */

    RelationsManager() : relations(nullptr), nbRelation(0), nbMaxRelation(0), filename("tmp.dat") {}

    /**
     * @fn RelationsManager
     * @brief constructeur de recopie rendu privé
     */
    RelationsManager(const NotesManager&);

    ///DESTRUCTEUR
    ~RelationsManager() {}

public:
    ///ACCESSEUR

    /**
     * @fn getNbRelation
     * @return le nombre de relations de relationsmanager
     */
    unsigned int getNbRelation() const {return nbRelation;}

    /**
     * @fn getRelation
     * @param nom de la relation qu'on cherche
     * @return retourne la relation dont le nom est passé en paramètre
     */

    Relation& getRelation(const QString&);

    /**
     * @fn getRelation
     * @param entier qui correspond à la ième relation du relationsmanager
     * @return la relation occupant la position i du relations manager
     */

    Relation& getRelation(unsigned int);

    ///MANIPULATION RELATIONS

    /**
     * @fn getNewRelation
     * @param titre de la relation
     * @param description de la relation
     * @return créée une relation dont le titre et la description sont passés en argument
     */
    Relation& getNewRelation(const QString&, const QString&);

    /**
     * @fn addRelation
     * @param pointeur sur relation qu'on vient de créer
     * @brief  permet d'ajouter une nouvelle relation au tableau de relations du relationsmanager
     */

    void addRelation(Relation*);

    /**
     * @fn chercherCouple
     * @param pointeur sur une note dont on cherche toutes les occurences dans les différents couples d'une relation
     */
    void chercherCouple(Note*);

    ///METHOD FICHIER XML
    ///

    /**
     * @fn getFilename
     * @return le fichier associé au notesmanager dans lequel on sauve les données
     */

     QString getFilename() const { return filename; }

     /**
      * @fn setFilename
      * @param f : nouveau fichier que l'on souhaite utiliser pour sauvegarder et charger les relations
      */

     void setFilename(const QString& f) { filename=f; }

     /**
      * @fn load
      *@brief  permet de charger l'ensemble des relations sauvegardées dans filename
      */
     void load();

     /**
      * @fn saveRelation
      *@brief  permet de sauvegarder l'ensemble des relations de relationsmanager
      */
     void saveRelation() const;


     void loadRelations();

     /**
      * @fn loadRelation
      *@brief  permet de charger l'ensemble des relations sauvegardées dans filename
      */

     Relation* loadRelation(QXmlStreamReader &xml);

     /**
      * @fn loadCouple
      * @param r : relation à laquelle le couple que l'on charge appartient
      * @brief
      * permet de charger les couples d'une relation
      */
     void loadCouple(QXmlStreamReader &xml, Relation* r);


    ///ITERATOR

     /**
      * @class iterator
      *@brief  permet de parcourir séquentiellement l'ensemble des relations de relationsmanager
      */
     class iterator{
        friend class RelationsManager;
        Relation** currentN;

        iterator(Relation**n): currentN(n){}

    public:
        bool operator!=(iterator it) const {return currentN != it.currentN;}
        Relation* value() const {return *currentN;}
        iterator& operator++() {currentN++; return *this;}

    };
     /**
     * @fn begin
     * @return itérateur correspondant à la première relation de relationsmanager
     *
     */
    iterator begin() const{ return iterator(relations); }

    /**
     * @fn end
     * @return itérateur correspondant à la dernière relation de relationsmanager
     */
    iterator end() const{return iterator(relations + nbRelation);}


};




/***************************************
 **            CORBEILLE              **
 ***************************************/
/**
 * @class  Corbeille
 *@brief  classe qui hérite de Singleton et qui gère les notes qui ont été supprimé
 * en laissant à l'utilisateur la possibilité de les restaurer
 */
class Corbeille : public Singleton<Corbeille>{
    friend class Singleton<Corbeille>;
private:
    Note** notesSuppr;
    unsigned int nbNote;
    unsigned int nbMaxNote;
    QString filename;

    ///CONSTRUCTEURS
    /**
     * @fn Corbeille
     *@brief  constructeur par défaut de la corbeile qui retourne une corbeille dont le tableau de notes est vide
     */

    Corbeille() : notesSuppr(nullptr), nbNote(0), nbMaxNote(0), filename("tmp.dat") {}

    /**
     * @fn Corbeille
     * @brief constructeur de recopie rendu privé
     *
     */

    Corbeille(const NotesManager&);

    ///DESTRUCTEUR
    ~Corbeille() {};

public:

    ///ACCESSEURS
    /**
     * @fn getNote
     * @return la note de la corbeille qui correspond à celle passée en paramètre
     */

    Note* getNote(Note*);

    /**
     * @fn getNote
     * @return note située à la i ème position de la corbeille
     */
    Note* getNote(int);

    /**
     * @fn getNbNote
     * @return le nombre de note dans la corbeille
     */

    unsigned int getNbNote(){return nbNote;}

    ///MANIPULATION NOTES

    /**
     * @fn addNoteCorbeille
     * @param note que l'on souhaite placée dans la corbeille
     * @brief met dans la corbeille la note passée en paramètre
     */

    void addNoteCorbeille(Note*);

    void deleteNote(const QString&);
    /**
     * @fn deleteAll
     * @brief
     * permet de vider la corbeille et supprimer définitivement toutes les notes
     */

    void deleteAll();

    /**
     * @fn restaurer
     * @param id de la note à restaurer
     * @brief permet de restaurer la note dont 'id est passé en paramètre
     */
    void restaurer(unsigned int);
    void supprimerNote(unsigned int id);

    ///ITERATOR

    /**
     * @class iterator
     * @brief
     * permet de parcourir séquentiellement les notes de la corbeille
     */
    class iterator{
        friend class Corbeille;
        Note** currentN;

        iterator(Note**n): currentN(n){}

    public:
        bool operator!=(iterator it) const {return currentN != it.currentN;}
        Note* value() const {return *currentN;}
        iterator& operator++() {currentN++; return *this;}

    };
    /**
     * @fn begin
     * @return itérateur pointant sur la première note dans la corbeille
     */
    iterator begin() const{ return iterator(notesSuppr); }

    /**
     * @fn end
     * @return itérateur pointant sur la dernière note dans la corbeille
     */
    iterator end() const{return iterator(notesSuppr + nbNote);}

};



#endif
