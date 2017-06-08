#ifndef relationediteur_cpp
#define relationediteur_cpp
#include <QDebug>
#include "relationediteur.h"


#endif

RelationEditeur::RelationEditeur(Relation* r, QWidget*) : relation(r) {

    titreRelation = new QLabel(relation->getTitle());
    list = new QListWidget();
    layout = new QVBoxLayout();
    scroller = new QScrollArea();
    modifier = new QPushButton("Modifier label");
    supprimer = new QPushButton("Supprimer couple");
    ajouter = new QPushButton("Ajouter couple");
    rafraichir = new QPushButton("Rafraîchir la liste");
    oriented = new QCheckBox("orientée");
    option = new QGroupBox("options");
    optionLayout = new QVBoxLayout;

    modifier->setDisabled(true);
    supprimer->setDisabled(true);
    rafraichir->setDisabled(true);
    optionLayout->addWidget(oriented);

    option->setLayout(optionLayout);
    scroller->setWidget(list);
    layout->addWidget(titreRelation);
    layout->addWidget(list);
    layout->addWidget(ajouter);
    layout->addWidget(modifier);
    layout->addWidget(supprimer);
    layout->addWidget(rafraichir);
    layout->addWidget(option);

    setList();

    setLayout(layout);


    QObject::connect(modifier, SIGNAL(clicked()), this, SLOT(modifierLabel()));
    QObject::connect(supprimer, SIGNAL(clicked()), this, SLOT(supprimerCouple()));
    QObject::connect(list, SIGNAL(itemSelectionChanged()), this, SLOT(afficherBoutons()));
    QObject::connect(modifier, SIGNAL(clicked()), this, SLOT(afficherRafraichir()));
    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(addCouple()));
    QObject::connect(rafraichir,SIGNAL(clicked()), this, SLOT(ssetList()));
    QObject::connect(oriented, SIGNAL(clicked()),this,SLOT(setOriented()));

}

void RelationEditeur::setOriented(){
    relation->setOriented();
}

void RelationEditeur::ssetList(){
    list->clear();
    QListWidgetItem* item;
    for(unsigned int i=0;i<relation->getNbCouple();i++){
        Couple* c = relation->getCouple(i);
        QString label=c->getLabel();
        QString id1 =QString::number(c->getNote1()->getId());
        QString id2 =QString::number(c->getNote2()->getId());
        item = new QListWidgetItem("Note1: "+id1+" Note2: "+id2+" ("+label+")",list);
    }
    rafraichir->setDisabled(true);
}
void RelationEditeur::setList(){
    list->clear();
    QListWidgetItem* item;
    for(unsigned int i=0;i<relation->getNbCouple();i++){
        Couple* c = relation->getCouple(i);
        QString label=c->getLabel();
        QString id1 =QString::number(c->getNote1()->getId());
        QString id2 =QString::number(c->getNote2()->getId());
        if (label == "") item = new QListWidgetItem("Note1: "+id1+" Note2: "+id2+" ",list);
        else {item = new QListWidgetItem("Note1: "+id1+" Note2: "+id2+" ("+label+")",list);};
    }

}

void RelationEditeur::supprimerCouple(){
    QListWidgetItem* item = list->currentItem();
    QString id1 = item->text().section(" ",1,1);
    QString id2 = item->text().section(" ",3,3);
    unsigned int id1int = id1.toInt();
    unsigned int id2int = id2.toInt();
    for (unsigned int i=0; i<relation->getNbCouple();i++){
        if (relation->getCouple(i)->getNote1()->getId() == id1int && relation->getCouple(i)->getNote2()->getId() == id2int){
            relation->removeCouple(relation->getCouple(i)->getLabel(),relation->getCouple(i)->getNote1(),relation->getCouple(i)->getNote2());
        }
    }
    setList();
}

void RelationEditeur::modifierLabel(){
    QListWidgetItem* item = list->currentItem();
    QString id1 = item->text().section(" ",1,1);
    QString id2 = item->text().section(" ",3,3);
    unsigned int id1int = id1.toInt();
    unsigned int id2int = id2.toInt();
    labelEditeur* l = new labelEditeur(relation->getCouple(id1int,id2int));
    l->show();
    modifier->setDisabled(true);
    setList();
}

void RelationEditeur::addCouple(){
    relation->getNewCouple();
    rafraichir->setDisabled(false);
}

void RelationEditeur::afficherBoutons(){
    supprimer->setDisabled(false);
    modifier->setDisabled(false);
}

void RelationEditeur::afficherRafraichir(){
    rafraichir->setDisabled(false);
}
