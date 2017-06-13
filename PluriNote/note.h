#ifndef note_h
#define note_h
#include <QString>
#include <QDate>
#include <QXmlStreamWriter>

#include "noteediteur.h"
#include "ui_mainwindow.h"

class NoteEditeur;
class ArticleEditeur;
class TaskEditeur;
class ImageEditeur;
class VideoEditeur;
class AudioEditeur;
class MultimediaEditeur;

/*********************************************************************
***                            Execption                           ***
**********************************************************************/
/*! \class NoteExeption
   * \brief classe permettant de lancer des exeptions en cas d'erreur
   */

class NotesException{
public:
    NotesException(const QString& message):info(message) {}
    QString getInfo() const {
        return info;
    }
private:
    QString info;
};

/*********************************************************************/



/*********************************************************************
***                        Note Abstract Class                     ***
**********************************************************************/
/*! \class Note
   * \brief Abastraite dont hérite toutes les autres notes
   *
   * Cette classe ne peut pas être instanciée
   */

class Note {

protected:
    int id ;
    QString title ;
    QDate dateC;
    QDate dateM;
    bool archive;
    unsigned int nbMemento;
    unsigned int nbMax;


public:

    static int idIterator;

    /**
     * @brief Note
     * constructeur sans argument pour la creation automatique qui sera ensuite éditée
     */
    Note(): id(), title(""), dateC(QDate::currentDate()), dateM(QDate::currentDate()), archive(false),nbMemento(0),nbMax(5) {}
    virtual ~Note() {}
    /**
     * @brief Note
     * @param i
     * @param t
     * @param d_c
     * @param d_lm
     * @param a
     * constructeur avec argument que l'on utilise lors de la reconstruction après le chargement du fichier XML
     */
    Note(int i, const QString t=(QString)"", QDate d_c=QDate::currentDate(),
         QDate d_lm=QDate::currentDate(), bool a=false): id(i), title(t), dateC(d_c), dateM(d_lm), archive(a), nbMemento(0),nbMax(5){}

    /**
     * @brief clone
     * @return un pointeur sur note
     * methode virtuelle pur qui clone le type en question
     * elle sera redéfinie pour TOUTES les classes filles
     */
    virtual Note* clone() =0;

    ///ACCESSEURS
    /**
     * @brief getId
     * @return unsigned int
     * retourne l'id de la
     */
    unsigned int getId() const {return id;}
    /**
     * @brief getTitle
     * @return le titre
     */
    const QString& getTitle() const {return title;}
    /**
     * @brief getDateC
     * @return la date de creation de la note
     */
    const QDate& getDateC() const  {return dateC;}
    /**
     * @brief getDateM
     * @return la date de dernière modification
     */
    const QDate& getDateM() const  {return dateM;}
    /**
     * @brief GetArchive
     * @return retourne le booleen archive
     * permet de savoir si la note est archivée ou non
     */
    bool GetArchive() const {return archive;}
    /**
     * @brief getNbmemento
     * @return le nombre de version précédente
     */
    unsigned int getNbmemento() const {return nbMemento;}
    /**
     * @brief getType
     * @return le type de la fonction
     * nous avions implémenter cette fonction lorsque nous étions tenter d'utiliser des DownCast
     * nous avons finalement privilégié les methodes virtuelles
     */
    virtual const QString  getType() const =0;

    ///SET
    /**
     * @brief setTitle
     * @param newTitle
     * permet de modifier le titre d'une note
     */
    virtual void setTitle(const QString& newTitle) {title=newTitle ;}
    /**
     * @brief setDateLastModification
     * permet de modifier la date d'une note avec la date du jour
     */
    virtual void setDateLastModification() {dateM=QDate::currentDate();}
    /**
     * @brief setDateLastModification
     * @param newDate
     * permet de modifier la date d'une note avec une date donné (lorsqu'on récupère une version précédente)
     */
    virtual void setDateLastModification(QDate& newDate) {dateM=newDate;}
    /**
     * @brief setArchive
     * permet de rendre une note archivé ou non.
     */
    virtual void setArchive() {archive=!archive ;}
    /**
     * @brief setArchive
     * @param a
     * on utilise ici un paramètre pour modifier la valeur d'archive lors de la mise a jour d'une version précédente
     */
    virtual void setArchive(bool a) {archive=a ;}
    /**
     * @brief setId
     * met la valeur de l'id de la note avec la valeur incrémentée du dernier id
     */
    virtual void setId() {id = idIterator++;}
    /**
     * @brief setNotesListNote
     * @return retourne le titre de la note que l'on va mettre dans la liste des notes (affichage)
     * on utilise une methode virtuelle car lorsqu'on manipule les notes du tableau de note de NoteManager
     * on ne connait pas le type de la note
     * on avait donc besoin de gérer la génération du titre a afficher au niveau des methodes de note
     */
    virtual QString setNotesListNote();

    ///SAVE
    /**
     * @brief saveNote
     * @param stream
     * on utilise une methode virtuelle car lorsqu'on manipule les notes du tableau de note de NoteManager
     * on ne connait pas le type de la note
     * on save les notes differements au niveau de leur type
     * la methode doit donc être redefinie et est donc virtuelle pure
     */
    virtual void saveNote(QXmlStreamWriter &stream) const = 0;

    ///MEMENTO
    /**
     * @brief addMemento
     * @return une reference sur la note
     * ajoute la version de la note avant les modifications au tableau careTaker
     *
     */
    virtual Note& addMemento()=0;
    /**
     * @brief editNote
     * genère l'éditeur adéquat en fonction du type de la note
     * cette methode doit donc être redefini pour chaque type de note
     */
    virtual void editNote() =0;

};


/*********************************************************************/

/*********************************************************************
***                        Note Abstract Memento                    ***
**********************************************************************/
/**
 * @brief The MementoN class
 * classe abstraite de base dont vont hériter les autres memento
 */
class MementoN {
protected :
    friend class Note;

    int id ;
    QString title ;
    QDate dateC;
    QDate dateM;
    bool archive;

public :
    /**
     * @brief MementoN
     * @param i
     * @param t
     * @param d_c
     * @param d_lm
     * @param a
     * constructeur de la classe
     */
    MementoN(int i, const QString t, QDate d_c,
             QDate d_lm, bool a): id(i), title(t), dateC(d_c), dateM(d_lm), archive(a){}

};

/*********************************************************************
***                       Memento Article                           ***
**********************************************************************/

/*! \class MementoA
   * \brief Classe qui hérite de MementoN
   *
   * Elle regroupe les même attributs qu'un Article avec des methodes différentes
   *
   */


class MementoA : public MementoN {
private :
    friend class Article;
    QString text;

public:
    /**
     * @brief MementoA
     * @param i
     * @param t
     * @param d_c
     * @param d_lm
     * @param a
     * @param txt
     * constructeur de la classe
     */
    MementoA(int i, const QString t, QDate d_c, QDate d_lm, bool a, const QString txt): MementoN(i,t,d_c,d_lm,a), text(txt) {}


};




/*********************************************************************
 ***                        Article                                 **
 *********************************************************************/

/*! \class Article
   * \brief Classe qui hérite de Note
   *
   * Note avec un tableau des attributs en plus :
   * Un tableau (+taille max et taille actuelle) de MementoA pour sauvegarder ses versions précédentes
   * Du texte
   */

class Article : public Note {
private:
    QString text;
    MementoA** careTaker;

public :
    /**
     * @brief Article
     * constructeur sans argument
     */
    Article() : Note(), text(""), careTaker(new MementoA*[5]) {}
    /**
     * @brief Article
     * @param i
     * @param t
     * @param d_c
     * @param d_lm
     * @param a
     * @param txt
     * constructeur avec argument pour la reconstruction à partir du fichier xml
     */
    Article(int i, const QString t=(QString)"", QDate d_c=QDate::currentDate(),
            QDate d_lm=QDate::currentDate(), bool a=false, const QString txt=(QString)""):
        Note(i,t,d_c,d_lm,a), text(txt), careTaker(new MementoA*[5]){}

    /**
     * @brief clone
     * @return un pointeur sur article
     * permet de cloner un patron de base de la classe
     */
    virtual Article* clone();

    ///ACCESSEURS
    /**
     * @brief getText
     * @return le texte de l'article
     */
    const QString& getText() const {return text ;}
    /**
     * @brief getDateC
     * @return la date de creation
     */
    const QDate& getDateC() const {return dateC;}
    /**
     * @brief getType
     * @return le type
     */
    const QString getType() const {return "Article";}

    ///SET
    /**
     * @brief setText
     * @param t
     * permet de modifier le text
     */
    void setText(const QString& t) {text=t ;}

    ///DESCTRUCTEUR
    ~Article() {}

    /**
     * @brief saveNote
     * @param stream
     * permet de d'adopter la syntaxe adequat a l'artivle pour le save

     */
    void saveNote(QXmlStreamWriter &stream) const;

    ///MEMENTO
    /**
     * @brief createMemento
     * @return un pointeur sur une version antèrieur
     */
    MementoA* createMemento() {
        return new MementoA(getId(),getTitle(),getDateC(),getDateM(),GetArchive(),text) ;
    }
    /**
     * @brief addMemento
     * @return une ref sur l'article
     * permet d'ajouter le memento au tableau des versions précédentes
     */
    Article& addMemento();
    /**
     * @brief getPreviousMemento
     * @return un pointeur sur l'article
     * modifie la note avec l'état de la version précédente
     */
    Article *getPreviousMemento();

    /**
     * @brief editNote
     * voir Note
     */
    void editNote();


};

/********************************************************************/

enum state {Waiting,Ongoing,Done};

    ///METHODES PERMETTANT LE PASSSAGE D'UN TYPE QSTRING A UN TYPE STATE ET INVERSEMENT

/*! \enum state
 *  \brief
 *  Différents états que peut prendre une Tâche
 */

inline QString toString(state s){
    switch (s){
    case Waiting:   return "Waiting";
    case Ongoing:   return "Ongoing";
    case Done:      return "Done";
    default:      return "[Unknown status]";
    }
}
/*! \enum state
 *  \brief
 *  Différents états que peut prendre une Tâche
 */
inline state toState(const QString& s){
    if (s == "Waiting") return Waiting;
    if (s == "Ongoing") return Ongoing;
    if (s == "Done") return Done;
    else throw NotesException("ERROR");
}


/*********************************************************************
***                       Memento Task                           ***
**********************************************************************/
**********************************************************************/

/*! \class MementoT
   * \brief Classe qui hérite de MementoN
   *
   * Elle regroupe les même attributs qu'une Tache avec des methodes différentes
   *
   */
class MementoT : public MementoN {
private :
    friend class Task;
    QString action;
    unsigned int priority;
    QDate deadline;
    state status;

public :
    /**
     * @brief MementoT
     * @param i
     * @param t
     * @param d_c
     * @param d_lm
     * @param a
     * @param act
     * @param p
     * @param dl
     * @param s
     * constructeur
     */
    MementoT(int i, const QString t, QDate d_c, QDate d_lm, bool a, const QString act, unsigned int p, QDate dl, state s):
        MementoN(i,t,d_c,d_lm,a), action(act), priority(p), deadline(dl) ,status(s) {}

};



/********************************************************************
***                        Task                                   ***
*********************************************************************/
/*! \class Task
   * \brief Classe qui hérite de Note
   *
   * Note avec un tableau et des attributs en plus :
   * Un tableau (+taille max et taille actuelle) de MementoA pour sauvegarder ses versions précédentes
   * une action
   * une valeur de priorité
   * une date d'échéance
   * un etat (en cours, en attente, fait)
   * un tableau des états précédents
   */

class Task : public Note {
private:
    QString action;
    unsigned int priority;
    QDate deadline;
    state status;
    MementoT** careTaker;


public :
    ///CONSTRUCTEURS
    /**
     * @brief Task
     * @param i
     * @param t
     * @param d_c
     * @param d_lm
     * @param a
     * @param act
     * @param p
     * @param dl
     * @param s
     * constructeur avec argument
     */
    Task(int i, const QString t, QDate d_c, QDate d_lm, bool a, const QString act, unsigned int p=0,
         QDate dl=QDate(0000,00,00), state s=Waiting):
        Note(i,t,d_c,d_lm,a), action(act), priority(p), deadline(dl), status(s), careTaker(new MementoT*[5]) {}
    /**
     * @brief Task
     * constructeur sans argument
     */

    Task() : Note(), action(""), priority(0), deadline(QDate::currentDate()), status(Waiting),careTaker(new MementoT*[5]) {}

    /**
     * @brief clone
     * @return un pointeur sur Task
     * voir Note
     */
    virtual Task* clone();

    ///ACCESSEURS
    /**
     * @brief getAction
     * @return l'action
     */
    const QString& getAction() const  {return action ;}
    /**
     * @brief getPriority
     * @return la valeur de la priorité
     */
    const unsigned int& getPriority() const  {return priority ;}
    /**
     * @brief getDeadline
     * @return la date d'échéance
     */
    const QDate& getDeadline() const {return deadline ;}
    /**
     * @brief getState
     * @return l'état parmis les états possible
     */
    const state& getState() const {return status ;}
    /**
     * @brief getType
     * @return le type
     */
    const QString getType() const {return "Task";}

    ///SET
    /**
     * @brief setAction
     * @param newAction
     * permet de modifier l'action
     */
    void setAction(const QString& newAction) {action=newAction;}
    /**
     * @brief setPriority
     * @param p
     * permet de modifier la priorité
     */
    void setPriority (unsigned int p) {priority = p ;}
    /**
     * @brief setDeadline
     * @param newDl
     * permet de modifier l'échéance
     */
    void setDeadline (QDate newDl) {deadline=newDl ;}
    /**
     * @brief setState
     * @param s
     * modifier l'état a partir d'une chaine de caractère
     */
    void setState (const QString& s) {status = toState(s);}
    /**
     * @brief setState
     * @param s
     * modifier l'état a partir d'un état donné
     */
    void setState(state& s){status= s ;}

    /**
     * @brief saveNote
     * @param stream
     * voir Note
     */
    void saveNote(QXmlStreamWriter &stream) const;
    /**
     * @brief setNotesListNote
     * @return
     * voir Note
     */
    QString setNotesListNote();


    ///MEMENTO
    /**
     * @brief createMemento
     * @return un pointeur sur une version précédente
     * voir Article
     */
    MementoT* createMemento() {
        return new MementoT(getId(),getTitle(),getDateC(),getDateM(),GetArchive(),action,priority,deadline,status) ;
    }
    /**
     * @brief addMemento
     * @return
     * voir Article
     */
    Task& addMemento();
    /**
     * @brief getPreviousMemento
     * @return
     * voir Article
     */
    Task* getPreviousMemento();
    /**
     * @brief editNote
     * voir Article
     */
    void editNote();

    ///destructeur
    ~Task() {}
};


/*********************************************************************/


/*********************************************************************
***                       Memento Multimedia                        ***
**********************************************************************/
/*! \class MementoM
   * \brief Classe qui hérite de MementoN
   *
   * Elle regroupe les même attributs qu'un Article avec des methodes différentes
   * Elle permet permet d'instancier un objet d'une version précédentes :
   * d'image
   * de video
   * d'audio
   */

class MementoM : public MementoN {
protected :
    friend class Audio;
    friend class Image;
    friend class Video;
    friend class Multimedia;
    QString description;
    QString image;

public :
    ///CONSTRUCTEUR
    MementoM( int i, const QString t, QDate d_c, QDate d_lm, bool a, const QString& d, const QString& f) :
        MementoN(i,t,d_c,d_lm,a), description(d), image(f) {}

};




/*********************************************************************/


/*********************************************************************
 ***                        Multimedia                              ***
 **********************************************************************/


/*! \class Multimedia
   * \brief Classe qui hérite de Note
   *
   * Note avec un tableau et des attributs en plus :
   * Un tableau (+taille max et taille actuelle) de MementoM pour sauvegarder ses versions précédentes
   * une description
   * une image/video/audio (on a choisi de mettre un Qstring pour représenter le lien vers ce fichier)
   *
   * C'est une classe abstraite dont herite les : Image/Video/Audio
   */
class Multimedia : public Note {
protected:
    QString description;
    QString image;
    MementoM** careTaker;

public:

    /**
     * @brief Multimedia
     * @param i
     * @param t
     * @param d_c
     * @param d_lm
     * @param a
     * @param d
     * @param f
     * constructeur avec argument
     */
    Multimedia (int i, const QString t, QDate d_c, QDate d_lm, bool a, const QString& d, const QString& f) :
        Note(i,t,d_c,d_lm,a), description(d), image(f), careTaker(new MementoM*[5]){}
    
    /**
     * @brief Multimedia
     * constructeur sans argument
     */
    Multimedia() : Note(), description(""), image(""), careTaker(new MementoM*[5]) {}

    /**
     * @brief getDescription
     * @return la description
     */
    const QString& getDescription() const {return description;}
    /**
     * @brief getImage
     * @return le lien vers l'image
     */
    const QString& getImage() const {return image;}

    const QString  getType() const =0;

    /**
     * @brief setDescription
     * @param d
     * permet de modifier la description
     */
    void setDescription(const QString& d) { description=d;}
    /**
     * @brief setImage
     * @param i
     * permet de modifier le lien vers l'image
     */
    void setImage(const QString & i) { image = i;}


    /**
    * @brief clone
    * @return voir les classes précédentes
    */
    virtual Multimedia* clone()=0;

    
    ///Method save
    /**
     * @brief saveNote
     * @param stream
     * voir les classes précédente
     */
    void saveNote(QXmlStreamWriter &stream) const;

    ///MEMENTO
    /**
     * @brief createMemento
     * @return MementoM*
     */
    MementoM* createMemento() {
        return new MementoM(getId(),getTitle(),getDateC(),getDateM(),GetArchive(),description,image) ;
    }
    /**
     * @brief addMemento
     * @return Multimedia&
     */
    Multimedia& addMemento();
    /**
     * @brief getPreviousMemento
     * @return  Multimedia*
     */
    Multimedia* getPreviousMemento();

    /**
     * @brief editNote
     */
    void editNote() =0;

    ///DESTRUCTEUR
    ~Multimedia(){}
};

/*********************************************************************/



/*********************************************************************
 ***                        Image                                   ***
 **********************************************************************/

/*! \class Image
   * \brief Classe qui hérite Multimedia (qui elle meme hérite de Note)
   *
   * Seules les methodes sont modifiées
   */


class Image : public Multimedia{

public:

    /**
     * @brief Image
     * @param i
     * @param t
     * @param d_c
     * @param d_m
     * @param a
     * @param d
     * @param f
     * constructeurs avec arguments
     */
    Image(int i, const QString t, QDate d_c ,QDate d_m ,bool a, const QString& d, const QString& f):
        Multimedia(i,t,d_c,d_m,a,d,f) {}
    
    /**
     * @brief Image
     * constructeur sans argument
     */
    Image() : Multimedia() {}

    /**
     * @brief clone
     * @return Image *
     */
    virtual Image * clone ();

    ///DESTRUCTEUR
    ~Image() {}

    /**
     * @brief getType
     * @return le type
     */
    const QString getType() const {return "Image";}
    
    ///SAVE
    void saveNote(QXmlStreamWriter &stream) const;

    /**
     * @brief getPreviousMemento
     * @return Image*
     */
    Image* getPreviousMemento();

    /**
     * @brief editNote
     */
    void editNote();
};

/*********************************************************************/


/*********************************************************************
 ***                   Enregistrement Audio                        ***
 **********************************************************************/

/*! \class Audio
   * \brief Classe qui hérite Multimedia (qui elle meme hérite de Note)
   *
   * Seules les methodes sont modifiées
   */

class Audio : public Multimedia{

public:
    ///CONSTRUCTEUR
    Audio(int i, const QString t, QDate d_c ,QDate d_m ,bool a, const QString& d, const QString& f):
        Multimedia(i,t,d_c,d_m,a,d,f) {}
    
    Audio(): Multimedia() {}
    ///CLONE
    virtual Audio* clone ();

    ///DESTRUCTEUR
    ~Audio() {}

    ///ACESSEURS
    const QString  getType() const {return "Audio";}
    
    ///SAVE
    void saveNote(QXmlStreamWriter &stream) const;


    ///MEMENTO
    Audio* getPreviousMemento();
    /**
     * @brief editNote
     */
    void editNote();
};

/*********************************************************************/


/*********************************************************************
 ***                        video                                   ***
 **********************************************************************/
/*! \class Audio
   * \brief Classe qui hérite Multimedia (qui elle meme hérite de Note)
   *
   * Seules les methodes sont modifiées
   */
class Video : public Multimedia{

public:
    /**
     * @brief Video
     * @param i
     * @param t
     * @param d_c
     * @param d_m
     * @param a
     * @param d
     * @param f
     * constructeur avec argument
     */
    Video(int i, const QString t, QDate d_c ,QDate d_m ,bool a, const QString& d, const QString& f):
        Multimedia(i,t,d_c,d_m,a,d,f) {}

    /**
     * @brief Video
     * constructeur sans argument
     */
    Video() : Multimedia() {}

    ///CLONE
    virtual Video * clone ();
    ///DESTRUCTEUR
    ~Video() {}
    
    /**
     * @brief getType
     * @return le type
     */
    const QString  getType() const {return "Video";}

    ///SAVE
    void saveNote(QXmlStreamWriter &stream) const;

    /**
     * @brief getPreviousMemento
     * @return Video*
     */
    Video* getPreviousMemento();
    /**
     * @brief editNote
     */
    void editNote();
};


/*********************************************************************/

#endif

