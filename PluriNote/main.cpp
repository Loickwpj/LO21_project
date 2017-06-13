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
#include <QSettings>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    NotesManager::Register("Article", new Article);
    NotesManager::Register("Task", new Task);
    NotesManager::Register("Audio", new Audio);
    NotesManager::Register("Video", new Video);
    NotesManager::Register("Image", new Image);
    QSettings settings("loickwpj","pluriNote");
    settings.setValue("viderCorbeilleAuto",false);



    QString fichier = QFileDialog::getOpenFileName();
    NotesManager::getInstance().setFilename(fichier);
    NotesManager::getInstance().load();

    QString fichierRelation = QFileDialog::getOpenFileName();
    RelationsManager::getInstance().setFilename(fichierRelation);
    RelationsManager::getInstance().loadRelations();

    mainWindow* mw = mainWindow::getInstance();
    mw->show();

    return app.exec();
}

