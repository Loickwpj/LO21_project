#ifndef relations_cpp
#define relations_cpp
#include <QMessageBox>
#include "relation.h"
#include <QDebug>
#endif


/**************************************************************
 ***                     Base Relation                      ***
 ***************************************************************/


void BaseRelation::chercherCoupleInRelation(Note*n){
    unsigned int j=0;
    for (unsigned int i=0; i<nbCouple; i++){
        if (couples[i]->getNote1() == n || couples[i]->getNote2() == n){
            removeCouple(couples[i]->getLabel(),couples[i]->getNote1(),couples[i]->getNote2());
            j++;
            i--;
        }
    }
    QString nbCoupleSuppr = QString::number(j);
    QMessageBox::information(0,"Suppression", nbCoupleSuppr+" couple(s) on été supprimé dans la relation "+getTitle());
}


Couple* BaseRelation::getCouple(unsigned int id1, unsigned int id2 ) const{
    for (unsigned int i=0; i<getNbCouple();i++){
        if (getCouple(i)->getNote1()->getId() == id1 && getCouple(i)->getNote2()->getId() == id2){
            return couples[i];
        }
    }
    throw NotesException("Error");
}

/**************************************************************
 ***                        Relation                        ***
 ***************************************************************/

/*void BaseRelation::addCouple(Note* n1, Note* n2){
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
}*/

void BaseRelation::addCouple(Couple* c){
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
    couples[nbCouple++]=c;
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
void BaseRelation::getNewCouple(){
    Couple* c= new Couple();
    CoupleEdit(c);
    //addCouple(c->getNote1(),c->getNote2());
    addCouple(c);
}

void BaseRelation::CoupleEdit(Couple* c){
    CoupleEditeur * ce = new CoupleEditeur(c);
    ce->show();
}


/**************************************************************
***                         Relation                        ***
***************************************************************/


void Reference::chercherReference(){
    for (int i=0; i<Note::idIterator; i++){
        for(NotesManager::iterator it=NotesManager::getInstance().begin(); it!=NotesManager::getInstance().end(); ++it){
        }

     }
}

















