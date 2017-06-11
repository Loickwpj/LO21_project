#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QListWidgetItem>

#include "manager.h"
#include "noteediteur.h"
#include "relationediteur.h"
#include "labelrelationediteur.h"


namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    friend class Note;
    Q_OBJECT

public:
    void clear();


    static mainWindow* getInstance();
    static void libererInstance();
    void setNotesList();
    void setArchivesList();
    void setRelationsList();

    Ui::mainWindow *ui;

private:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

    static mainWindow* instance;

public slots:
    void createArticle();
    void createTask();
    void createAudio();
    void createImage();
    void createVideo();
    void afficherCorbeille();

    void createRelation() ;
    void afficherRelation();
    void afficherNote();
    void afficherTask();
    void afficherArchive();
};

#endif // MAINWINDOW_H
