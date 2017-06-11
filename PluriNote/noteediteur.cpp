#ifndef noteediteur_cpp
#define noteediteur_cpp

#include "noteediteur.h"
#include <QMessageBox>
#include <QDebug>



#endif
/*********************************************************************
 ***                       Note Editeur                             **
 *********************************************************************/

NoteEditeur::NoteEditeur(QWidget *){
    formulaire = new QFormLayout;
    layout = new QVBoxLayout;

    id = new QLineEdit(this);
    title = new QLineEdit(this);
    dateC = new QDateEdit(this);
    dateM = new QDateEdit(this);
    sauver = new QPushButton("sauver",this);
    bsupprimer = new QPushButton("supprimer",this);
    ///MEMENTO CREATION DU BOUTON
    bprevious = new QPushButton("previous Version", this);


    formulaire->addRow("Identificateur :", id);
    formulaire->addRow("Titre :", title);
    formulaire->addRow("Date de création :", dateC);
    formulaire->addRow("Date de dernière modification :", dateM);


    layout = new QVBoxLayout;
    layout->addLayout(formulaire);
    //layout->addWidget(sauver);
    //layout->addWidget(bsupprimer);


    id->setDisabled(true);
    sauver->setDisabled(true);
    dateC->setDisabled(true);
    dateM->setDisabled(true);


}

void NoteEditeur::afficherBouton(QString){
    sauver->setDisabled(false);
}

void NoteEditeur::afficherBouton(int){
    sauver->setDisabled(false);
}

void NoteEditeur::afficherBouton(QDate){
    sauver->setDisabled(false);
}


/*********************************************************************/



/*********************************************************************
 ***                      Article Editeur                           **
 *********************************************************************/
ArticleEditeur::ArticleEditeur(Article* a, QWidget *parent) : NoteEditeur(parent), article(a){
    ///MEMENTO CONDITION A CHECK
    if(article->getNbmemento()>0)
    {bprevious->setDisabled(false);}
    else
        bprevious->setDisabled(true);

    text = new QLineEdit(this);
    formulaire->addRow("Texte :", text);

    dateC->setDate(a->getDateC());
    dateM->setDate(a->getDateM());
    id->setText(QString::number(a->getId()));
    title->setText(a->getTitle());
    text->setText(a->getText());


    layout->addWidget(sauver);
    layout->addWidget(bsupprimer);
    ///MEMENTO APPARITION DU BOUTON
    layout->addWidget(bprevious);

    setLayout(layout);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(saveModifications()));
    QObject::connect(title , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(text , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(bsupprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
    ///MEMENTO CONNECT
    QObject::connect(bprevious, SIGNAL(clicked()), this, SLOT(previousVersion()));

    if (article->GetArchive()){
        title->setDisabled(true);
        text->setDisabled(true);
        bsupprimer->setDisabled(true);
        bprevious->setDisabled(true);

    }
}


void ArticleEditeur::saveModifications(){
    ///MEMENTO ADD
    article->addMemento();

    article->setTitle(title->text());
    article->setText(text->text());
    article->setDateLastModification();

    qDebug()<<"nb memento après save= "<< article->getNbmemento();
    sauver->setDisabled(true);
    ///MEMENTO APPARITION DU BOUTON APRES SAVE
    bprevious->setDisabled(false);
    if (NotesManager::getInstance().getFilename() !="tmp.dat") NotesManager::getInstance().save();

    Reference::getInstance()->chercherReference();

    mainWindow::getInstance()->setNotesList();

    QMessageBox::information(this, "Sauvegarde", "Article sauvegardé !");
}


void ArticleEditeur::supprimer(){

    if (Reference::getInstance()->checkIfInReference( article )){
        article->setArchive();
        QMessageBox::information(this, "Archivage", "Article archivé !");
    }
    else{
        Singleton<Corbeille>::getInstance().addNoteCorbeille(article);
        Singleton<NotesManager>::getInstance().supprimerNote(article->getId());
        QMessageBox::information(this, "Suppression", "Article supprimé !");
        CorbeilleEditeur* c = new CorbeilleEditeur (&(Corbeille::getInstance()));
        RelationsManager::getInstance().chercherCouple(article);
        c->show();
    }
    mainWindow::getInstance()->setNotesList();
    this->close();
}


///MEMENTO METHOD REDEFINI
void ArticleEditeur::previousVersion(){
    ArticleEditeur* aE = new ArticleEditeur((article->getPreviousMemento()));
    QMessageBox::information(this, "update", "Version précédente mise à jour !");
    if(article->getNbmemento()>0)
        {bprevious->setDisabled(false);}
    else
        bprevious->setDisabled(true);
    aE->show();
    this->close();
}

/*********************************************************************
 ***                         Task Editeur                           **
 *********************************************************************/
TaskEditeur::TaskEditeur(Task* t, QWidget *parent) : NoteEditeur(parent), task(t) {
    ///MEMENTO CONDITION CHECK
    if(task->getNbmemento()>0)
    {bprevious->setDisabled(false);}
    else
        bprevious->setDisabled(true);

    state = new QComboBox;
    state->addItem("Waiting");
    state->addItem("Ongoing");
    state->addItem("Done");

    action = new QLineEdit(this);
    priority = new QSpinBox(this);
    deadline = new QDateEdit(this);
    //state = new QLineEdit(this);
    priorite = new QCheckBox("priorité");
    bdeadline = new QCheckBox("deadline");
    option = new QGroupBox("Options",this);
    lay = new QHBoxLayout;

    priority->setMaximum(5);
    priority->setMinimum(0);
    //priority->setValue(0);

    formulaire->addRow("Texte :", action);
    formulaire->addRow("Priorité :", priority);
    formulaire->addRow("Deadline :", deadline);
    formulaire->addRow("Etat :", state);

    deadline->setDisabled(true);
    priority->setDisabled(true);

    lay->addWidget(priorite);
    lay->addWidget(bdeadline);
    option->setLayout(lay);


    dateC->setDate(t->getDateC());
    dateM->setDate(t->getDateM());
    id->setText(QString::number(t->getId()));
    title->setText(t->getTitle());
    action->setText(t->getAction());
    priority->setValue(t->getPriority());
    deadline->setDate(t->getDeadline());
    state->setCurrentText(toString(t->getState()));

    layout->addWidget(option);
    layout->addWidget(sauver);
    layout->addWidget(bsupprimer);
    ///MEMENTO AJOUT DU BOUTON
    layout->addWidget(bprevious);
    setLayout(layout);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(saveModifications()));
    QObject::connect(title , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(action , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(priority , SIGNAL(valueChanged(int)), this, SLOT(afficherBouton(int)));
    QObject::connect(deadline , SIGNAL(dateChanged(QDate)), this, SLOT(afficherBouton(QDate)));
    QObject::connect(state,SIGNAL(currentIndexChanged(QString)),this,SLOT(afficherBouton(QString)));
    QObject::connect(bsupprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
    QObject::connect(bdeadline,SIGNAL(clicked()), this, SLOT(afficherDeadline()));
    QObject::connect(priorite,SIGNAL(clicked()), this, SLOT(afficherPriorite()));
    ///MEMENTO CONNECT
    QObject::connect(bprevious, SIGNAL(clicked()), this, SLOT(previousVersion()));

    if (task->GetArchive()){
        title->setDisabled(true);
        action->setDisabled(true);
        priorite->setDisabled(true);
        bdeadline->setDisabled(true);
        bsupprimer->setDisabled(true);
        state->setDisabled(true);
        bprevious->setDisabled(true);
    }


}
void TaskEditeur::saveModifications(){
    ///MEMENTO ADD MEMENTO
    task->addMemento();

    task->setTitle(title->text());
    task->setAction(action->text());
    task->setPriority(priority->value());
    task->setDateLastModification();
    task->setDeadline(deadline->date());
    task->setState(state->currentText());
    //task->setDeadline(deadline->text().t);

    if (NotesManager::getInstance().getFilename() !="tmp.dat") NotesManager::getInstance().save();

        Reference::getInstance()->chercherReference();

        mainWindow::getInstance()->setNotesList();

    QMessageBox::information(this, "Sauvegarde", "Tâche sauvegardée !");
    sauver->setDisabled(true);
    ///MEMENTO AFFICHAGE DU BOUTON
    bprevious->setDisabled(false);
}

void TaskEditeur::supprimer(){
    if (Reference::getInstance()->checkIfInReference( task )){
        task->setArchive();
        QMessageBox::information(this, "Archivage", "Tâche archivée !");
    }
    else{
        Singleton<Corbeille>::getInstance().addNoteCorbeille(task);
        Singleton<NotesManager>::getInstance().supprimerNote(task->getId());
        QMessageBox::information(this, "Suppression", "Article supprimé !");
        CorbeilleEditeur* c = new CorbeilleEditeur (&(Corbeille::getInstance()));
        RelationsManager::getInstance().chercherCouple(task);
        c->show();
    }

    mainWindow::getInstance()->setNotesList();
    this->close();
}

void TaskEditeur::afficherDeadline(){
    if (bdeadline->isChecked()) deadline->setDisabled(false);
    else {
        deadline->setDisabled(true);
        deadline->setDate(dateC->date());
    }
}

void TaskEditeur::afficherPriorite(){
    if(priorite->isChecked()) priority->setDisabled(false);
    else {
        priority->setDisabled(true);
        priority->setValue(0);
    }
}

///MEMENTO METHOD REDEFINI
void TaskEditeur::previousVersion(){
    TaskEditeur* E = new TaskEditeur((task->getPreviousMemento()));
    QMessageBox::information(this, "update", "Version précédente mise à jour !");
    if(task->getNbmemento()>0)
        bprevious->setDisabled(false);
    else
        bprevious->setDisabled(true);
    E->show();
    this->close();
}


/*********************************************************************/




/********************************************************************
**                     Multimedia Editeur                          **
*********************************************************************/

MultimediaEditeur::MultimediaEditeur(QWidget*parent) : NoteEditeur(parent) {

    description = new QLineEdit(this);
    image = new QLineEdit(this);

    formulaire->addRow("Description :", description);
    formulaire->addRow("Image :", image);

}


/*********************************************************************/



/********************************************************************
***                          Image Editeur                         **
*********************************************************************/

ImageEditeur::ImageEditeur(Image*i, QWidget*parent) : MultimediaEditeur(parent), fichierImage(i) {
    ///MEMENTO CONDITION A CHECK
    if(fichierImage->getNbmemento()>0)
    {bprevious->setDisabled(false);}
    else
        bprevious->setDisabled(true);

    sauver->setDisabled(true);
    layout->addWidget(sauver);
    layout->addWidget(bsupprimer);
    ///MEMENTO AJOUT DU BOUTON
    layout->addWidget(bprevious);
    setLayout(layout);

    id->setText(QString::number(fichierImage->getId()));
    dateC->setDate(fichierImage->getDateC());
    title->setText(fichierImage->getTitle());
    description->setText(fichierImage->getDescription());
    image->setText(fichierImage->getImage());

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(saveModifications()));
    QObject::connect(title , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(description, SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(image, SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(bsupprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
    ///MEMENTO CONNECT
    QObject::connect(bprevious, SIGNAL(clicked()), this, SLOT(previousVersion()));


    if (fichierImage->GetArchive()){
        title->setDisabled(true);
        description->setDisabled(true);
        bsupprimer->setDisabled(true);
        bprevious->setDisabled(true);
    }

}

void ImageEditeur::saveModifications(){
    ///MEMENTO ADD
    fichierImage->addMemento();


    fichierImage->setDateLastModification();
    fichierImage->setTitle(title->text());
    fichierImage->setDescription(description->text());
    fichierImage->setImage(image->text());

    if (NotesManager::getInstance().getFilename() !="tmp.dat") NotesManager::getInstance().save();

    Reference::getInstance()->chercherReference();

    mainWindow::getInstance()->setNotesList();

    QMessageBox::information(this, "Sauvegarde", "Image sauvegardée !");
    sauver->setDisabled(true);
    ///MEMENTO APPARITION BOUTON
    bprevious->setDisabled(false);
}

void ImageEditeur::supprimer(){
    if (Reference::getInstance()->checkIfInReference( fichierImage )){
        fichierImage->setArchive();
        QMessageBox::information(this, "Archivage", "Image archivée !");
    }
    else{
        Corbeille::getInstance().addNoteCorbeille(fichierImage);
        NotesManager::getInstance().supprimerNote(fichierImage->getId());
        QMessageBox::information(this, "Suppression", "Article supprimé !");
        CorbeilleEditeur* c = new CorbeilleEditeur (&(Corbeille::getInstance()));
        RelationsManager::getInstance().chercherCouple(fichierImage);
        c->show();
    }
    mainWindow::getInstance()->setNotesList();
    this->close();
}

///MEMENTO METHOD REDEFINI
void ImageEditeur::previousVersion(){
    ImageEditeur* E = new ImageEditeur((fichierImage->getPreviousMemento()));
    QMessageBox::information(this, "update", "Version précédente mise à jour !");
    if(fichierImage->getNbmemento()>0)
        bprevious->setDisabled(false);
    else
        bprevious->setDisabled(true);
    E->show();
    this->close();
}

/*********************************************************************/


/*********************************************************************/



/********************************************************************
***                          Video Editeur                         **
*********************************************************************/

VideoEditeur::VideoEditeur(Video*i, QWidget*parent) : MultimediaEditeur(parent), fichierVideo(i) {
    ///MEMENTO CONDITION CHECK
    if(fichierVideo->getNbmemento()>0)
    {bprevious->setDisabled(false);}
    else
        bprevious->setDisabled(true);
    sauver->setDisabled(true);
    layout->addWidget(sauver);
    layout->addWidget(bsupprimer);
    ///MEMENTO ADD LAYOUT
    layout->addWidget(bprevious);

    setLayout(layout);

    id->setText(QString::number(fichierVideo->getId()));
    dateC->setDate(fichierVideo->getDateC());
    title->setText(fichierVideo->getTitle());
    description->setText(fichierVideo->getDescription());
    image->setText(fichierVideo->getImage());

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(saveModifications()));
    QObject::connect(title , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(description, SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(image, SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(bsupprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
    ///MEMENTO CONNECT
    QObject::connect(bprevious, SIGNAL(clicked()), this, SLOT(previousVersion()));

    if (fichierVideo->GetArchive()){
        title->setDisabled(true);
        description->setDisabled(true);
        bsupprimer->setDisabled(true);
        bprevious->setDisabled(true);
    }
}

void VideoEditeur::saveModifications(){
    ///MEMENTO ADD
    fichierVideo->addMemento();

    fichierVideo->setDateLastModification();
    fichierVideo->setTitle(title->text());
    fichierVideo->setDescription(description->text());
    fichierVideo->setImage(image->text());

    if (NotesManager::getInstance().getFilename() !="tmp.dat") NotesManager::getInstance().save();

    Reference::getInstance()->chercherReference();

    mainWindow::getInstance()->setNotesList();

    //task->setDeadline(deadline->text().t);
    QMessageBox::information(this, "Sauvegarde", "Vidéo sauvegardée !");
    sauver->setDisabled(true);
    ///MEMENTO APPARITION DU BOUTON
    bprevious->setDisabled(false);
}

void VideoEditeur::supprimer(){
    if (Reference::getInstance()->checkIfInReference( fichierVideo )){
        fichierVideo->setArchive();
        QMessageBox::information(this, "Archivage", "Image archivée !");
    }
    else{
        Corbeille::getInstance().addNoteCorbeille(fichierVideo);
        NotesManager::getInstance().supprimerNote(fichierVideo->getId());
        QMessageBox::information(this, "Suppression", "Article supprimé !");
        CorbeilleEditeur* c = new CorbeilleEditeur (&(Corbeille::getInstance()));
        RelationsManager::getInstance().chercherCouple(fichierVideo);
        c->show();
    }

    mainWindow::getInstance()->setNotesList();
    this->close();
}

/// MEMENTO METHOD REDEFINI
void VideoEditeur::previousVersion(){
    VideoEditeur* E = new VideoEditeur((fichierVideo->getPreviousMemento()));
    QMessageBox::information(this, "update", "Version précédente mise à jour !");
    if(fichierVideo->getNbmemento()>0)
        bprevious->setDisabled(false);
    else
        bprevious->setDisabled(true);
    E->show();
    this->close();
}


/*********************************************************************/



/********************************************************************
***                          Audio Editeur                         **
*********************************************************************/

AudioEditeur::AudioEditeur(Audio*i, QWidget*parent) : MultimediaEditeur(parent), fichierAudio(i) {

    //sauver->setDisabled(true);
    ///MEMENTO CONDITION A CHECK
    if(fichierAudio->getNbmemento()>0)
    {bprevious->setDisabled(false);}
    else
        bprevious->setDisabled(true);

    layout->addWidget(sauver);
    layout->addWidget(bsupprimer);
    ///MEMENTO ADD WIDGET
    layout->addWidget(bprevious);
    setLayout(layout);

    id->setText(QString::number(fichierAudio->getId()));
    dateC->setDate(fichierAudio->getDateC());
    title->setText(fichierAudio->getTitle());
    description->setText(fichierAudio->getDescription());
    image->setText(fichierAudio->getImage());

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(saveModifications()));
    QObject::connect(title , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(description, SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(image, SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(bsupprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
    ///MEMENTO CONNEXION
    QObject::connect(bprevious, SIGNAL(clicked()), this, SLOT(previousVersion()));

    if (fichierAudio->GetArchive()){
        title->setDisabled(true);
        description->setDisabled(true);
        bsupprimer->setDisabled(true);
        bprevious->setDisabled(true);
    }
}

void AudioEditeur::saveModifications(){
    ///MEMENTO ADD
    fichierAudio->addMemento();

    fichierAudio->setDateLastModification();
    fichierAudio->setTitle(title->text());
    fichierAudio->setDescription(description->text());
    fichierAudio->setImage(image->text());

    if (NotesManager::getInstance().getFilename() !="tmp.dat") NotesManager::getInstance().save();

    Reference::getInstance()->chercherReference();

    mainWindow::getInstance()->setNotesList();

    //task->setDeadline(deadline->text().t);
    QMessageBox::information(this, "Sauvegarde", "Audio sauvegardé !");
    sauver->setDisabled(true);
    ///MEMENTO APPARITION BOUTON
    bprevious->setDisabled(false);
}

void AudioEditeur::supprimer(){
    if (Reference::getInstance()->checkIfInReference( fichierAudio )){
        fichierAudio->setArchive();
        QMessageBox::information(this, "Archivage", "Audio archivé !");
    }
    else{
        Corbeille::getInstance().addNoteCorbeille(fichierAudio);
        NotesManager::getInstance().supprimerNote(fichierAudio->getId());
        QMessageBox::information(this, "Suppression", "Article supprimé !");
        CorbeilleEditeur* c = new CorbeilleEditeur (&(Corbeille::getInstance()));
        RelationsManager::getInstance().chercherCouple(fichierAudio);
        c->show();
    }

    mainWindow::getInstance()->setNotesList();
    this->close();
}

///MEMENTO METHOD REDEFINI

void AudioEditeur::previousVersion(){
    AudioEditeur* E = new AudioEditeur((fichierAudio->getPreviousMemento()));
    QMessageBox::information(this, "update", "Version précédente mise à jour !");
    if(fichierAudio->getNbmemento()>0)
        bprevious->setDisabled(false);
    else
        bprevious->setDisabled(true);
    E->show();
    this->close();
}

