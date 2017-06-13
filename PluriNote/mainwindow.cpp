#ifndef mainwindow_h
#define mainwindow_h

#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "manager.h"
#include <iostream>
#include <typeinfo>
#include "note.h"
#include <QDebug>
#include <QSettings>


#endif

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainWindow()){
    ui->setupUi(this);

    QObject::connect(ui->actionNote, SIGNAL(triggered()), this, SLOT(createArticle()));
    QObject::connect(ui->actionTache, SIGNAL(triggered()), this, SLOT(createTask()));
    QObject::connect(ui->actionImage, SIGNAL(triggered()), this, SLOT(createImage()));
    QObject::connect(ui->actionVideo, SIGNAL(triggered()), this, SLOT(createVideo()));
    QObject::connect(ui->actionAudio, SIGNAL(triggered()), this, SLOT(createAudio()));

    QObject::connect(ui->pushButtonAudio, SIGNAL(clicked()), this, SLOT(createAudio()));
    QObject::connect(ui->pushButtonArticle, SIGNAL(clicked()), this, SLOT(createArticle()));
    QObject::connect(ui->pushButtonImage, SIGNAL(clicked()), this, SLOT(createImage()));
    QObject::connect(ui->pushButtonTask, SIGNAL(clicked()), this, SLOT(createTask()));
    QObject::connect(ui->pushButtonVideo, SIGNAL(clicked()), this, SLOT(createVideo()));

    QObject::connect(ui->listRelation, SIGNAL(itemSelectionChanged()), this, SLOT(afficherRelation()));
    QObject::connect(ui->nouvelleRelationAction,SIGNAL(triggered()), this, SLOT(createRelation()));
    QObject::connect(ui->actionafficher, SIGNAL(triggered()),this,SLOT(afficherCorbeille()));
    QObject::connect(ui->listWidgetNotesActives, SIGNAL(itemSelectionChanged()),this,SLOT( afficherNote() ));
    QObject::connect(ui->listWidgetTasksActives, SIGNAL(itemSelectionChanged()),this,SLOT( afficherTask() ));
    QObject::connect(ui->listWidgetArchive, SIGNAL(itemSelectionChanged()),this,SLOT( afficherArchive() ));
    //QObject::connect(ui->listRelation, SIGNAL(itemSelectionChanged()),this,SLOT(afficherReference()));
    QObject::connect(ui->actioncorbeille, SIGNAL(triggered()),this,SLOT(afficherParametreCorbeille()));
    QObject::connect(ui->actionclose,SIGNAL(triggered()), this, SLOT(quitter()));

    setNotesList();
    setRelationsList();

}

mainWindow::~mainWindow(){delete ui;}

mainWindow* mainWindow::instance =0;

mainWindow* mainWindow::getInstance(){
    if (!instance) instance = new mainWindow();
    return instance;
}

void mainWindow::libererInstance(){
    if (instance) delete instance;
    instance = nullptr;
}

void mainWindow::createArticle(){
    clear();
    Article* a = dynamic_cast<Article*>(NotesManager::getInstance().Create("Article"));
    NotesManager::getInstance().addNote(a);
    ArticleEditeur* e = new ArticleEditeur(a,this);
    ui->partiePrincipale->addWidget(e);

}


void mainWindow::createTask(){
    clear();
    Task* a = dynamic_cast<Task*>(NotesManager::getInstance().Create("Task"));
    NotesManager::getInstance().addNote(a);
    TaskEditeur* e = new TaskEditeur(a,this);
    ui->partiePrincipale->addWidget(e);

}

void mainWindow::createImage(){
    clear();
    Image* a = dynamic_cast<Image*>(NotesManager::getInstance().Create("Image"));
    NotesManager::getInstance().addNote(a);
    ImageEditeur* e = new ImageEditeur(a,this);
    ui->partiePrincipale->addWidget(e);

}

void mainWindow::createAudio(){
    clear();
    Audio* a = dynamic_cast<Audio*>(NotesManager::getInstance().Create("Audio"));
    NotesManager::getInstance().addNote(a);
    AudioEditeur* e = new AudioEditeur(a,this);
    ui->partiePrincipale->addWidget(e);

}

void mainWindow::createVideo(){
    clear();
    Video* a = dynamic_cast<Video*>(NotesManager::getInstance().Create("Video"));
    NotesManager::getInstance().addNote(a);
    VideoEditeur* e = new VideoEditeur(a,this);
    ui->partiePrincipale->addWidget(e);

}



void mainWindow::clear(){
    QLayoutItem *item;
    while ((item = ui->partiePrincipale->takeAt(0)) != 0) {
        item->widget()->deleteLater();
        delete item;
    }
}

void mainWindow::setNotesList(){

    ui->listWidgetNotesActives->clear();
    ui->listWidgetArchive->clear();
    ui->listWidgetTasksActives->clear();

    QListWidgetItem *item;
    NotesManager &nm = NotesManager::getInstance();



    for (unsigned int i=0;i<nm.getNbNote();i++){
        Note *n = nm.getNote(i);

        Reference::getInstance()->chercherReference();
        /// On met le tableau de référence à zéro et on le reconstruit pour obtenir les références réelles
        ///Si une note archivée n'est plus référencée par une note x (cas où x vient d'être supprimée), alors
        /// la note archivée ne l'est plus et on modifie la valeur de l'attribut archive et on la met dans la corbeille
        if (n->GetArchive()){
            n->setArchive(Reference::getInstance()->checkIfInReference(n));
            if ( n->GetArchive() == false ) { /// Si une note passe d'un état archivé à non archivé, on propose à l'utilisateur
                ///de la la supprimer car
                ///ça signifie que la note qui la référençait a été supprimé, il n'y a plus de
                /// raisons de la garder dans les archives
                ArchiveFenetreEditeur* fenetre = new ArchiveFenetreEditeur(n,this);
                fenetre->show();
            }
        }
    }

    for (unsigned int i=0;i<nm.getNbNote();i++){
        Note *n = nm.getNote(i);

        if (!n -> GetArchive()){
            if (n->getType() == "Task"){
                item= new QListWidgetItem(n->setNotesListNote(),ui->listWidgetTasksActives);
            }
            else{
                item = new QListWidgetItem(n->setNotesListNote(),ui->listWidgetNotesActives);
            }
        }
        else{
            item =  new QListWidgetItem(n->setNotesListNote(),ui->listWidgetArchive);
        }

    }
}

void mainWindow::setRelationsList(){
    QListWidgetItem *item;

    ui->listRelation->clear();

    item = new QListWidgetItem(Reference::getInstance()->getTitle(),ui->listRelation);

    for (unsigned int i=0; i<RelationsManager::getInstance().getNbRelation(); i++){
        Relation& relation = RelationsManager::getInstance().getRelation(i);
        item = new QListWidgetItem(relation.getTitle(),ui->listRelation);
    }
}


void mainWindow::afficherRelation(){
    clear();

    QListWidgetItem* item = ui->listRelation->currentItem();

    QString title = item->text();

    if (title == "Référence"){
        Reference::getInstance()->chercherReference();
        ReferenceEditeur* reference = new ReferenceEditeur(Reference::getInstance());
        ui->partiePrincipale->addWidget(reference);
    }
    else{
        Relation& relation = RelationsManager::getInstance().getRelation(title);
        RelationEditeur* r = new RelationEditeur(&relation);
        ui->partiePrincipale->addWidget(r);
    }
}

void mainWindow::createRelation(){
    Relation& relation = RelationsManager::getInstance().getNewRelation("","");
    labelRelationEditeur* editeur = new labelRelationEditeur(&relation);
    editeur->show();
}

void mainWindow::afficherCorbeille(){
    CorbeilleEditeur* corbeille = new CorbeilleEditeur(&Corbeille::getInstance());
    corbeille->show();
}

void mainWindow::afficherNote(){
    QListWidgetItem* item = ui->listWidgetNotesActives->currentItem();
    unsigned int id =  item->text().section(" ",1,1).toInt();
    for (NotesManager::iterator it = NotesManager::getInstance().begin(); it != NotesManager::getInstance().end() ; ++it){
        if (it.value()->getId() == id ){
            clear();
            it.value()->editNote();
        }
    }
}


void mainWindow::afficherTask(){

    QListWidgetItem* item = ui->listWidgetTasksActives->currentItem();
    unsigned int id =  item->text().section(" ",1,1).toInt();

    for (NotesManager::iterator it = NotesManager::getInstance().begin(); it != NotesManager::getInstance().end() ; ++it){
        if (it.value()->getId() == id ){
            clear();
            it.value()->editNote();
        }
    }
}


void mainWindow::afficherArchive(){

    QListWidgetItem* item = ui->listWidgetArchive->currentItem();
    unsigned int id =  item->text().section(" ",1,1).toInt();

    for (NotesManager::iterator it = NotesManager::getInstance().begin(); it != NotesManager::getInstance().end() ; ++it){
        if (it.value()->getId() == id ){
            clear();
            it.value()->editNote();
        }
    }
}

void mainWindow::afficherParametreCorbeille(){
    ParametreCorbeille* parametres = new ParametreCorbeille();
    parametres->show();
}

void mainWindow::quitter(){
    QSettings settings("loickwpj","pluriNote");
    if(settings.value("viderCorbeilleAuto").toBool()){
        Corbeille::getInstance().deleteAll();
        this->close();
    }
    else{
        QuitterApp* quitter = new QuitterApp();
        quitter->show();

    }
}
