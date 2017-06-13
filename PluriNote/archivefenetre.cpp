#include "archivefenetre.h"



ArchiveFenetreEditeur::ArchiveFenetreEditeur(Note* n, QWidget*) : note(n) {

    question = new QLabel("Voulez-vous supprimer de manière définitive la note "+QString::number(note->getId())+" ?");
    layout = new QVBoxLayout;
    reponses = new QHBoxLayout;
    oui = new QPushButton("Oui");
    non = new QPushButton ("Non");

    reponses->addWidget(oui);
    reponses->addWidget(non);

    layout->addWidget(question);
    layout->addLayout(reponses);

    setLayout(layout);


    QObject::connect(oui,SIGNAL(clicked()),this,SLOT(clickOnOui()));
    QObject::connect(non,SIGNAL(clicked()),this,SLOT(clickOnNon()));

};

void ArchiveFenetreEditeur::clickOnOui(){
    Singleton<Corbeille>::getInstance().addNoteCorbeille(note);
    Singleton<NotesManager>::getInstance().supprimerNote(note->getId());
    mainWindow::getInstance()->setNotesList();
    this->close();
}

void ArchiveFenetreEditeur::clickOnNon(){
    this->close();
}
