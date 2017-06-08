#ifndef mainwindow_h
#define mainwindow_h

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manager.h"
#include <iostream>
#include <typeinfo>
#include "note.h"
#include <QDebug>


#endif

mainWindow::mainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::mainWindow){
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

    setNotesList();

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
    clear(ui->partiePrincipale);
    Article* a = dynamic_cast<Article*>(NotesManager::getInstance().Create("Article"));
    NotesManager::getInstance().addNote(a);
    ArticleEditeur* e = new ArticleEditeur(a,this);
    ui->partiePrincipale->addWidget(e);

}

void mainWindow::createTask(){
    clear(ui->partiePrincipale);
    Task* a = dynamic_cast<Task*>(NotesManager::getInstance().Create("Task"));
    NotesManager::getInstance().addNote(a);
    TaskEditeur* e = new TaskEditeur(a,this);
    ui->partiePrincipale->addWidget(e);

}

void mainWindow::createImage(){
    clear(ui->partiePrincipale);
    Image* a = dynamic_cast<Image*>(NotesManager::getInstance().Create("Image"));
    NotesManager::getInstance().addNote(a);
    ImageEditeur* e = new ImageEditeur(a,this);
    ui->partiePrincipale->addWidget(e);

}

void mainWindow::createAudio(){
    clear(ui->partiePrincipale);
    Audio* a = dynamic_cast<Audio*>(NotesManager::getInstance().Create("Audio"));
    NotesManager::getInstance().addNote(a);
    AudioEditeur* e = new AudioEditeur(a,this);
    ui->partiePrincipale->addWidget(e);

}

void mainWindow::createVideo(){
    clear(ui->partiePrincipale);
    Video* a = dynamic_cast<Video*>(NotesManager::getInstance().Create("Video"));
    NotesManager::getInstance().addNote(a);
    VideoEditeur* e = new VideoEditeur(a,this);
    ui->partiePrincipale->addWidget(e);

}



void mainWindow::clear(QLayout *layout){
    QLayoutItem *child;
    while( (child = layout->takeAt( 0 )) ){
        layout->removeItem( child );
        delete child->widget();
        delete child;
     }
}

void mainWindow::setNotesList(){

    ui->listWidgetNotesActives->clear();
    QListWidgetItem *item;
    NotesManager &nm = NotesManager::getInstance();
    Task *task_type = new Task();

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
    qDebug()<<"y a avait" << j <<"notes non archivées dans le tableau";
}


