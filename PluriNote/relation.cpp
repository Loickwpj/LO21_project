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
    qDebug()<<"on y est";
    for (unsigned int i=0; i<nbCouple; i++){
        if (couples[i]->getNote1() == n || couples[i]->getNote2() == n){

            removeCouple(couples[i]->getLabel(),couples[i]->getNote1(),couples[i]->getNote2());
           // j++;

        }
    }
    QString nbCoupleSuppr = QString::number(j);
    if (nbCoupleSuppr != 0)
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
/*
    qDebug()<<RelationsManager::getInstance().getRelation(1).getNbCouple();
    qDebug()<<RelationsManager::getInstance().getRelation(1).getNbMaxCouple();
*/
    couples[nbCouple++] = c;

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
/*
    qDebug()<<RelationsManager::getInstance().getRelation(1).getNbCouple();
    qDebug()<<RelationsManager::getInstance().getRelation(1).getNbMaxCouple();
*/
    addCouple(c);

}

void BaseRelation::CoupleEdit(Couple* c){
    CoupleEditeur * ce = new CoupleEditeur(c);
    ce->show();
}


/**************************************************************
***                         Relation                        ***
***************************************************************/

Reference* Reference::instance = 0;

Reference* Reference::getInstance(){
    if(!instance) instance = new Reference();
    return instance;
}

 void Reference::libererInstance(){
     if (instance) delete instance;
     instance=nullptr;
 }


void Reference::chercherReference(){
    for (int i=0; i<Note::idIterator; i++){
        for(NotesManager::iterator it=NotesManager::getInstance().begin(); it!=NotesManager::getInstance().end(); ++it){
            if (it.value()->getTitle().contains("\{"+QString::number(i)+"}")) Reference::addCoupleReference(*it.value(),i);
        }

     }
}


void Reference::addCoupleReference(Note& note1, int id2){
    bool existed = false;
    Note* note2 = NotesManager::getInstance().getNote(id2);
    for (iterator it=begin(); it!=end();++it){
        if (it.value().getNote1() == &note1 && it.value().getNote2() == note2) existed = true;
    }
    if (existed==false) {
        Couple* couple = new Couple("",&note1,note2);
        Reference::getInstance()->addCouple(couple);
    }
}

bool Reference::checkIfInReference(Note*n){
    for (iterator it = begin(); it != end() ; ++it){
        if (it.value().getNote2() == n ) return true;
    }
    return false;
}







