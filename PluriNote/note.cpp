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

