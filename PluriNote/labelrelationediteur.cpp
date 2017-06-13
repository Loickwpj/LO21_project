#ifndef labelrelationediteur_cpp
#define labelrelationediteru_cpp

#include "labelrelationediteur.h"

#endif

labelRelationEditeur::labelRelationEditeur(Relation* r, QWidget*) : relation(r){
    description = new QLineEdit;
    titre = new QLineEdit;
    formulaire = new QFormLayout;
    layout = new QVBoxLayout;
    creer = new QPushButton ("créer");
    bannuler = new QPushButton ("annuler");

    formulaire->addRow("Titre : " , titre);
    formulaire->addRow("Description : ",description);


    creer->setDisabled(true);

    layout->addLayout(formulaire);
    layout->addWidget(creer);
    layout->addWidget(bannuler);
    setLayout(layout);

    QObject::connect(bannuler,SIGNAL(clicked()),this,SLOT(annuler()));
    QObject::connect(titre,SIGNAL(textChanged(QString)),this,SLOT(afficherButton()));
    QObject::connect(creer,SIGNAL(clicked()),this,SLOT(saveModification()));

}

void labelRelationEditeur::saveModification(){
    relation->setTitle(titre->text());
    relation->setDescription(description->text());
    QMessageBox::information(this,"sauvegarde","Relation créée !");
    mainWindow::getInstance()->setRelationsList();
    this->close();
}

void labelRelationEditeur::afficherButton(){
    creer->setDisabled(false);
}
