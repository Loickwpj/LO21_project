#ifndef NOTES_H_INCLUDED
#define NOTES_H_INCLUDED
#include<string>
#include "timing.h"
#include <ctime>

using namespace TIME;
using namespace std;

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

/*********************************************************************/



/*********************************************************************
***                        Note Abstract Class                     ***
**********************************************************************/

class Note {
    friend class NotesManager;
private:
    string id ;
    string title ;
    Date dateCreation;
    Date dateLastModif;
    bool archive;
    
    ///Constructor privé (Les notes sont construites via un objet NotesManager )
    Note(const string i, const string t, Date d_c, Date d_lm): id(i), title(t), dateCreation(d_c), dateLastModif(d_lm){}

public:


    ///Memento
        //Memento createMemento();
        //setMemento(Memento m);

    ///Accessor in Reading (return by const ref)
    const string& getId() const {return id;}
    const string& getTitle() const {return title;}
    const Date& getDateCreation() const  {return dateCreation ;}
    const Date& getLastModif() const  {return dateLastModif ;}
    const bool GetArchive() const {return archive ;}

    ///Modify attribute
    void SetTitle(string& newTitle) {title=newTitle ;}
    void SetDateCreation(Date& newDate) {dateCreation=newDate ;}
    void setDateLastCreation(Date& newDate) {dateLastModif=newDate;}
    void SetArchive() {archive=!archive ;}
    
    //Get Ascendant/Descendant in all differents Relations
    void getRelAsc(const string& /*titre de la note à obtenir*/);
    void getRelDesc(const string&);
    
    virtual Note* clone()=0 ;
    virtual ~Note(); // implement to delete in all relation
};

/*********************************************************************/



/*********************************************************************
 ***                        Article                                 **
 *********************************************************************/


class Article : public Note {
private:
    string text;

public :
    ///Constructor
    Article(const string i, const string t, Date d_c, Date d_lm, const string txt): Note(i,t,d_c,d_lm), text(txt) {}
    
    ///clone
    virtual Article* clone();

    ///Accessor
    const string& getText() const {return text ;}

    ///Modify attribute
    void setText(string& newTxt) {text=newTxt ;}

};

/********************************************************************/



/********************************************************************
***                        Task                                   ***
*********************************************************************/


enum state {Waiting,Ongoing,Done};

class Tache : public Note {
private:
string action;
unsigned int priority;
Date deadline;
state status;

public :
///Constructor (how to put deadline optional)
Tache(const string i, const string t, Date d_c, Date d_lm, const string txt, const string a, unsigned int p=0, Date dl, state s=Waiting): Note(i,t,d_c,d_lm), action(a), priority(p), deadline(dl), status(s) {}

///clone
virtual Tache* clone();

///Accessor
const string& getAction() const  {return action ;}
const unsigned int& getPriority() const  {return priority ;}
const Date& getDeadline() const {return deadline ;}
const state& getStatus() const {return status ;}

///Modify attribute

void setAction(string& newAction) {action=newAction;}
void setPriority (unsigned int p) {priority = p ;}
void setDeadline (Date newDl) {deadline=newDl ;}
//void setSatus()

};

/*********************************************************************/



/*********************************************************************
 ***                        Multimedia                              ***
 **********************************************************************/


class Multimedia : public Note {
private:
    string description;
    string image;
public:
    //Constructor
    Multimedia (const string i, const string t, Date d_c, Date d_lm, const string& d, const string& f) : Note(i,t,d_c,d_lm), description(d), image(f) {}
    
    //Accessor
    const string& getDescription() const {return description;}
    const string& getImage() {return image;}
    
    //clone virtual pure
    virtual Multimedia* clone()=0;

};

/*********************************************************************/



/*********************************************************************
 ***                        Image                                   ***
 **********************************************************************/

class Image : public Multimedia{
public:
    virtual Image * clone ();
};

/*********************************************************************/


/*********************************************************************
 ***                   Enregistrement Audio                        ***
 **********************************************************************/

class Audio : public Multimedia{
public:
    virtual Audio* clone ();
};

/*********************************************************************/


/*********************************************************************
 ***                        video                                   ***
 **********************************************************************/

class Video : public Multimedia{
public:
    virtual Video * clone ();
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
    Note& getNote1() const {return note1;}
    Note& getNote2() const {return note2;}
    const string& getLavel() const {return label;}
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
    Relation(const string & t, cont string& d) : title(t), description(d), couples(nullptr), nbCouple(0), nbMaxCouple(0), oriented(false) {}
    const string& getTitle() const {return title;}
    const string& getDescription() const {return description;}
    void addCouple(Note* n1, Note* n2); //add a couple without label
    void removeCouple(const string&,Note* n1, Note* n2); //looks for a couple with this label & notes
    void setOriented(){oriented= !oriented;};
    ~Relation();
    
};


#endif // NOTES_H_INCLUDED




























