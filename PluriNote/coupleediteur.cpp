#ifndef coupleediteur_cpp
#define coupleediteur_cpp

#include <QMessageBox>
#include <QDebug>

#include "coupleediteur.h"
//#inclde "manager.h"

#endif

CoupleEditeur::CoupleEditeur(Couple* c, QWidget *) : couple(c){

    note1 = new QListWidget();
    note2 = new QListWidget();
    note1l = new QLabel ("Note 1 :");
    note2l = new QLabel ("Note 2 :");
    labell = new QLabel("Label :");
    note1Layout = new QVBoxLayout;
    note2Layout = new QVBoxLayout;
    notes = new QHBoxLayout;
    label = new QHBoxLayout;
    layout = new QVBoxLayout;
    labelEdit = new QLineEdit;
    sauver = new QPushButton("sauver");
    scroll1 = new QScrollArea;
    scroll2 = new QScrollArea;


    scroll1->setWidget(note1);
    scroll2->setWidget(note2);


    note1Layout->addWidget(note1l);
    note1Layout->addWidget(note1);
    note2Layout->addWidget(note2l);
    note2Layout->addWidget(note2);
    label->addWidget(labell);
    label->addWidget(labelEdit);

    notes->addLayout(note1Layout);
    notes->addLayout(note2Layout);

    layout->addLayout(notes);
    layout->addLayout(label);
    layout->addWidget(sauver);

    setList1();
    setList2();

    setLayout(layout);

    sauver->setDisabled(true);
    labelEdit->setDisabled(true);


    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(saveModifications()));
    QObject::connect(labelEdit,SIGNAL(textChanged(QString)),this,SLOT(afficherBouton()));
    QObject::connect(note2,SIGNAL(itemSelectionChanged()),this,SLOT(afficherLabel1()));
    QObject::connect(note2,SIGNAL(itemSelectionChanged()),this,SLOT(afficherLabel2()));

}


void CoupleEditeur::afficherBouton(){
    sauver->setDisabled(false);
}

void CoupleEditeur::afficherLabel1(){
    if (note1->currentItem()->isSelected()) labelEdit->setDisabled(false);
}

void CoupleEditeur::afficherLabel2(){
    if (note2->currentItem()->isSelected()) labelEdit->setDisabled(false);
}

void CoupleEditeur::saveModifications(){


    couple->setLabel(labelEdit->text());
    QString id1 = note1->currentItem()->text().section("-",0,0);
    unsigned int idint1 = id1.toInt();
    QString id2 = note2->currentItem()->text().section("-",0,0);
    unsigned int idint2 = id2.toInt();

    ///On accepte qu'une note soit en relation avec elle-même (exemple : une note peut être en relation
    ///avec une de ses parties qui sera transmise en label )

    Note* n1;
    Note* n2;
    for (unsigned int i =0; i<NotesManager::getInstance().getNbNote();i++){
        if (NotesManager::getInstance().getNote(i)->getId() == idint1) n1 = NotesManager::getInstance().getNote(i);
        if (NotesManager::getInstance().getNote(i)->getId() == idint2) n2 = NotesManager::getInstance().getNote(i);
    }

    couple->setNote1(n1);
    couple->setNote2(n2);
    RelationsManager::getInstance().saveRelation();
    QMessageBox::information(this, "Sauvegarde","Le couple a été enregistré !");
    close();
}

void CoupleEditeur::setList1(){
    note1->clear();
    QListWidgetItem* item;
    for(unsigned int i=0;i<NotesManager::getInstance().getNbNote();i++){
        Note* n = NotesManager::getInstance().getNote(i);
        QString id =QString::number(n->getId());
        QString title = n->getTitle();
        QString titre =id+"-"+title;

        item = new QListWidgetItem(titre,note1);
    }
}


void CoupleEditeur::setList2(){
    note2->clear();
    QListWidgetItem* item;
    for(unsigned int i=0;i<NotesManager::getInstance().getNbNote();i++){
        Note* n = NotesManager::getInstance().getNote(i);
        QString id =QString::number(n->getId());
        QString title = n->getTitle();
        QString titre =id+"-"+title;
        item = new QListWidgetItem(titre,note2);
    }
}

