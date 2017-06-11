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

    /// MEMENTO MODIFICATION Constructor
    Note(): id(), title(""), dateC(QDate::currentDate()), dateM(QDate::currentDate()), archive(false),nbMemento(0),nbMax(5) {}
    virtual ~Note() {}

    Note(int i, const QString t=(QString)"", QDate d_c=QDate::currentDate(),
         QDate d_lm=QDate::currentDate(), bool a=false): id(i), title(t), dateC(d_c), dateM(d_lm), archive(a), nbMemento(0),nbMax(5){}
    virtual Note* clone() =0;

    ///Accessor
    unsigned int getId() const {return id;}
    const QString& getTitle() const {return title;}
    const QDate& getDateC() const  {return dateC;}
    const QDate& getDateM() const  {return dateM;}
    bool GetArchive() const {return archive;}
    unsigned int getNbmemento() const {return nbMemento;}
    //static int getIdIterator() const {return idIterator;}
    virtual const QString  getType() const =0;

    ///Method set
    virtual void setTitle(const QString& newTitle) {title=newTitle ;}
    virtual void setDateLastModification() {dateM=QDate::currentDate();}
    virtual void setDateLastModification(QDate& newDate) {dateM=newDate;}
    virtual void setArchive() {archive=!archive ;}
    virtual void setArchive(bool a) {archive=a ;}
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
    virtual void saveNote(QXmlStreamWriter &stream) const = 0;

    ///Method setNotesList
    virtual QString setNotesListNote();

    ///Memento
    virtual Note& addMemento()=0;

    virtual void editNote() =0;

};


/*********************************************************************/

/*********************************************************************
***                        Note Abstract Memento                    ***
**********************************************************************/

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
    Article *getPreviousMemento();

    void editNote();


};

/********************************************************************/

enum state {Waiting,Ongoing,Done};

inline QString toString(state s){
    switch (s){
    case Waiting:   return "Waiting";
    case Ongoing:   return "Ongoing";
    case Done:      return "Done";
    default:      return "[Unknown status]";
    }
}

inline state toState(const QString& s){
    if (s == "Waiting") return Waiting;
    if (s == "Ongoing") return Ongoing;
    if (s == "Done") return Done;
    else throw NotesException("ERROR");
}


/*********************************************************************
***                       Memento Task                           ***
**********************************************************************/

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
    Task* getPreviousMemento();
    
    void editNote();

    ~Task() {}
};


/*********************************************************************/


/*********************************************************************
***                       Memento Multimedia                        ***
**********************************************************************/

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


    ///MEMENTO
    Image* getPreviousMemento();

    void editNote();
};

/*********************************************************************/


/*********************************************************************
 ***                   Enregistrement Audio                        ***
 **********************************************************************/

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


    ///MEMENTO
    Audio* getPreviousMemento();

    void editNote();
};

/*********************************************************************/


/*********************************************************************
 ***                        video                                   ***
 **********************************************************************/

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
    Video* getPreviousMemento();

    void editNote();
};


/*********************************************************************/

#endif

