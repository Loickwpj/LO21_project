#ifndef labelediteur_cpp
#define labelediteur_cpp
#include "labelediteur.h"
#include <QMessageBox>
#include <QDebug>
#endif


labelEditeur::labelEditeur(Couple* c, QWidget*) : couple(c){
    label = new QLineEdit;
    formulaire = new QFormLayout;
    layout = new QVBoxLayout;
    modifier = new QPushButton ("enregistrer");
    bannuler = new QPushButton ("annuler");

    formulaire->addRow("Label : ",label);


    modifier->setDisabled(true);

    layout->addLayout(formulaire);
    layout->addWidget(modifier);
    layout->addWidget(bannuler);
    setLayout(layout);

    QObject::connect(bannuler,SIGNAL(clicked()),this,SLOT(annuler()));
    QObject::connect(label,SIGNAL(textChanged(QString)),this,SLOT(afficherButton()));
    QObject::connect(modifier,SIGNAL(clicked()),this,SLOT(saveModification()));

}

void labelEditeur::saveModification(){
    couple->setLabel(label->text());
    QMessageBox::information(this,"sauvegarde","Label modifié !");
    this->close();
}

void labelEditeur::afficherButton(){
    modifier->setDisabled(false);
}
