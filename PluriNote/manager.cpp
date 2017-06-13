#ifndef manager_cpp
#define manager_cpp

#include "manager.h"

#include <QDebug>
#include <QTextCodec>
#include <QTextCodec>
#include <QtXml>
#include <map>
#include <QFile>

#endif

/**********************************************
 **             NOTESMANAGER                 **
 **********************************************/

std::map<QString,Note*> NotesManager::m_map= std::map<QString,Note*>();

void NotesManager::Register(const QString& key,Note* obj)
{
    //si la clé n'est pas déjà présente
    if(m_map.find(key)==m_map.end())
    {
        //on ajoute le type d'objet dans le map
        m_map[key]=obj;
    }

}

Note* NotesManager::Create(const QString& key) const
{
    Note* tmp=0;
    std::map<QString, Note*>::const_iterator it=m_map.find(key);

    //si l'itérateur ne vaut pas map.end(), cela signifie que la clé à été trouvée
    if(it!=m_map.end())
    {
        tmp=((*it).second)->clone();
    }
    tmp->setId();
    return tmp;
}


Note* NotesManager::getNewNote(const QString& type){
    Note* n = Create(type);
    addNote(n);
    //editNote(n,type);
    return n;
}


void NotesManager::addNote(Note* n){

    if(nbNote == nbMaxNote){
        Note ** old_notes = notes;
        notes = new Note*[nbMaxNote+5];
        for(unsigned int i = 0; i < nbNote; i++){
            notes[i] = old_notes[i];
        }
        nbMaxNote += 5;
        delete[] old_notes;
    }

    notes[nbNote++] = n;

}

void NotesManager::supprimerNote(int id){
    notes[id]=notes[--nbNote];
}

Note* NotesManager::getNote(int i){
    return notes[i];
}


void NotesManager::save() const {
    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException("erreur sauvegarde notes : ouverture fichier xml");
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("fichier_notes");
    for(unsigned int i=0; i<nbNote; i++){
        notes[i]->saveNote(stream);
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}


void NotesManager::load(){
    QFile fin(filename);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
    }

    QXmlStreamReader xml(&fin);



    while(!xml.atEnd() && !xml.hasError()) {

        QXmlStreamReader::TokenType token = xml.readNext();

        if(token == QXmlStreamReader::StartDocument) continue;

        if(token == QXmlStreamReader::StartElement) {


            if(xml.name() == "fichier_notes") continue;


            if (xml.name()=="Article")
                loadArticle(xml);
            else
                if(xml.name()=="Task")
                    loadTask(xml);
                else
                    if(xml.name()=="Image")
                        loadMultimedia(xml,(QString)"Image");
                    else
                        if(xml.name()=="Audio")
                            loadMultimedia(xml,(QString)"Audio");
                        else
                            if(xml.name()=="Video")
                                loadMultimedia(xml,(QString)"Video");
                            else
                                throw NotesException("Partie du xml non reconnue");

        }
    }


    if(xml.hasError()) {
        qDebug()<<"erreur lecteur fichier, parser \n";
        throw NotesException("Erreur lecteur fichier notes, parser xml");

    }

    xml.clear();

    qDebug()<<"fin load\n";
}


void NotesManager::loadArticle(QXmlStreamReader &xml){

    QString identificateur;
    QString titre;
    QString text;
    QString dateC;
    QString dateM;
    QString archive;

    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Article")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toInt();
                qDebug()<<"id="<<identificateur<<"\n";
            }


            if(xml.name() == "title") {
                xml.readNext(); titre=xml.text().toString();
                qDebug()<<"titre="<<titre<<"\n";
            }


            if(xml.name() == "dateCreation") {
                xml.readNext();
                dateC=xml.text().toString();
                qDebug()<<"date creation"<<dateC<<"\n";
            }


            if(xml.name() == "dateModif") {
                xml.readNext();
                dateM=xml.text().toString();
                qDebug()<<"date de derniere modif"<<dateM<<"\n";
            }


            if(xml.name() == "archive") {
                xml.readNext();
                archive = (xml.text()).toInt();
                qDebug()<<"archive"<<archive<<"\n";
            }


            if(xml.name() == "texte") {
                xml.readNext(); text=xml.text().toString();
                qDebug()<<"texte="<<text<<"\n";
            }
        }

        xml.readNext();
    }
    qDebug()<<"ajout Article "<<identificateur<<"\n";
    Note *ArticleLoaded = new Article(identificateur.toInt(),titre,QDate::fromString(dateC),QDate::fromString(dateM),archive.toInt(),text);
    ArticleLoaded->setId();
    addNote(ArticleLoaded);
}


void NotesManager::loadTask(QXmlStreamReader &xml){
    qDebug()<<"new Task\n";
    QString identificateur;
    QString titre;
    QString text;
    QString dateC;
    QString dateM;
    QString archive;
    QString action;
    QString priority;
    QString deadline;
    QString status;


    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Task")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toInt();
                qDebug()<<"id="<<identificateur<<"\n";
            }


            if(xml.name() == "title") {
                xml.readNext(); titre=xml.text().toString();
                qDebug()<<"titre="<<titre<<"\n";
            }

            if(xml.name() == "dateCreation") {
                xml.readNext();
                dateC=xml.text().toString();
                qDebug()<<"date creation"<<dateC<<"\n";
            }


            if(xml.name() == "dateModif") {
                xml.readNext();
                dateM=xml.text().toString();
                qDebug()<<"date de derniere modif"<<dateM<<"\n";
            }


            if(xml.name() == "archive") {
                xml.readNext();
                archive = (xml.text()).toInt();
                qDebug()<<"archive"<<archive<<"\n";
            }



            if(xml.name() == "dateModif") {
                xml.readNext();
                dateM=xml.text().toString();
                qDebug()<<"date de derniere modif"<<dateM<<"\n";
            }


            if(xml.name() == "action") {
                xml.readNext(); action=xml.text().toString();
                qDebug()<<"action="<<action<<"\n";
            }

            if(xml.name() == "priorite") {
                xml.readNext();
                priority=(xml.text().toInt());
                qDebug()<<"priorite"<<priority<<"\n";
            }

            if(xml.name() == "deadline") {
                xml.readNext();
                deadline=xml.text().toString();
                qDebug()<<"deadline"<<deadline<<"\n";
            }


            if(xml.name() == "etat") {
                xml.readNext();
                status=xml.text().toString();
                qDebug()<<"etat"<<status<<"\n";
            }
        }

        xml.readNext();
    }

    Note *taskLoaded = new Task(identificateur.toInt(),titre,
                                QDate::fromString(dateC),QDate::fromString(dateM),archive.toInt(),action,priority.toInt(),
                                QDate::fromString(deadline),toState(status) );
    taskLoaded->setId();
    addNote(taskLoaded);
}
void NotesManager::loadMultimedia(QXmlStreamReader &xml, QString type){
    qDebug()<<"new"<< type <<"\n";
    QString identificateur;
    QString titre;
    QString dateC;
    QString dateM;
    QString archive;
    QString description;
    QString image;



    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();

    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == type)) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {

            if(xml.name() == "id") {
                xml.readNext(); identificateur=xml.text().toInt();
                qDebug()<<"id="<<identificateur<<"\n";
            }


            if(xml.name() == "title") {
                xml.readNext(); titre=xml.text().toString();
                qDebug()<<"titre="<<titre<<"\n";
            }

            if(xml.name() == "dateCreation") {
                xml.readNext();
                dateC=xml.text().toString();
                qDebug()<<"date creation"<<dateC<<"\n";
            }


            if(xml.name() == "dateModif") {
                xml.readNext();
                dateM=xml.text().toString();
                qDebug()<<"date de derniere modif"<<dateM<<"\n";
            }



            if(xml.name() == "archive") {
                xml.readNext();
                archive = xml.text().toInt();
                qDebug()<<"archive"<<archive<<"\n";
            }


            if(xml.name() == "description") {

                xml.readNext(); description=xml.text().toString();
                qDebug()<<"description="<<description<<"\n";
            }



            if(xml.name() == "image") {

                xml.readNext(); image=xml.text().toString();
                qDebug()<<"image="<<image<<"\n";
            }
        }


        xml.readNext();
    }

    if(type=="Image")
    {
        qDebug()<<"ajout Image "<<identificateur<<"\n";
        Note *imageLoaded = new Image(identificateur.toInt(),titre,QDate::fromString(dateC),
                                      QDate::fromString(dateM),archive.toInt(),description,image);
        imageLoaded->setId();
        addNote(imageLoaded);
    }

    if (type=="Audio")
    {
        qDebug()<<"ajout Audio "<<identificateur<<"\n";
        Note *audioLoaded = new Audio(identificateur.toInt(),titre,QDate::fromString(dateC),
                                      QDate::fromString(dateM),archive.toInt(),description,image);
        audioLoaded->setId();
        addNote(audioLoaded);
    }

    if (type=="Video")
    {
        qDebug()<<"ajout Video "<<identificateur<<"\n";
        Note *videoLoaded = new Video(identificateur.toInt(),titre,QDate::fromString(dateC),
                                      QDate::fromString(dateM),archive.toInt(),description,image);
        videoLoaded->setId();
        addNote(videoLoaded);
    }


}



/**********************************************
**             RELATIONSMAANGER              **
***********************************************/


Relation& RelationsManager::getNewRelation(const QString& id,const QString& desc){

    Relation *r = new Relation(id,desc);
    addRelation(r);
    return *r;
}

void RelationsManager::addRelation(Relation* r){
    for(unsigned int i = 0; i < nbRelation; i++){
        if(r->getTitle() == relations[i]->getTitle())
            throw NotesException("Relation existe deja");
    }
    if(nbRelation == nbMaxRelation){
        Relation** newRelation = new Relation* [nbMaxRelation+5];
        for (unsigned int i=0; i<nbMaxRelation; i++){
            newRelation[i]= new Relation (*relations[i]);
        }
        Relation** oldRelations = relations;
        relations = newRelation;
        for (unsigned int i=0; i<nbMaxRelation; i++){
            delete oldRelations[i];
        }
        delete [] oldRelations;
        nbMaxRelation+=5;
    }
    relations[nbRelation++]=r;
}

Relation& RelationsManager::getRelation(const QString& title){
    for(unsigned int i = 0; i <nbRelation; i++){
        if( relations[i]->getTitle() == title) return *relations[i];
    }
    throw NotesException("Relation n existe pas");
}

Relation& RelationsManager::getRelation(unsigned int i){
    return *relations[i];
}

void RelationsManager::chercherCouple(Note*n){
    for (unsigned int i=0; i<nbRelation;i++){
        relations[i]->chercherCoupleInRelation(n);
    }
}



void RelationsManager::saveRelation() const {

    QFile newfile(filename);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException("erreur sauvegarde notes : ouverture fichier xml");
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("fichier_relation");
    for(unsigned int i=0; i<nbRelation; i++){
        stream.writeStartElement("relation");
        stream.writeTextElement("titleRelation", relations[i]->getTitle());
        stream.writeTextElement("descriptionRelation", relations[i]->getDescription());
        stream.writeTextElement("nbCouple",QString::number(relations[i]->getNbCouple()));
        stream.writeTextElement("nbMaxCouple",QString::number(relations[i]->getNbMaxCouple()));
        stream.writeTextElement("oriented",QString::number(relations[i]->getOriented()));

        stream.writeStartElement("couples");
        for(unsigned int j=0; j<relations[i]->getNbCouple();j++)
        {
            qDebug()<<"on est dans la boucle qui save les couple jusqu'a nombre de couple = "<<relations[i]->getNbCouple();
            relations[i]->getCouple(j)->saveCouple(stream);
        }
        stream.writeEndElement();
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}


void RelationsManager::loadRelations(){
    Relation* r = nullptr;
    QFile fin(filename);
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
            if(xml.name() == "fichier_relation") continue;

            if(xml.name() == "relation") {
                r=loadRelation(xml);
            }
            if(xml.name() == "couples") continue;
            if(xml.name()=="couple")
            {
                loadCouple(xml,r);
            }

        }

    }

    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}
/*
// We've found couples
if(xml.name() == "couples") {
    r= new Relation(descirption,title,oriented.toInt());
    loadCouple(xml,r);
    addRelation(r);
}
*/


Relation* RelationsManager::loadRelation(QXmlStreamReader &xml){
    qDebug()<<"new relation\n";
    QString title;
    QString descirption;

    QString nbCouple;
    QString nbMaxcouple;
    QString oriented;
    QXmlStreamAttributes attributes = xml.attributes();
    xml.readNext();
    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "oriented")) {
        if(xml.tokenType() == QXmlStreamReader::StartElement) {
            // We've found title
            if(xml.name() == "titleRelation") {
                xml.readNext(); title=xml.text().toString();
            }

            // We've found description
            if(xml.name() == "descriptionRelation") {
                xml.readNext(); descirption=xml.text().toString();
            }

            if(xml.name() == "oriented") {
                xml.readNext();
                oriented=xml.text().toString();
            }

        }
        xml.readNext();

    }

    Relation *r= new Relation(title,descirption,oriented.toInt());
    addRelation(r);
    return r;
}



void RelationsManager::loadCouple(QXmlStreamReader &xml,Relation* r){
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
    qDebug()<<"ajout couple "<<label<<"\n";
    Note* n1=NotesManager::getInstance().getNote(id1.toInt());
    Note* n2=NotesManager::getInstance().getNote(id2.toInt());
    //qDebug()<<"getNote(x) avec x1 = "<< id1.toInt();
    //qDebug()<<"getNote(x) avec x2 = "<< id2.toInt();
    //qDebug()<<"titre de n1"<<n1->getTitle() ;
    //qDebug()<<"titre de n2"<<n2->getTitle() ;
    Couple* coupleLoaded= new Couple(label,n1,n2);
    r->addCouple(coupleLoaded);
}



/**********************************************
***                 CORBEILLE                **
***********************************************/


void Corbeille::addNoteCorbeille(Note* n){

    if(nbNote == nbMaxNote){
        Note ** old_notes = notesSuppr;
        notesSuppr = new Note*[nbMaxNote+5];
        for(unsigned int i = 0; i < nbNote; i++){
            notesSuppr[i] = old_notes[i];
        }
        nbMaxNote += 5;
        delete[] old_notes;
    }
    notesSuppr[nbNote++]=n;

}

Note* Corbeille::getNote(Note* n){
    for (unsigned int i=0; i<nbNote; i++){
        if (notesSuppr[i]->getId() == n->getId() ) return notesSuppr[i];
    }
    throw NotesException("Error");
}

Note* Corbeille::getNote(int i){
    return notesSuppr[i];
}


void Corbeille::deleteNote(const QString & id){
    unsigned int i=0;
    while (i<nbNote && notesSuppr[i]->getId() != id) i++;
    if (i==nbNote) throw NotesException("Cette note n'est pas dans la corbeille");
    delete notesSuppr[i];
    notesSuppr[i]=notesSuppr[nbNote-1];
    nbNote--;

}

void Corbeille::deleteAll(){

    for (unsigned int i=0; i<nbNote; i++)delete notesSuppr[i];
    delete [] notesSuppr;
    notesSuppr=nullptr;
    nbNote=0;
    nbMaxNote=0;
}

void Corbeille::supprimerNote(unsigned int id){


    for (unsigned int i =0; i<nbNote;i++){
        if (notesSuppr[i]->getId() == id){

            if (nbNote-1 == i){ notesSuppr[i]=nullptr; nbNote--;}
            else{
                if (nbNote == 1) {notesSuppr[--nbNote]=nullptr;}
                else {notesSuppr[i]=notesSuppr[--nbNote];}
            }
        }
    }
}


void Corbeille::restaurer(unsigned int id){
    for (unsigned int i=0; i<nbNote; i++){
        if (notesSuppr[i]->getId() == id ) NotesManager::getInstance().addNote(notesSuppr[i]);
    }
    supprimerNote(id);
}




