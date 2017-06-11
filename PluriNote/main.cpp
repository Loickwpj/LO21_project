#include <QApplication>
#include <QWidget>
#include "note.h"

//#include "noteediteur.h"
//#include  "manager.h"
#include "singleton.h"
#include "corbeilleediteur.h"
#include "relationediteur.h"
#include "coupleediteur.h"
#include "mainwindow.h"
#include <QDebug>
#include <QFileDialog>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    NotesManager::Register("Article", new Article);
    NotesManager::Register("Task", new Task);
    NotesManager::Register("Audio", new Audio);
    NotesManager::Register("Video", new Video);
    NotesManager::Register("Image", new Image);

    QString fichier = QFileDialog::getOpenFileName();
    NotesManager::getInstance().setFilename(fichier);
    NotesManager::getInstance().load();

    qDebug()<<"on est maintenant là";
    mainWindow* mw = mainWindow::getInstance();
    mw->show();
<<<<<<< HEAD

*/
=======
/*
     Couple c1();
>>>>>>> 381718c66f38ac4b35b901ea4f898450bec1d6f8

   Article* a = new Article();
    Article* b = new Article();
    Task* c = new Task();
    Task* d= new Task();
    Relation re("desc1","titre1");
    Couple* couple = new Couple ("label",a,b);
    re.addCouple(couple);
    RelationEditeur* r = new RelationEditeur(&re);
    r->show();


    return app.exec();

}

