#ifndef note_h
#define note_h
#include <QString>
#include <QDate>


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
    QString id ;
    QString title ;
    QDate dateC;
    QDate dateM;
    bool archive;


public:
    ///Constructor
    Note(const QString i, const QString t):
        id(i), title(t), dateC(QDate::currentDate()), dateM(QDate::currentDate()), archive(false) {}
    virtual ~Note() {}

    ///Accessor
    const QString& getId() const {return id;}
    const QString& getTitle() const {return title;}
    const QDate& getDateC() const  {return dateC;}
    const QDate& getDateM() const  {return dateM;}
    bool GetArchive() const {return archive;}

    ///Method set
    void setTitle(const QString& newTitle) {title=newTitle ;}
    void setDateLastModification() {dateM=QDate::currentDate();}
    void setArchive() {archive=!archive ;}
    void setId(const QString& i) {id = i;}


};


/*********************************************************************/



/*********************************************************************
 ***                        Article                                 **
 *********************************************************************/


class Article : public Note {
private:
    QString text;

public :
    ///Constructor
    Article(const QString i, const QString t, const QString txt): Note(i,t), text(txt) {}
/*
    ///clone
    virtual Article* clone();
*/
    ///Accessor
    const QString& getText() const {return text ;}
    const QDate& getDateC() const {return dateC;}

    ///Modify attribute
    void setText(const QString& t) {text=t ;}


    ~Article() {}

};

/********************************************************************/



/********************************************************************
***                        Task                                   ***
*********************************************************************/


enum state {Waiting,Ongoing,Done};

inline QString toString(state s){
    switch (s){
        case Waiting:   return "En attente";
        case Ongoing:   return "En cours";
        case Done: return "Termine";
        default:      return "[Unknown status]";
    }
}

inline state toState(const QString& s){
    if (s == "Waiting") return Waiting;
    if (s == "Ongoing") return Ongoing;
    if (s == "Done") return Done;
    else throw NotesException("ERROR");
}

class Task : public Note {
private:
QString action;
unsigned int priority;
QDate deadline;
state status;

public :
///Constructor (how to put deadline optional)
Task(const QString i, const QString t, const QString a, unsigned int p=0, QDate dl=QDate(0000,00,00), state s=Waiting):
    Note(i,t), action(a), priority(p), deadline(dl), status(s) {}
/*
///clone
virtual Tache* clone();
*/

///Accessor
const QString& getAction() const  {return action ;}
const unsigned int& getPriority() const  {return priority ;}
const QDate& getDeadline() const {return deadline ;}
const state& getState() const {return status ;}

///Modify attribute
void setAction(const QString& newAction) {action=newAction;}
void setPriority (unsigned int p) {priority = p ;}
void setDeadline (QDate newDl) {deadline=newDl ;}
void setState (const QString& s) {status = toState(s);}

    ~Task() {}
};

/*********************************************************************/


/*********************************************************************
 ***                        Multimedia                              ***
 **********************************************************************/


class Multimedia : public Note {
private:
    QString description;
    QString image;
public:
    //Constructor
    Multimedia (const QString i, const QString t, const QString& d, const QString& f) : Note(i,t), description(d), image(f) {}

    //Accessor
    const QString& getDescription() const {return description;}
    const QString& getImage() {return image;}

    //setMethod
    void setDescription(const QString& d) { description=d;}
    void setImage(const QString & i) { image = i;}

/*
    //clone virtual pure
    virtual Multimedia* clone()=0;
*/

    ~Multimedia(){}
};

/*********************************************************************/



/*********************************************************************
 ***                        Image                                   ***
 **********************************************************************/

class Image : public Multimedia{
public:
    Image(const QString i, const QString t, const QString& d, const QString& f):
    Multimedia(i,t,d,f) {}
   // virtual Image * clone ();
    ~Image() {}
};

/*********************************************************************/


/*********************************************************************
 ***                   Enregistrement Audio                        ***
 **********************************************************************/

class Audio : public Multimedia{
public:
    Audio(const QString i, const QString t, const QString& d, const QString& f):
    Multimedia(i,t,d,f) {}
    //virtual Audio* clone ();
    ~Audio() {}
};

/*********************************************************************/


/*********************************************************************
 ***                        video                                   ***
 **********************************************************************/

class Video : public Multimedia{
public:
    Video(const QString i, const QString t, const QString& d, const QString& f):
    Multimedia(i,t,d,f) {}
    //virtual Video * clone ();
    ~Video() {}
};


/*********************************************************************/

#endif
