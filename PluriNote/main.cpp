#include <QApplication>
#include <QWidget>
#include "note.h"
#include "noteediteur.h"
#include  "manager.h"
#include "singleton.h"
#include "corbeilleediteur.h"
#include "couple.h"
#include <QDebug>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    NotesManager::Register("Article", new Article);
    NotesManager::Register("Task", new Task);
    NotesManager::Register("Audio", new Audio);
    NotesManager::Register("Video", new Video);
    NotesManager::Register("Image", new Image);
    //Corbeille& c = Corbeille::getInstance();
    NotesManager& nm = NotesManager::getInstance();
    RelationsManager& rm = RelationsManager::getInstance();
    Note* n1 = nm.getNewNote("Article");
    Note* n2= nm.getNewNote("Task");
    Note* n3 = nm.getNewNote("Image");

    Relation& r = rm.getNewRelation("description1","titre1");
    r.addCouple(n1,n2);
    Relation& r1 = rm.getNewRelation("description2","titre2");
    r1.addCouple(n3,n2);



    return app.exec();
}

