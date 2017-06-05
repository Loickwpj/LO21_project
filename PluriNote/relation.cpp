#ifndef relations_cpp
#define relations_cpp

#include "relation.h"

#endif

/**************************************************************
 ***                        Relation                        ***
 ***************************************************************/

void BaseRelation::addCouple(Note* n1, Note* n2){
    if (nbCouple == nbMaxCouple ){
        Couple** newCouples = new Couple* [nbMaxCouple+5];
        for (unsigned int i=0; i<nbCouple; i++){
            newCouples[i]= new Couple (*couples[i]);
        }
        nbMaxCouple+=5;
        Couple** oldcouples=couples;
        couples=newCouples;
        delete [] oldcouples;
    }
    couples[nbCouple++]= new Couple("",n1,n2);
}


void BaseRelation::removeCouple(const QString & label,Note* n1, Note* n2){
    unsigned int i=0;
    while(i<nbCouple && !(couples[i]->getLabel() == label && couples[i]->getNote1() == n1  && couples[i]->getNote2() == n2)){
        i++;
    }
    if (i == nbCouple) throw NotesException("Couple inexistant...");

    delete couples [i];
    if(i != nbCouple) couples[i]=couples[nbCouple-1];
    nbCouple--;
}

