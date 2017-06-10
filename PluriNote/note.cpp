#ifndef note_cpp
#define note_cpp
#include "note.h"
#include<QDebug>
#endif


/**************************************************************
***                        Clone                            ***
***************************************************************/

int Note::idIterator = 0;

Task* Task::clone(){return new Task(*this);}
Article* Article::clone(){return new Article(*this);}
Image* Image::clone(){return new Image(*this);}
Audio* Audio::clone(){return new Audio(*this);}
Video* Video::clone(){return new Video(*this);}



/**************************************************************
 ***                        saveNote                          ***
 ***************************************************************/

//on pourrait factoriser les premiers elements
//(mais on adopte methode agile donc on privilégie la fonctionnalité)


void Note::saveNote(QXmlStreamWriter &stream) const {
    
    stream.writeTextElement("id",QString::number(getId()));
    stream.writeTextElement("title", getTitle());
    stream.writeTextElement("dateCreation",getDateC().toString());
    stream.writeTextElement("dateModif", getDateM().toString());
    stream.writeTextElement("archive", QString::number(GetArchive()) );
    
}

void Article::saveNote(QXmlStreamWriter &stream) const {
    
    stream.writeStartElement("Article");
    Note::saveNote(stream);
    stream.writeTextElement("texte", getText());
    
    stream.writeEndElement();
}


void Task::saveNote(QXmlStreamWriter &stream) const {
    
    stream.writeStartElement("Task");
    Note::saveNote(stream);
    stream.writeTextElement("action", getAction());
    stream.writeTextElement("priorite", QString::number(getPriority()));
    stream.writeTextElement("deadline",getDeadline().toString());
    stream.writeTextElement("etat", toString(getState()));
    stream.writeEndElement();
}

void Multimedia::saveNote(QXmlStreamWriter &stream) const {
    
    Note::saveNote(stream);
    
    stream.writeTextElement("description", getDescription());
    stream.writeTextElement("image", getImage());
    
}


void Image::saveNote(QXmlStreamWriter &stream) const {
    
    stream.writeStartElement("Image");
    Multimedia::saveNote(stream);
    stream.writeEndElement();
    
}

void Audio::saveNote(QXmlStreamWriter &stream) const {
    
    stream.writeStartElement("Audio");
    Multimedia::saveNote(stream);
    stream.writeEndElement();
    
}

void Video::saveNote(QXmlStreamWriter &stream) const {
    
    stream.writeStartElement("Video");
    Multimedia::saveNote(stream);
    stream.writeEndElement();
    
}
/**************************************************************
 ***                        setList                           ***
 ***************************************************************/


QString Note::setNotesListNote(){
        qDebug() << "Note non archive" ;
        QString id = QString::number(getId());
        QString title = getTitle();
        QString titre = id+"-"+title ;
        //qDebug()<<"on ajoute la note non archive did" << id <<"a la list";
        //item = new QListWidgetItem(titre,ui->listWidgetNotesActives);
        qDebug()<<"on ajoute la note non archive did" << id <<"a la list";
        return(titre);
}

QString Task::setNotesListNote()
{
    qDebug() << "Task non archive" ;
    QString id = QString::number(getId());
    QString title = getTitle();
    QString priorite = QString::number(getPriority());
    QString deadLine = getDeadline().toString();
    QString titre = id+"-"+title+" : " + priorite + " --> " + deadLine ;
    //qDebug()<<"on ajoute la note non archive did" << id <<"a la list";
    //item = new QListWidgetItem(titre,ui->listWidgetNotesActives);
    qDebug()<<"on ajoute la task non archive did" << id <<"a la list";
    return(titre);
}



/**************************************************************
 ***                       MEMENTO                             ***
 ***************************************************************/



/*********************************************************************
***                       Memento Article                         ***
**********************************************************************/


Article& Article::addMemento() {
        qDebug()<<"on est rentré dans add";
        if(nbMemento == nbMax){
        qDebug()<<" on est dans le if";
        MementoA** oldCareTaker = careTaker;
        nbMax += 5;
        careTaker = new MementoA*[nbMax];
        for(unsigned int i =0; i < nbMemento; i++)
            careTaker[i] = oldCareTaker[i];
        delete[] oldCareTaker;
    }
    qDebug()<<"on est just apres le if";
    MementoA *m = createMemento();
    qDebug()<<"jusque la tout va bien";

    careTaker[nbMemento++]= m ;// crée un memento et l'ajoute au tableau des mementos
    qDebug()<<"on a crée un memento dans le tableau";
    return *this;
}

Article* Article::getPreviousMemento() {
    unsigned int i=nbMemento-1;
    setText(careTaker[i]->text);
    setTitle(careTaker[i]->title);
    setArchive(careTaker[i]->archive);
    setDateLastModification(careTaker[i]->dateM);
    delete careTaker[i];
    nbMemento--;
    qDebug()<<"nb memento ="<<nbMemento;
    return this;
}



/*********************************************************************
***                       Memento Tache                             ***
**********************************************************************/


Task& Task::addMemento() {
        if(nbMemento == nbMax){
        MementoT** oldCareTaker = careTaker;
        nbMax += 5;
        careTaker = new MementoT*[nbMax];
        for(unsigned int i =0; i < nbMemento; i++)
            careTaker[i] = oldCareTaker[i];
        delete[] oldCareTaker;
    }
    careTaker[nbMemento++]= createMemento(); // crée un memento et l'ajoute au tableau des mementos
    return *this;
}

Task* Task::getPreviousMemento() {
    unsigned int i=nbMemento-1;
    setTitle(careTaker[i]->title);
    setArchive(careTaker[i]->archive);

    setDateLastModification(careTaker[i]->dateM);
    setAction(careTaker[i]->action);
    setPriority(careTaker[i]->priority);
    setDeadline(careTaker[i]->deadline);
    setState(careTaker[i]->status);
    delete careTaker[i];
    nbMemento--;
    return this;
}


/*********************************************************************
***                       Memento Multimedia                       ***
**********************************************************************/


Multimedia& Multimedia::addMemento() {
        if(nbMemento == nbMax){
        MementoM** oldCareTaker = careTaker;
        nbMax += 5;
        careTaker = new MementoM*[nbMax];
        for(unsigned int i =0; i < nbMemento; i++)
            careTaker[i] = oldCareTaker[i];
        delete[] oldCareTaker;
    }
    careTaker[nbMemento++]= createMemento(); // crée un memento et l'ajoute au tableau des mementos
    return *this;
}

Multimedia* Multimedia::getPreviousMemento() {
    unsigned int i=nbMemento-1;
    setTitle(careTaker[i]->title);
    setArchive(careTaker[i]->archive);

    setDateLastModification(careTaker[i]->dateM);
    setDescription(careTaker[i]->description);
    setImage(careTaker[i]->image );
    delete careTaker[i];
    nbMemento--;
    return this;
}



Video* Video::getPreviousMemento() {
    unsigned int i=nbMemento-1;

    setTitle(careTaker[i]->title);
    setArchive(careTaker[i]->archive);
    setDateLastModification(careTaker[i]->dateM);
    setDescription(careTaker[i]->description);
    setImage(careTaker[i]->image );
    delete careTaker[i];
    nbMemento--;
    return this;
}


Image* Image::getPreviousMemento() {
    unsigned int i=nbMemento-1;
    setTitle(careTaker[i]->title);
    setArchive(careTaker[i]->archive);

    setDateLastModification(careTaker[i]->dateM);
    setDescription(careTaker[i]->description);
    setImage(careTaker[i]->image );
    delete careTaker[i];
    nbMemento--;
    return this;
}

Audio* Audio::getPreviousMemento() {
    unsigned int i=nbMemento-1;
    setTitle(careTaker[i]->title);
    setArchive(careTaker[i]->archive);

    setDateLastModification(careTaker[i]->dateM);
    setDescription(careTaker[i]->description);
    setImage(careTaker[i]->image );
    delete careTaker[i];
    nbMemento--;
    return this;
}
