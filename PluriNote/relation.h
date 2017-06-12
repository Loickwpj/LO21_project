#ifndef relation_h
#define relation_h
//#include "couple.h"
//#include "manager.h"
#include "coupleediteur.h"
#include <QFile>




/*******************************************************************
 ***                        Base Relation                        ***
 *******************************************************************/
class Couple;
class Note;

class BaseRelation{
protected:
    QString title;
    QString description;
    Couple** couples;
    unsigned int nbCouple, nbMaxCouple;
public:

    BaseRelation(const QString & d, const QString & t) : title(t), description(d), couples(nullptr), nbCouple(0), nbMaxCouple(0) {}
    BaseRelation() :title(""), description(""), couples(nullptr), nbCouple(0), nbMaxCouple(0) {}

    //Accesor
    const QString & getDescription () const {return description;}
    unsigned int getNbCouple() const {return nbCouple;}
    unsigned int getNbMaxCouple() const {return nbMaxCouple;}
    //void addCouple(Note*, Note*);
    void addCouple(Couple*);
    void removeCouple(const QString&,Note*,Note*);
    const QString& getTitle() const {return title;}
    Couple* getCouple(int i) const {return couples[i];}
    Couple* getCouple(unsigned int id1, unsigned int id2 ) const;

    void setTitle(const QString & t) {title=t;}
    void setDescription(const QString & d) {description=d;}

    //Methods
    void chercherCoupleInRelation(Note*);
    void getNewCouple();
    void CoupleEdit(Couple*);

    virtual ~BaseRelation() {}

};


/*******************************************************************
 ***                        Relation                             ***
 *******************************************************************/

class Relation : public BaseRelation {
    bool oriented;
public:
    Relation(const QString & d, const QString& t) : BaseRelation(t,d), oriented(true) {}
    ///rajout d'un constructeur
    Relation(const QString & d, const QString& t, bool o) : BaseRelation(t,d), oriented(o) {}
    bool getOriented() const {return oriented ;}
    void setOriented(){oriented= !oriented;}
    ~Relation() {/*for (unsigned int i=0; i<nbCouple;i++) delete couples[i]; delete [] couples;*/}


};


/*******************************************************************
 ***                        Decorateur                           ***
 *******************************************************************/
/*
class Decorateur : public BaseRelation {
    BaseRelation& base;
public:
    Decorateur( const QString& d, BaseRelation& b) : BaseRelation(d), base(b) {}
    ~Decorateur()=0;
};
*/


/*******************************************************************
 ***                           Référence                         ***
 *******************************************************************/


class Reference : public BaseRelation {

private:

    static Reference* instance;

    Reference() : BaseRelation("Ensemble des notes référérençant d'autres notes via la notation \{id}","Référence") {}
    ~Reference() {
        /*
         * for (unsigned int i=0; i<nbCouple; i++) delete couples[i];
        delete [] couples;*/
    }



public:
    static Reference* getInstance();
    static void libererInstance();
    void chercherReference();
    void addCoupleReference(Note&,int);
    //void saveRef();
    //void loadRef(QString f);
    //void loadCouple(QXmlStreamReader& xml);


    bool checkIfInReference(Note*);


    /// Class iterator
    class iterator{
        friend class Reference;
        Couple** currentN;

        iterator(Couple**n): currentN(n){}

    public:
        bool operator!=(iterator it) const {return currentN != it.currentN;}
        Couple& value() const {return **currentN;}
        iterator& operator++() {currentN++; return *this;}

    };

    iterator begin() const{ return iterator(couples); }
    iterator end() const{return iterator(couples + nbCouple);}

};


#endif
