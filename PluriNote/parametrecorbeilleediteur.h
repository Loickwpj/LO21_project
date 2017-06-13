#ifndef parametrecorbeilleediteur_h
#define parametrecorbeilleediteur_h
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>
#include "mainwindow.h"



class Editeur : public QWidget {
    Q_OBJECT
protected:
    QLabel* question;
    QPushButton* oui;
    QPushButton* non;
    QHBoxLayout* reponse;
    QVBoxLayout* layout;
public:

    Editeur (QWidget* parent =0);

public slots:
    virtual void clickOnOui() =0;
    virtual void clickOnNon() =0;
private slots:
};

class ParametreCorbeille : public Editeur{
    Q_OBJECT
public:
    ParametreCorbeille (QWidget* parent =0);
public slots:
    void clickOnOui();
    void clickOnNon();
};

class QuitterApp : public Editeur {
    Q_OBJECT
public :
    QuitterApp(QWidget* =0);
public slots:
    void clickOnOui();
    void clickOnNon();

};


#endif
