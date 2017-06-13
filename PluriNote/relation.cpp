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
    //unsigned int j=0;

    /*for (unsigned int i=0; i<nbCouple; i++){
        if (couples[i]->getNote1() == n || couples[i]->getNote2() == n){

            removeCouple(couples[i]->getLabel(),couples[i]->getNote1(),couples[i]->getNote2());
           // j++;

        }*/
    for (BaseRelation::iterator it = begin() ; it != end() ; ++it){
        if (it.value().getNote1() == n || it.value().getNote2() == n){
            removeCouple(it.value().getLabel(),it.value().getNote1(),it.value().getNote2());
        }
    }
}


Couple* BaseRelation::getCouple(unsigned int id1, unsigned int id2 ) const{
    /*for (unsigned int i=0; i<getNbCouple();i++){
        if (getCouple(i)->getNote1()->getId() == id1 && getCouple(i)->getNote2()->getId() == id2){
            return couples[i];
        }
    }*/
    for (BaseRelation::iterator it = begin() ; it != end() ; ++it){
        if (it.value().getNote1()->getId() == id1 && it.value().getNote2()->getId() == id2){
            return &it.value();
        }
    }
    throw NotesException("Error");
}

/**************************************************************
 ***                        Relation                        ***
 ***************************************************************/


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

    if (couples){
        for (unsigned int i=0; i<nbCouple;i++) delete couples[i];
        delete [] couples;
        couples = nullptr;
        nbCouple=0;
        nbMaxCouple=0;
    }

    for (int i=0; i<Note::idIterator; i++){
        for(NotesManager::iterator it=NotesManager::getInstance().begin(); it!=NotesManager::getInstance().end(); ++it){
            if (it.value()->getTitle().contains("\{"+QString::number(i)+"}")) Reference::addCoupleReference(*it.value(),i);

            if(it.value()->getType() == "Article"){
                Article* a = dynamic_cast<Article*>(it.value());
                if (a->getText().contains("\{"+QString::number(i)+"}")) Reference::addCoupleReference(*it.value(),i);
            }

            if(it.value()->getType() == "Task"){
                Task* t = dynamic_cast<Task*>(it.value());
                if (t->getAction().contains("\{"+QString::number(i)+"}")) Reference::addCoupleReference(*it.value(),i);
            }

            if(it.value()->getType() == "Audio"){
                Audio* a = dynamic_cast<Audio*>(it.value());
                if (a->getDescription().contains("\{"+QString::number(i)+"}")) Reference::addCoupleReference(*it.value(),i);
            }

            if(it.value()->getType() == "Video"){
                Video* v = dynamic_cast<Video*>(it.value());
                if (v->getDescription().contains("\{"+QString::number(i)+"}")) Reference::addCoupleReference(*it.value(),i);
            }

            if(it.value()->getType() == "Image"){
                Image* im = dynamic_cast<Image*>(it.value());
                if (im->getDescription().contains("\{"+QString::number(i)+"}")) Reference::addCoupleReference(*it.value(),i);
            }

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

void Reference::chercherCouple(Note*n){
    chercherCoupleInRelation(n);
}


/*
void Reference::saveRef() {

    QFile newfile("reference.xml");
    qDebug()<<"on est apres le newfile";
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"on throw l'exeption";
        throw NotesException("erreur sauvegarde notes : ouverture fichier xml");}
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("fichier_reference");
    stream.writeStartElement("reference");
    stream.writeTextElement("titleReference",getTitle());
    stream.writeTextElement("descriptionReference", getDescription());
    stream.writeStartElement("couples");
    for(unsigned int j=0;getNbCouple();j++)
    {
        qDebug()<<"on est dans la boucle qui save les couples";
        getInstance()->getCouple(j)->saveCouple(stream);
    }
    stream.writeEndElement();
    stream.writeEndElement();

    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}


void Reference::loadRef(QString f){
    QFile fin(f);
    qDebug()<<"on arrive la";
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
    }

    QXmlStreamReader xml(&fin);
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();

        if(token == QXmlStreamReader::StartDocument) continue;

        if(token == QXmlStreamReader::StartElement) {
            // If it's named fichier_relation, we'll go to the next.
            if(xml.name() == "fichier_reference") continue;

            if(xml.name() == "reference") {
                qDebug()<<"on arrive ici";
                Reference::getInstance();
            }
            if(xml.name() == "couples") continue;
            if(xml.name()=="couple")
            {
                loadCouple(xml);
            }

        }

    }

    // Error handling.
    if(xml.hasError()) {
        qDebug()<<"c la que ça plante";
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}


void Reference::loadCouple(QXmlStreamReader& xml){
    QString id1;
    QString id2;
    QString label;

    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    //We're going to loop over the things because the order might change.
    //We'll continue the loop until we hit an EndElement named article.
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couple")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            // We've found date label
            if(xml.name() == "label") {
                xml.readNext();
                label=xml.text().toString();
                qDebug()<<"label"<<label<<"\n";
            }

            // We've found id1
            if(xml.name() == "id1") {
                xml.readNext(); id1=xml.text().toString();
                qDebug()<<"id1"<<id1<<"\n";
            }

            // We've found id2
            if(xml.name() == "id2") {
                xml.readNext(); id2=xml.text().toString();
                qDebug()<<"id2"<<id2<<"\n";
            }


        }
        // ...and next...
        xml.readNext();
    }
    Note* n1=NotesManager::getInstance().getNote(id1.toInt());
    //qDebug()<<"getNote(x) avec x1 = "<< id1.toInt();
    //qDebug()<<"getNote(x) avec x2 = "<< id2.toInt();
    //qDebug()<<"titre de n1"<<n1->getTitle() ;
    //qDebug()<<"titre de n2"<<n2->getTitle() ;
    //Couple* coupleLoaded= new Couple(label,n1,n2);
    Reference::getInstance()->addCoupleReference(*n1,id2.toInt());
}


*/


