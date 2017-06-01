#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED
#include<string>
#include "timing.h"
#include <ctime>

using namespace TIME;
using namespace std;

enum state {Waiting,Ongoing,Done};

/*********************************************************************/



/*********************************************************************
***                            Execption                           ***
**********************************************************************/

class NotesException{
   public:
    NotesException(const string& message):info(message) {}
    string getInfo() const {
        return info;
    }
   private:
    string info;
};


/*********************************************************************
***                       NOTE ABSTRACT                            ***
**********************************************************************/

class Note {
private:
    string id ;
    string title ;
    Date dateCreation ;
    Date dateLastModif ;
    bool archive ;

public:
    ///Constructor
    Note(const string i, const string t, Date d_c, Date d_lm, bool a=false): id(i), title(t), dateCreation(d_c), dateLastModif(d_lm), archive(a){}

    ///Memento
    //virtual MementoN* createMemento()=0;
     virtual Note& addMemento()=0 ;

    ///Accessor in Lecture (return by const ref)
    const string& getId() const {return id;}
    const string& getTitle() const {return title;}
    const Date& getDateCreation() const  {return dateCreation ;}
    const Date& getLastModif() const  {return dateLastModif ;}
    const bool GetArchive() const {return archive ;}

    ///Modify attribute
    void SetTitle(const string newTitle) {addMemento(); title=newTitle;}
    void SetDateCreation(Date& newDate) {addMemento(); dateCreation=newDate ;}
    void setDateLastModif(Date& newDate) {addMemento(); dateLastModif=newDate;}
    void SetArchive(bool a) {addMemento(); archive=a ;}
    void SetArchive() {addMemento(); archive=!archive ;}
//    virtual Note* clone()=0 ;
//    virtual ~Note(); // implement to delete in all relation
};


/*********************************************************************
***                        Note Abstract Memento                    ***
**********************************************************************/

class MementoN {
protected :
    friend class Note;
//    friend class Tache;
//    friend class Article;

    string id ;
    string title ;
    Date dateCreation;
    Date dateLastModif;
    bool archive;

public :
    MementoN(const string i, const string t, Date d_c, Date d_lm, bool a) : id(i), title(t), dateCreation(d_c), dateLastModif(d_lm), archive(a) {}
    //Note getState()
};

/*********************************************************************
***                       Memento Article                           ***
**********************************************************************/


class MementoA : public MementoN {
private :
friend class Article;
string text;

public:
MementoA(const string i, const string t, Date d_c, Date d_lm, bool a, const string txt): MementoN(i,t,d_c,d_lm,a), text(txt) {}


};




/*********************************************************************
 ***                        Article                                ***
 **********************************************************************/

class Article : public Note {
private:
    string text;
    MementoA** careTaker;
    unsigned int nbMemento;
    unsigned int nbMax;

public :
///Constructor
Article(const string i, const string t, Date d_c, Date d_lm, bool a, const string txt): Note(i,t,d_c,d_lm,a), text(txt), careTaker(new MementoA*[5]),nbMemento(0),nbMax(5) {}

//void setMemento(MementoA* mA) {SetTitle(mA->title); SetDateCreation(mA->dateCreation); setDateLastModif(mA->dateLastModif); SetArchive(mA->archive); setText(mA->text);}

///Memento
MementoA* createMemento() {return new MementoA(getId(),getTitle(),getDateCreation(),getLastModif(),GetArchive(),text) ;}
Article& addMemento();
Article& getPreviousMemento();

///clone
//virtual Article* clone() {}

///Accessor
const string& getText() const {return text ;}

///Modify attribute
void setText(const string newTxt) { addMemento(); text=newTxt ; /*SetDateLastModif(dateDuJour);*/}

~Article(){}
};


/*********************************************************************
***                       Memento Task                           ***
**********************************************************************/

class MementoT : public MementoN {
private :
friend class Tache;
string action;
unsigned int priority;
Date deadline;
state status;



public :

MementoT(const string i, const string t, Date d_c, Date d_lm, bool a, const string act, unsigned int p, Date dl, state s): MementoN(i,t,d_c,d_lm,a), action(act), priority(p), deadline(dl) ,status(s) {}

};






/*********************************************************************
***                              TACHE                             ***
**********************************************************************/


class Tache : public Note {
private:
string action;
unsigned int priority;
Date deadline;
state status;

///Memento

MementoT** careTaker;
unsigned int nbMemento;
unsigned int nbMax;

public :
///Constructor (how to put deadline optional)
Tache(const string i, const string t, Date d_c, Date d_lm,bool ar, const string a, unsigned int p/*=0*/, Date dl, state s=Waiting): Note(i,t,d_c,d_lm,ar), action(a), priority(p), deadline(dl), status(s), careTaker(new MementoT*[5]),nbMemento(0),nbMax(5) {}

///clone
//virtual Tache* clone(){}

///Accessor
const string& getAction() const  {return action ;}
const unsigned int& getPriority() const  {return priority ;}
const Date& getDeadline() const {return deadline ;}
const state& getStatus() const {return status ;}

///Modify attribute

void setAction(string& newAction) {addMemento(); action=newAction;}
void setPriority (unsigned int p) {addMemento(); priority = p ;}
void setDeadline (Date newDl) {addMemento(); deadline=newDl ;}
//void setSatus()

///Memento
MementoT* createMemento() {return new MementoT(getId(),getTitle(),getDateCreation(),getLastModif(),GetArchive(),action,priority,deadline,status) ;}
Tache& addMemento();
Tache& getPreviousMemento();

};




/*********************************************************************/


/*********************************************************************
***                       Memento Multimedia                        ***
**********************************************************************/

class MementoM : public MementoN {
private :
friend class Multimedia;
    string description;
    string image;



public :
MementoM(const string i, const string t, Date d_c, Date d_lm, bool a, const string& d, const string& f) : MementoN(i,t,d_c,d_lm,a), description(d), image(f) {}

};




/*********************************************************************
 ***                        Multimedia                              ***
 **********************************************************************/


class Multimedia : public Note {
private:
    string description;
    string image;

///Memento
MementoM** careTaker;
unsigned int nbMemento;
unsigned int nbMax;

public:
    //Constructor
    Multimedia (const string i, const string t, Date d_c, Date d_lm, const string& d, const string& f) : Note(i,t,d_c,d_lm), description(d), image(f), careTaker(new MementoM*[5]),nbMemento(0),nbMax(5)  {}

    //Accessor
    const string& getDescription() const {return description;}
    const string& getImage() const {return image;}

    //Modif
    void setDescription (const string newD) {addMemento() ;description=newD;}
    void setImage (const string newI) {addMemento() ;image=newI ;}
    //clone virtual pure
    virtual Multimedia* clone()=0;

    //Memento
    MementoM* createMemento() {return new MementoM(getId(),getTitle(),getDateCreation(),getLastModif(),GetArchive(),description,image) ;}
    Multimedia& addMemento();
    Multimedia& getPreviousMemento();

    ~Multimedia(){}
};

/*********************************************************************/



/*********************************************************************
 ***                        Image                                   ***
 **********************************************************************/

class Image : public Multimedia{
public:
    Image(const string i, const string t, Date d_c, Date d_lm, const string& d, const string& f):
    Multimedia(i,t,d_c,d_lm,d,f) {}
    virtual Image * clone ();
    ~Image() {}
};

/*********************************************************************/


/*********************************************************************
 ***                   Enregistrement Audio                        ***
 **********************************************************************/

class Audio : public Multimedia{
public:
    Audio(const string i, const string t, Date d_c, Date d_lm, const string& d, const string& f):
    Multimedia(i,t,d_c,d_lm,d,f) {}
    virtual Audio* clone ();
    ~Audio() {}
};

/*********************************************************************/


/*********************************************************************
 ***                        video                                   ***
 **********************************************************************/

class Video : public Multimedia{
public:
    Video(const string i, const string t, Date d_c, Date d_lm, const string& d, const string& f):
    Multimedia(i,t,d_c,d_lm,d,f) {}
    virtual Video * clone ();
    ~Video() {}
};


/*********************************************************************/


/********************************************************************
 ***                        Couple                                ***
 ********************************************************************/


class Couple {
private:
    string label;
    Note* note1;
    Note* note2;
public:
    Couple(const string& l,Note* n1, Note* n2) :label(l), note1(n1), note2(n2) {}
    Note* getNote1() const  {return note1;}
    Note* getNote2() const {return note2;}
    const string& getLabel() const {return label;}
    void setLabel(const string & l) {label =l;}

};

/*********************************************************************/


/*******************************************************************
 ***                        Relation                             ***
 *******************************************************************/

class Relation{
private:
    string title, description;
    Couple** couples;
    unsigned int nbCouple, nbMaxCouple;
    bool oriented;
public:
    Relation(const string & t, const string& d) : title(t), description(d), couples(nullptr), nbCouple(0), nbMaxCouple(0), oriented(false) {}
    const string& getTitle() const {return title;}
    const string& getDescription() const {return description;}
    void addCouple(Note* n1, Note* n2); //add a couple without label
    void removeCouple(const string&,Note* n1, Note* n2); //looks for a couple with this label & notes
    void setOriented(){oriented= !oriented;};
    ~Relation() {for (unsigned int i=0; i<nbCouple;i++) delete couples[i]; delete [] couples;}
};
#endif // NOTES_H_INCLUDED

