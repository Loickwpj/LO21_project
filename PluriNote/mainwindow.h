#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QListWidgetItem>

#include "manager.h"
#include "noteediteur.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
;
    void clear(QLayout *layout);

    static mainWindow* getInstance();
    static void libererInstance();
    void setNotesList();
    void setArchivesList();

private:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();
    Ui::mainWindow *ui;
    static mainWindow* instance;

public slots:
    void createArticle();
    void createTask();
    void createAudio();
    void createImage();
    void createVideo();

};

#endif // MAINWINDOW_H
