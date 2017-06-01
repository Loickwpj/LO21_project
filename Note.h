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
private:
    string id ;
    string title ;
    Date dateCreation;
    Date dateLastModif;
    bool archive;
    
    //attributs statiques réunissant l'ensemble des ids de toutes les notes
    static string* ids;
    static unsigned int nbId, nbMaxId;
    
    
public:
    ///Constructor
    Note(const string i, const string t, Date d_c, Date d_lm): id(i), title(t), dateCreation(d_c), dateLastModif(d_lm), archive(false){addID(i);}

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
    void SetTitle(const string& newTitle) {title=newTitle ;}
    void SetDateCreation(Date& newDate) {dateCreation=newDate ;}
    void setDateLastCreation(Date& newDate) {dateLastModif=newDate;}
    void SetArchive() {archive=!archive ;}
    Note& setId(const string& i) {id = i; addID(i); return *this;}
    void addID(const string & id);
    
    //Get Ascendant/Descendant in all differents Relations
    void getRelAsc(const string& /*titre de la note à obtenir*/);
    void getRelDesc(const string&);
    
    virtual Note* clone()=0 ;
    virtual ~Note() {} // implement to delete in all relation

    /// Class Iterator
    class Iterator{
        friend class Note;
        string* currentI;
        int nbRemain;
        Iterator(string*a, int nb): currentA(a), nbRemain(nb){}
    public:
        bool isDone()const {return nbRemain == 0;}
        Article& current() const{ return *currentI;}
        void next(){
            if(isDone())
                throw NotesException("ERROR : fin de la collection");
            currentI++;
            nbRemain--;
        }
        
    };
    
    //Méthode static car on itère sur l'attribut static ids (ensemble des IDs de toutes les notes)
    static Iterator getIterator() const;

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
    
    ~Article() {}

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
Tache(const string i, const string t, Date d_c, Date d_lm, const string a, unsigned int p=0, Date dl=Date(1,1,1), state s=Waiting):
    Note(i,t,d_c,d_lm), action(a), priority(p), deadline(dl), status(s) {}

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

    ~Tache() {}
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




























