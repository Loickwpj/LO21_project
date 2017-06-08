#ifndef relation_h
#define relation_h
//#include "couple.h"
//#include "manager.h"
#include "coupleediteur.h"




/*******************************************************************
 ***                        Base Relation                        ***
 *******************************************************************/
class Couple;

class BaseRelation{
protected:
    QString title;
    QString description;
    Couple** couples;
    unsigned int nbCouple, nbMaxCouple;
public:

    BaseRelation(const QString & d, const QString & t) : title(t), description(d), couples(nullptr), nbCouple(0), nbMaxCouple(0) {;}
    BaseRelation() :title(""), description(""), couples(nullptr), nbCouple(0), nbMaxCouple(0) {}

    //Accesor
    const QString & getDescription () const {return description;}
    unsigned int getNbCouple() const {return nbCouple;}
    //void addCouple(Note*, Note*);
    void addCouple(Couple*);
    void removeCouple(const QString&,Note*,Note*);
    const QString& getTitle() const {return title;}
    Couple* getCouple(int i) const {return couples[i];}
    Couple* getCouple(unsigned int id1, unsigned int id2 ) const;


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
    void setOriented(){oriented= !oriented;};
    ~Relation() {for (unsigned int i=0; i<nbCouple;i++) delete couples[i]; delete [] couples;}


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
        for (unsigned int i=0; i<nbCouple; i++) delete couples[i];
        delete [] couples;
    }



public:
    static Reference* getInstance();
    static void libererInstance();
    void chercherReference();

};


#endif
