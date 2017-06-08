#include <QApplication>
#include <QWidget>
#include "note.h"
#include "noteediteur.h"
#include  "manager.h"
#include "singleton.h"
#include "corbeilleediteur.h"
#include "couple.h"
#include <QDebug>
#include <QFileDialog>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    NotesManager::Register("Article", new Article);
    NotesManager::Register("Task", new Task);
    NotesManager::Register("Audio", new Audio);
    NotesManager::Register("Video", new Video);
    NotesManager::Register("Image", new Image);
    //Corbeille& c = Corbeille::getInstance();
    NotesManager& nm = NotesManager::getInstance();
    //RelationsManager& rm = RelationsManager::getInstance();

   /* Note* n2= nm.getNewNote("Task");
    Note* n3 = nm.getNewNote("Image");
    Note* n4 = nm.getNewNote("Audio");
    Note* n5 = nm.getNewNote("Video");
    */
    //Relation& r = rm.getNewRelation("description1","titre1");
    //r.addCouple(n1,n2);
    //Relation& r1 = rm.getNewRelation("description2","titre2");
    //r1.addCouple(n3,n2);

    QString fichier = QFileDialog::getOpenFileName();
    nm.setFilename(fichier);
    qDebug()<<"avant load"<<"\n";
    nm.load();

    qDebug()<<"après load"<<"\n";

    qDebug()<<NotesManager::getInstance().getNbNote();
    for(unsigned int i=0;i<nm.getNbNote();i++){
    qDebug()<<"id: " <<nm.notes[i]->getId()<<"\n";
    qDebug()<<"date creation: " <<nm.notes[i]->getDateC()<<"\n";
    qDebug()<<"date lastmodif: " <<nm.notes[i]->getDateM()<<"\n";
    qDebug()<<"title " <<nm.notes[i]->getTitle()<<"\n";
    }

    Note* n1 = nm.getNewNote("Article");

    return app.exec();
}

