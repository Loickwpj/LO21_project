#ifndef noteediteur_h
#define noteediteur_h

#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDate>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QSpinBox>

//#include "manager.h"
//#include "singleton.h"
//#include "note.h"
#include "corbeilleediteur.h"
#include "mainwindow.h"

/*********************************************************************
 ***                         Note Editeur                           **
 *********************************************************************/

class Article;
class Task;
class Image;
class Audio;
class Video;

class NoteEditeur : public QWidget{

private:
    Q_OBJECT
protected:
    QFormLayout* formulaire;
    QVBoxLayout* layout;

    QLineEdit* id;
    QLineEdit* title;
    QDateEdit* dateC;
    QDateEdit* dateM;

    QPushButton* sauver;
    QPushButton* bsupprimer;
    ///MEMENTO AJOUT BOUTON
    QPushButton* bprevious;




    // Note* note;

public:
    NoteEditeur(QWidget *parent = 0);
    virtual ~NoteEditeur() {}


signals:


public slots:
    virtual void saveModifications()=0;
    virtual void supprimer()=0;
    ///MEMENTO METHOD VIRTUELLE PUR
    virtual void previousVersion()=0;
private slots:
    void afficherBouton(QString str="");
    void afficherBouton(int);
    void afficherBouton(QDate);

};


/*********************************************************************/



/*********************************************************************
 ***                      Article Editeur                           **
 *********************************************************************/

class ArticleEditeur : public NoteEditeur{
private:
    Q_OBJECT
    QLineEdit* text;
    Article* article;

public:
    ArticleEditeur(Article* a, QWidget *parent=0);
    ~ArticleEditeur() {}

signals:


public slots:
    virtual void saveModifications();
    virtual void supprimer();
    ///MEMENTO METHOD REDEFINI
    virtual void previousVersion();


private slots:
};

/*********************************************************************/



/*********************************************************************
 ***                           Task Editeur                         **
 *********************************************************************/
class TaskEditeur : public NoteEditeur{
private:
    Q_OBJECT
    QLineEdit* action;
    QSpinBox* priority;
    QDateEdit* deadline;
    //QLineEdit* state;
    QComboBox* state;
    Task* task;
    QCheckBox* priorite;
    QCheckBox* bdeadline;
    QGroupBox* option;
    QHBoxLayout* lay;

public:
    TaskEditeur(Task* a, QWidget *parent=0);
    ~TaskEditeur() {}


signals:

public slots:
    virtual void saveModifications();
    virtual void supprimer();
    ///MEMENTO METHOD REDEFINI
    virtual void previousVersion();
private slots:
    void afficherPriorite();
    void afficherDeadline();
};


/********************************************************************
***                     Multimedia Editeur                         **
*********************************************************************/

class MultimediaEditeur : public NoteEditeur {
private:
    Q_OBJECT
protected:
    QLineEdit* description;
    QLineEdit* image;

public:
    MultimediaEditeur(QWidget*parent=0);
    ~MultimediaEditeur(){}

signals:
public slots:
    virtual void saveModifications() = 0;
    virtual void supprimer() = 0;
    ///MEMENTO METHOD REDEFINI PUR
    virtual void previousVersion()=0;

private slots:
};

/*********************************************************************/

/********************************************************************
***                          Image Editeur                         **
*********************************************************************/

class ImageEditeur : public MultimediaEditeur {
private:
    Q_OBJECT
    Image* fichierImage;
public:
    ImageEditeur(Image*, QWidget*parent=0);
    ~ImageEditeur() {}

public slots :
    void saveModifications();
    virtual void supprimer();
    ///MEMENTO METHOD REDEFINI
    virtual void previousVersion();
};

/*********************************************************************/

/********************************************************************
***                          Audio Editeur                         **
*********************************************************************/

class AudioEditeur : public MultimediaEditeur {
private:
    Q_OBJECT
    Audio* fichierAudio;
public:
    AudioEditeur(Audio*, QWidget*parent=0);
    ~AudioEditeur() {}

public slots :
    void saveModifications();
    virtual void supprimer();
    ///MEMENTO METHOD REDEFINI
    virtual void previousVersion();
};

/*********************************************************************/

/********************************************************************
***                          Video Editeur                         **
*********************************************************************/

class VideoEditeur : public MultimediaEditeur {
private:
    Q_OBJECT
    Video* fichierVideo;
public:
    VideoEditeur(Video*, QWidget*parent=0);
    ~VideoEditeur() {}

public slots :
    void saveModifications();
    virtual void supprimer();
    ///MEMENTO METHOD REDEFINI
    virtual void previousVersion();
};

#endif




























