#ifndef corbeilleediteur_cpp
#define corbeilleediteur_cpp
#include "corbeilleediteur.h"
#include <QDebug>
#include<QMessageBox>
#endif

CorbeilleEditeur::CorbeilleEditeur( Corbeille* c, QWidget *) : corbeille(c){
    list = new QListWidget();
    layout = new QVBoxLayout();
    scroller = new QScrollArea();
    vider = new QPushButton("Vider la Corbeille");
    restaurer = new QPushButton("Restaurer");

    restaurer->setDisabled(true);

    scroller->setWidget(list);
    layout->addWidget(scroller);
    layout->addWidget(vider);
    layout->addWidget(restaurer);

    setList();

    setLayout(layout);

    QObject::connect(vider, SIGNAL(clicked()), this, SLOT(viderCorbeille()));
    QObject::connect(restaurer, SIGNAL(clicked()), this, SLOT(restaurerNote()));
    QObject::connect(list, SIGNAL(itemSelectionChanged()), this, SLOT(afficherBoutons()));

}

void CorbeilleEditeur::afficherBoutons(){restaurer->setDisabled(false);}

void CorbeilleEditeur::viderCorbeille(){
    Corbeille::getInstance().deleteAll();
    list->clear();
}

void CorbeilleEditeur::setList(){
    list->clear();
    QListWidgetItem* item;
    for(unsigned int i=0;i<Corbeille::getInstance().getNbNote();i++){
        Note* n = Corbeille::getInstance().getNote(i);
        QString id =QString::number(n->getId());
        QString title = n->getTitle();
        QString titre =id+"-"+title;
        item = new QListWidgetItem(titre,list);
    }
}


void CorbeilleEditeur::restaurerNote(){
   // if(!list->currentItem() == 0){
        QListWidgetItem* item = list->currentItem();
        QString id = item->text().section("-",0,0);
        unsigned int idint = id.toInt();
        //Note* n = NoteManager::getNoteManager().getNoteWithTitle(titleNote, "Trash");
        //Note* n = Corbeille::getInstance().getNote(id.toInt());
        Corbeille::getInstance().restaurer(idint);
        QMessageBox::information(this, "Restauration", "Note restaurée !");
        list->takeItem(list->currentRow());
        setList();
   // }
   // throw NotesException("ERROR");
}





