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
    ///MEMENTO AJOUT ATTRIBUT
    unsigned int nbMemento;
    unsigned int nbMax;


public:

    static int idIterator;

    ///On a 2 constructeurs :
    /// 1 sans argument pour les editeurs
    /// l'autre avec argument pour reconstruire les notes après chargement du fichier XML
    /// on a fait la même chose pour chaque classe fille
    Note(): id(), title(""), dateC(QDate::currentDate()), dateM(QDate::currentDate()), archive(false),nbMemento(0),nbMax(5) {}
    virtual ~Note() {}

    Note(int i, const QString t=(QString)"", QDate d_c=QDate::currentDate(),
         QDate d_lm=QDate::currentDate(), bool a=false): id(i), title(t), dateC(d_c), dateM(d_lm), archive(a), nbMemento(0),nbMax(5){}
    virtual Note* clone() =0;

    ///Accessor
    /// \brief
    /// recupere l'id
    unsigned int getId() const {return id;}
    /// \brief
    /// recupere le titre
    const QString& getTitle() const {return title;}
    /// \brief
    /// recupere la date de création
    const QDate& getDateC() const  {return dateC;}
    /// \brief
    /// recupere la date de derniere modification
    const QDate& getDateM() const  {return dateM;}
    /// \brief
    /// permet de savoir si une note est archivée ou non
    bool GetArchive() const {return archive;}
    /// \brief
    /// recupere le nombre de version précédente
    unsigned int getNbmemento() const {return nbMemento;}
    //static int getIdIterator() const {return idIterator;}
    virtual const QString  getType() const =0;

    ///Method set
    ///  \brief
    /// permet de modifier le titre
    virtual void setTitle(const QString& newTitle) {title=newTitle ;}
    ///  \brief
    /// permet de modifier la date modification
    virtual void setDateLastModification() {dateM=QDate::currentDate();}
    virtual void setDateLastModification(QDate& newDate) {dateM=newDate;}
    ///  \brief
    /// permet de rendre un note archivé ou non
    virtual void setArchive() {archive=!archive ;}
    virtual void setArchive(bool a) {archive=a ;}
    ///  \brief
    /// permet d'incrémenter la valeur de l'id
    virtual void setId() {id = idIterator++;}

    /*
    ///Method set
    virtual void setMementoTitle(const QString& newTitle) {title=newTitle ;}
    virtual void setMementoDateLastModification() {dateM=QDate::currentDate();}
    virtual void setMementoDateLastModification(QDate& newDate) {dateM=newDate;}
    virtual void setMementoArchive() {archive=!archive ;}
    virtual void setMementoArchive(bool a) {archive=a ;}
    virtual void setMementoId() {id = idIterator++;}
*/
    ///Method save
    /// \fn virtual void saveNote(QXmlStreamWriter &stream) const = 0
    ///  \brief
    /// Cette methode permet de sauvegarder la note
    /// methode virtuelle pur : indique qu'il FAUT la redéfinir dans chaque classe fille
    virtual void saveNote(QXmlStreamWriter &stream) const = 0;

    /// \fn virtual QString setNotesListNote();
    /// \brief
    /// method qui permet d'afficher les notes peut importe leur type dans la liste
    /// virtual suppose que la method va être redefinie
    virtual QString setNotesListNote();

    ///Memento
    /// \fn virtual Note& addMemento()=0;
    /// \brief
    /// method qui permet d'ajouter sauvegarder l'etat d'une note après une modification
    /// on appelle la methode après chaque void saveModifications()
    /// cette fontion est dans le fichier noteediteur.h
    /// cette methode est virtuelle pur : il FAUT la redefinir dans chaque classe fille
    virtual Note& addMemento()=0;

    /// \fn virtual void editNote() =0
    /// \brief
    /// permet d'editer grâce au NoteEditeur qui lui correspond
    /// c'est pour cela que la methode est virtuelle pur, on la redefini pour chaque classe fille
    virtual void editNote() =0;

};


/*********************************************************************/

/*********************************************************************
***                        Note Abstract Memento                    ***
**********************************************************************/
/*! \class MementoN
   * \brief Classe Abastraite dont hérite tous les autres memento
   *
   * Elle regroupe les même attributs qu'une note avec des methodes différentes
   * Les classes Memento permettent de fixer l'etat d'un type de note avant une modification
   * Chaque class Memento est friendclass de la classe dont elle a les mêmes attributs pour avoir accès à celle-ci.
   */


class MementoN {
protected :
    friend class Note;
    //    friend class Tache;
    //    friend class Article;

    int id ;
    QString title ;
    QDate dateC;
    QDate dateM;
    bool archive;

public :
    MementoN(int i, const QString t, QDate d_c,
             QDate d_lm, bool a): id(i), title(t), dateC(d_c), dateM(d_lm), archive(a){}
    //Note getState()
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
    ///Constructor
    //Article(const QString i, const QString t, const QString txt): Note(i,t), text(txt) {}

    ///MEMENTO MODIFICATION DES CONSTRUCTEURS
    Article() : Note(), text(""), careTaker(new MementoA*[5]) {}
    
    Article(int i, const QString t=(QString)"", QDate d_c=QDate::currentDate(),
            QDate d_lm=QDate::currentDate(), bool a=false, const QString txt=(QString)""):
        Note(i,t,d_c,d_lm,a), text(txt), careTaker(new MementoA*[5]){}


    ///clone
    virtual Article* clone();

    ///Accessor
    const QString& getText() const {return text ;}
    const QDate& getDateC() const {return dateC;}
    const QString getType() const {return "Article";}

    ///Modify attribute
    void setText(const QString& t) {text=t ;}



    ~Article() {}

    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;

    ///Memento
    MementoA* createMemento() {

        return new MementoA(getId(),getTitle(),getDateC(),getDateM(),GetArchive(),text) ;
    }
    Article& addMemento();
    /// \fn  Article* getPreviousMemento()
    /// \brief
    /// fonction permettant de set tout les attributs avec les attributs de la version précédentes
    /// \return Article* un_pointeur_sur_une_version_precedente
    Article *getPreviousMemento();

    void editNote();


};

/********************************************************************/

/*! \enum state
 *  \brief
 *  Différents états que peut prendre une Tâche
 */

enum state {Waiting,Ongoing,Done};


/*! \fn inline QString toString(state s)
 *  \brief
 *  Permet de convertir le type de l'enumeration state en type Qstring
 */
inline QString toString(state s){
    switch (s){
    case Waiting:   return "Waiting";
    case Ongoing:   return "Ongoing";
    case Done:      return "Done";
    default:      return "[Unknown status]";
    }
}
/*! \fn inline state toState(const QString& s)
 *  \brief
 *  Permet de convertir le type Qstring en type énuméré sate
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

    ///memento
    MementoT** careTaker;


public :
    ///Constructor (how to put deadline optional)


    ///MEMENTO MODIFICATIONS DES CONSTRUCTEURS
    Task(int i, const QString t, QDate d_c, QDate d_lm, bool a, const QString act, unsigned int p=0,
         QDate dl=QDate(0000,00,00), state s=Waiting):
        Note(i,t,d_c,d_lm,a), action(act), priority(p), deadline(dl), status(s), careTaker(new MementoT*[5]) {}
    
    Task() : Note(), action(""), priority(0), deadline(QDate::currentDate()), status(Waiting),careTaker(new MementoT*[5]) {}

    ///clone
    virtual Task* clone();

    ///Accessor
    const QString& getAction() const  {return action ;}
    const unsigned int& getPriority() const  {return priority ;}
    const QDate& getDeadline() const {return deadline ;}
    const state& getState() const {return status ;}
    const QString getType() const {return "Task";};

    ///Modify attribute
    void setAction(const QString& newAction) {action=newAction;}
    void setPriority (unsigned int p) {priority = p ;}
    void setDeadline (QDate newDl) {deadline=newDl ;}
    void setState (const QString& s) {status = toState(s);}

    ///MEMENTO SURCHARGE DE LA METHODE
    void setState(state& s){status= s ;}

    /// save
    void saveNote(QXmlStreamWriter &stream) const;

    QString setNotesListNote();


    ///Memento
    MementoT* createMemento() {
        return new MementoT(getId(),getTitle(),getDateC(),getDateM(),GetArchive(),action,priority,deadline,status) ;
    }
    Task& addMemento();

    ///MEMENTO
    /// \fn  Task* getPreviousMemento()
    /// \brief
    /// fonction permettant de set tout les attributs avec les attributs de la version précédentes
    /// \return Task* un_pointeur_sur_une_version_precedente
    Task* getPreviousMemento();
    
    void editNote();

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

    ///Memento
    MementoM** careTaker;

public:
    //Constructor

    ///MEMENTO MODIFICATION DES CONSTRUCTEURS
    Multimedia (int i, const QString t, QDate d_c, QDate d_lm, bool a, const QString& d, const QString& f) :
        Note(i,t,d_c,d_lm,a), description(d), image(f), careTaker(new MementoM*[5]){}
    
    Multimedia() : Note(), description(""), image(""), careTaker(new MementoM*[5]) {}
    //Accessor
    const QString& getDescription() const {return description;}
    const QString& getImage() const {return image;}
    const QString  getType() const =0;

    //setMethod
    void setDescription(const QString& d) { description=d;}
    void setImage(const QString & i) { image = i;}


    //clone virtual pure
    virtual Multimedia* clone()=0;

    
    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;

    ///Memento
    MementoM* createMemento() {
        return new MementoM(getId(),getTitle(),getDateC(),getDateM(),GetArchive(),description,image) ;
    }
    Multimedia& addMemento();
    Multimedia* getPreviousMemento();

    void editNote() =0;

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
    Image(int i, const QString t, QDate d_c ,QDate d_m ,bool a, const QString& d, const QString& f):
        Multimedia(i,t,d_c,d_m,a,d,f) {}
    
    Image() : Multimedia() {}
    virtual Image * clone ();
    ~Image() {}

    const QString getType() const {return "Image";}
    
    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;


    /// \fn  Image* getPreviousMemento()
    /// \brief
    /// fonction permettant de set tout les attributs avec les attributs de la version précédentes
    /// \return Image* un_pointeur_sur_une_version_precedente
    Image* getPreviousMemento();

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
    Audio(int i, const QString t, QDate d_c ,QDate d_m ,bool a, const QString& d, const QString& f):
        Multimedia(i,t,d_c,d_m,a,d,f) {}
    
    Audio(): Multimedia() {}
    virtual Audio* clone ();
    ~Audio() {}

    const QString  getType() const {return "Audio";}
    
    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;

    /// \fn  Audio* getPreviousMemento()
    /// \brief
    /// fonction permettant de set tout les attributs avec les attributs de la version précédentes
    /// \return Audio* un_pointeur_sur_une_version_precedente
    Audio* getPreviousMemento();

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
    
    Video(int i, const QString t, QDate d_c ,QDate d_m ,bool a, const QString& d, const QString& f):
        Multimedia(i,t,d_c,d_m,a,d,f) {}

    Video() : Multimedia() {}
    virtual Video * clone ();
    ~Video() {}
    
    const QString  getType() const {return "Video";}

    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;

    ///MEMENTO
    /// \fn  Video* getPreviousMemento()
    /// \brief
    /// fonction permettant de set tout les attributs avec les attributs de la version précédentes
    /// \return Video* un_pointeur_sur_une_version_precedente
    Video* getPreviousMemento();

    void editNote();
};


/*********************************************************************/

#endif

