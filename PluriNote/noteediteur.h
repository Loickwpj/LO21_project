#ifndef noteediteur_h
#define noteediteur_h
#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QDate>
#include <QPushButton>
#include <QLineEdit>
#include "note.h"
#include <QComboBox>

/*********************************************************************
 ***                         Note Editeur                           **
 *********************************************************************/

class NoteEditeur : public QWidget{
private:
    Q_OBJECT
protected:
    QFormLayout* formulaire;
    QVBoxLayout* layout;

    QLineEdit* id;
    QLineEdit* title;
    QLineEdit* dateC;
    QLineEdit* dateM;

    QPushButton* sauver;

   // Note* note;

public:
    NoteEditeur(QWidget *parent = 0);
    virtual ~NoteEditeur() {}

signals:


public slots:
    virtual void saveModifications()=0;
private slots:
    void afficherBouton(QString str="");
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
    QLineEdit* priority;
    QLineEdit* deadline;
    //QLineEdit* state;
    QComboBox* state;
    Task* task;

public:
    TaskEditeur(Task* a, QWidget *parent=0);
    ~TaskEditeur() {}

signals:

public slots:
    virtual void saveModifications();

private slots:
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
};

#endif




























