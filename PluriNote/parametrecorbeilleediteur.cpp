#ifndef parametrecorbeilleediteur_cpp
#define parametrecorbeilleediteur_cpp

#include "parametrecorbeilleediteur.h"

#endif

Editeur::Editeur (QWidget*){


    oui = new QPushButton("oui");
    non = new QPushButton("non");
    reponse = new QHBoxLayout;
    layout= new QVBoxLayout;

    reponse->addWidget(oui);
    reponse->addWidget(non);



}

ParametreCorbeille::ParametreCorbeille(QWidget*) : Editeur() {

    question = new QLabel ("Voulez-vous vider la corbeille automatique à chaque fermeture de l'application?");

    layout->addWidget(question);
    layout->addLayout(reponse);

    setLayout(layout);

    QObject::connect(oui,SIGNAL(clicked()),this,SLOT(clickOnOui()));
    QObject::connect(non,SIGNAL(clicked()),this,SLOT(clickOnNon()));


};


void ParametreCorbeille::clickOnOui(){
    QSettings settings("loickwpj","pluriNote");
    settings.setValue("viderCorbeilleAuto",true);
    this->close();
}

void ParametreCorbeille::clickOnNon(){
    QSettings settings("loickwpj","pluriNote");
    settings.setValue("viderCorbeilleAuto",false);
    this->close();
}

QuitterApp::QuitterApp(QWidget*) : Editeur() {

    question = new QLabel ("Voulez-vous vider la corbeille?");

    layout->addWidget(question);
    layout->addLayout(reponse);

    setLayout(layout);

    QObject::connect(oui,SIGNAL(clicked()),this,SLOT(clickOnOui()));
    QObject::connect(non,SIGNAL(clicked()),this,SLOT(clickOnNon()));


};
void QuitterApp::clickOnOui(){
    Corbeille::getInstance().deleteAll();
    this->close();
    mainWindow::getInstance()->close();
}

void QuitterApp::clickOnNon(){
    this->close();
    mainWindow::getInstance()->close();
}

