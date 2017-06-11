#ifndef mainwindow_h
#define mainwindow_h

#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "manager.h"
#include <iostream>
#include <typeinfo>
#include "note.h"
#include <QDebug>


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


    setNotesList();
    setRelationsList();

}

mainWindow::~mainWindow()
{
    delete ui;
}

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

/*    Task *task_type = new Task();

    unsigned int j;
    for (unsigned int i=0;i<nm.getNbNote();i++){
        Note *n = nm.getNote(i);
        //note non archive
        if(!n->GetArchive()){
            //ce n'est pas une tache
            if((typeid(*n).name()!=typeid(*task_type).name()))
            {//qDebug()<<"on ajoute la note non archive did" << id <<"a la list";
                item = new QListWidgetItem(n->setNotesListNote(),ui->listWidgetNotesActives);
            }
            //c'est une tache
            else
                item= new QListWidgetItem(n->setNotesListNote(),ui->listWidgetTasksActives);
        }
        //note archive
        else
            item =  new QListWidgetItem(n->setNotesListNote(),ui->listWidgetArchive);


        j=i+1;
    }
    //qDebug()<<"y a avait" << j <<"notes non archivées dans le tableau";*/

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
    //clear(ui->listRelationLayout);
    for (unsigned int i=0; i<RelationsManager::getInstance().getNbRelation(); i++){
        Relation& relation = RelationsManager::getInstance().getRelation(i);
        qDebug()<< relation.getTitle();
        qDebug()<<RelationsManager::getInstance().getRelation(0).getTitle();
        item = new QListWidgetItem(relation.getTitle(),ui->listRelation);
    }
}


void mainWindow::afficherRelation(){
    clear();
    QListWidgetItem* item = ui->listRelation->currentItem();
    QString title = item->text();
    if (title == "Référence"){ ReferenceEditeur* reference = new ReferenceEditeur(Reference::getInstance());
        ui->partiePrincipale->addWidget(reference);}
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


