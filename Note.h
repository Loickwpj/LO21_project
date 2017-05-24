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
***                        Note Abstract Class                      ***
**********************************************************************/

class Note {
private:
    string id ;
    string title ;
    Date dateCreation;
    Date dateLastModif;
    bool archive;

public:
    ///Constructor
    Note(const string i, const string t, Date d_c, Date d_lm): id(i), title(t), dateCreation(d_c), dateLastModif(d_lm){}

    ///Memento
    //Memento createMemento();
    //setMemento(Memento m);

    ///Accessor in Lecture (return by const ref)
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
    virtual Note* clone()=0 ;
    virtual ~Note(); // implement to delete in all relation
};

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

class Multimedia : public Note {

};
#endif // NOTES_H_INCLUDED

