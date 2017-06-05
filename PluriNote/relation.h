#ifndef relation_h
#define relation_h

#include "note.h"
#include "couple.h"

#endif


/*******************************************************************
 ***                        Base Relation                        ***
 *******************************************************************/

class BaseRelation{
protected:
    QString description;
    Couple** couples;
    unsigned int nbCouple, nbMaxCouple;
public:

    BaseRelation(const QString & d) : description(d), couples(nullptr), nbCouple(0), nbMaxCouple(0) {}
    BaseRelation() : description(""), couples(nullptr), nbCouple(0), nbMaxCouple(0) {}

    //Accesor
    const QString & getDescription () const {return description;}
    void addCouple(Note*, Note*);
    void removeCouple(const QString&,Note*,Note*);
    virtual ~BaseRelation() {}

};


/*******************************************************************
 ***                        Relation                             ***
 *******************************************************************/

class Relation : public BaseRelation {
    QString title;
    bool oriented;
public:
    Relation(const QString & d, const QString& t) : BaseRelation(d), title(t), oriented(false) {}
    const QString& getTitle() const {return title;}
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

    ~Reference() {
        for (unsigned int i=0; i<nbCouple; i++) delete couples[i];
        delete [] couples;
    }


};


