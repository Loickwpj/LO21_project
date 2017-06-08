#ifndef note_h
#define note_h
#include <QString>
#include <QDate>
#include <QXmlStreamWriter>


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


public:

    static int idIterator;

    ///Constructor
    Note(): id(), title(""), dateC(QDate::currentDate()), dateM(QDate::currentDate()), archive(false) {}
    virtual ~Note() {}

    Note(int i, const QString t=(QString)"", QDate d_c=QDate::currentDate(),
         QDate d_lm=QDate::currentDate(), bool a=false): id(i), title(t), dateC(d_c), dateM(d_lm), archive(a){}
    virtual Note* clone() =0;

    ///Accessor
    unsigned int getId() const {return id;}
    const QString& getTitle() const {return title;}
    const QDate& getDateC() const  {return dateC;}
    const QDate& getDateM() const  {return dateM;}
    bool GetArchive() const {return archive;}
    //static int getIdIterator() const {return idIterator;}

    ///Method set
    void setTitle(const QString& newTitle) {title=newTitle ;}
    void setDateLastModification() {dateM=QDate::currentDate();}
    void setArchive() {archive=!archive ;}
    void setId() {id = idIterator++;}

    ///Method save
    virtual void saveNote(QXmlStreamWriter &stream) const = 0;



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
    //Article(const QString i, const QString t, const QString txt): Note(i,t), text(txt) {}
    Article() : Note(), text("") {}
    
    Article(int i, const QString t=(QString)"", QDate d_c=QDate::currentDate(),
            QDate d_lm=QDate::currentDate(), bool a=false, const QString txt=(QString)""):
        Note(i,t,d_c,d_lm,a), text(txt)/*, careTaker(new MementoA*[5]),nbMemento(0),nbMax(5)*/ {}


    ///clone
    virtual Article* clone();

    ///Accessor
    const QString& getText() const {return text ;}
    const QDate& getDateC() const {return dateC;}

    ///Modify attribute
    void setText(const QString& t) {text=t ;}


    ~Article() {}

    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;


};

/********************************************************************/



/********************************************************************
***                        Task                                   ***
*********************************************************************/


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

class Task : public Note {
private:
    QString action;
    unsigned int priority;
    QDate deadline;
    state status;

public :
    ///Constructor (how to put deadline optional)
    Task(int i, const QString t, QDate d_c, QDate d_lm, bool a, const QString act, unsigned int p=0, QDate dl=QDate(0000,00,00), state s=Waiting):
        Note(i,t,d_c,d_lm,a), action(act), priority(p), deadline(dl), status(s) {}
    
    Task() : Note(), action(""), priority(0), deadline(QDate::currentDate()), status(Waiting) {}

    ///clone
    virtual Task* clone();

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

    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;
    
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
    Multimedia (int i, const QString t, QDate d_c, QDate d_lm, bool a, const QString& d, const QString& f) :
        Note(i,t,d_c,d_lm,a), description(d), image(f) {}
    
    Multimedia() : Note(), description(""), image("") {}
    //Accessor
    const QString& getDescription() const {return description;}
    const QString& getImage() const {return image;}

    //setMethod
    void setDescription(const QString& d) { description=d;}
    void setImage(const QString & i) { image = i;}


    //clone virtual pure
    virtual Multimedia* clone()=0;

    
    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;

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
    
    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;
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

    
    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;

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
    
    
    ///Method save
    void saveNote(QXmlStreamWriter &stream) const;
};


/*********************************************************************/

#endif

