#ifndef relations_hpp
#define relations_hpp

#include "Note.hpp"

#endif


/*******************************************************************
 ***                        Base Relation                        ***
 *******************************************************************/

class BaseRelation{
protected:
    string description;
    Couple** couples;
    unsigned int nbCouple, nbMaxCouple;
public:
    
    BaseRelation(const std::string & d) : description(d), couples(nullptr), nbCouple(0), nbMaxCouple(0) {}
    BaseRelation() : description(""), couples(nullptr), nbCouple(0), nbMaxCouple(0) {}
    
    //Accesor
    const string & getDescription () const {return description;}
    addCouple(Note*, Note*);
    removeCouple(Note*,Note*);
    ~Relation() =0;
    
};


/*******************************************************************
 ***                        Relation                             ***
 *******************************************************************/

class Relation public BaseRelation {
    std::string title;
    bool oriented;
public:
    Relation(const string & d, const string& t) : BaseRelation(d), title(t), oriented(false) {}
    const string& getTitle() const {return title;}
    void setOriented(){oriented= !oriented;};
    ~Relation() {for (unsigned int i=0; i<nbCouple;i++) delete couples[i]; delete [] couples;}
};


/*******************************************************************
 ***                        Decorateur                           ***
 *******************************************************************/

class Decorateur : public BaseRelation {
    BaseRelation& base;
public:
    Decorateur( const std::string& d, BaseRelation& b) : BaseRelation(d), base(b) {}
    ~Decorateur ()=0;
};

/*******************************************************************
 ***                        Référence                            ***
 *******************************************************************/

class Reference : public Decorateur {

    ~Reference() {
        for (unsigned int i=0; i<nbCouple; i++) delete couples[i];
        delete [] couples;
    }
    
        
};




























