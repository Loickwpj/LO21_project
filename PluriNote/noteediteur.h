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
    QPushButton* bprevious;


public:

    ///CONSTRUCTEUR
    NoteEditeur(QWidget *parent = 0);

    ///DESTRUCTEUR
    virtual ~NoteEditeur() {}


signals:


public slots:
    virtual void saveModifications()=0;
    virtual void supprimer()=0;
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

    ///CONSTRUCTEUR
    ArticleEditeur(Article* a, QWidget *parent=0);

    ///DESTRUCTEUR
    ~ArticleEditeur() {}

signals:


public slots:
    virtual void saveModifications();
    virtual void supprimer();
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
    QComboBox* state;
    Task* task;
    QCheckBox* priorite;
    QCheckBox* bdeadline;
    QGroupBox* option;
    QHBoxLayout* lay;

public:

    ///CONSTRUCTEUR
    TaskEditeur(Task* a, QWidget *parent=0);

    ///DESTRUCTEUR
    ~TaskEditeur() {}


signals:

public slots:
    virtual void saveModifications();
    virtual void supprimer();
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
    ///CONSTRUCTEUR
    MultimediaEditeur(QWidget*parent=0);

    ///DESTRUCTEUR
    ~MultimediaEditeur(){}

signals:
public slots:
    virtual void saveModifications() = 0;
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

    ///CONSTRUCTEUR
    ImageEditeur(Image*, QWidget*parent=0);

    ///DESTRUCTEUR
    ~ImageEditeur() {}

public slots :
    void saveModifications();
    virtual void supprimer();
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

    ///CONSTRUCTEUR
    AudioEditeur(Audio*, QWidget*parent=0);

    ///DESTRUCTEUR
    ~AudioEditeur() {}

public slots :
    void saveModifications();
    virtual void supprimer();
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

    ///CONSTRUCTEUR
    VideoEditeur(Video*, QWidget*parent=0);

    ///DESTRUCTEUR
    ~VideoEditeur() {}

public slots :
    void saveModifications();
    virtual void supprimer();
    virtual void previousVersion();
};

#endif




























