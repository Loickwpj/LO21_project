#ifndef note_cpp
#define note_cpp
#include "note.h"
#include<QDebug>
#endif

/**************************************************************
***                        editNote()                       ***
***************************************************************/

void Article::editNote(){
    ArticleEditeur* e = new ArticleEditeur(this,0);
    mainWindow::getInstance()->ui->partiePrincipale->addWidget(e);
}

void Task::editNote(){
    TaskEditeur* e = new TaskEditeur(this,0);
    mainWindow::getInstance()->ui->partiePrincipale->addWidget(e);
}

void Image::editNote(){
    ImageEditeur* e = new ImageEditeur(this,0);
    mainWindow::getInstance()->ui->partiePrincipale->addWidget(e);
}

void Audio::editNote(){
    AudioEditeur* e = new AudioEditeur(this,0);
    mainWindow::getInstance()->ui->partiePrincipale->addWidget(e);
}

void Video::editNote(){
    VideoEditeur* e = new VideoEditeur(this,0);
    mainWindow::getInstance()->ui->partiePrincipale->addWidget(e);
}


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

/*************************************************************
***                        setList                         ***
**************************************************************/


QString Note::setNotesListNote(){
    QString id = QString::number(getId());
    QString title = getTitle();
    QString titre = " "+id+" -"+title ;
    return(titre);
}

QString Task::setNotesListNote(){
    QString id = QString::number(getId());
    QString title = getTitle();
    QString priorite = QString::number(getPriority());
    QString deadLine = getDeadline().toString();
    QString titre =" "+id+" -"+title+" : " + priorite + " --> " + deadLine ;
    return(titre);
}



/***************************************************************
 ***                       MEMENTO                           ***
 ***************************************************************/



/*******************************************************************
***                       Memento Article                        ***
********************************************************************/


Article& Article::addMemento() {

    if(nbMemento == nbMax){
        MementoA** oldCareTaker = careTaker;
        nbMax += 5;
        careTaker = new MementoA*[nbMax];
        for(unsigned int i =0; i < nbMemento; i++)
            careTaker[i] = oldCareTaker[i];
        delete[] oldCareTaker;
    }


    MementoA *m = createMemento();


    careTaker[nbMemento++]= m ;// crée un memento et l'ajoute au tableau des mementos

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
    careTaker[nbMemento++]= createMemento();
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
    careTaker[nbMemento++]= createMemento();
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
