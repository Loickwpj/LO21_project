#ifndef noteediteur_cpp
#define noteediteur_cpp

#include "noteediteur.h"
#include <QMessageBox>
#include <QDebug>
#include "corbeilleediteur.h"


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
    text = new QLineEdit(this);
    formulaire->addRow("Texte :", text);

    dateC->setDate(a->getDateC());
    dateM->setDate(a->getDateM());
    id->setText(QString::number(a->getId()));
    title->setText(a->getTitle());
    text->setText(a->getText());


    layout->addWidget(sauver);
    layout->addWidget(bsupprimer);


    setLayout(layout);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(saveModifications()));
    QObject::connect(title , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(text , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(bsupprimer, SIGNAL(clicked()), this, SLOT(supprimer()));
}


void ArticleEditeur::saveModifications(){
    article->setTitle(title->text());
    article->setText(text->text());
    article->setDateLastModification();
    sauver->setDisabled(true);
    if (NotesManager::getInstance().getFilename() !="tmp.dat") NotesManager::getInstance().save();
    QMessageBox::information(this, "Sauvegarde", "Article sauvegardé !");
}


void ArticleEditeur::supprimer(){
    Singleton<Corbeille>::getInstance().addNoteCorbeille(article);
    Singleton<NotesManager>::getInstance().supprimerNote(article->getId());
    QMessageBox::information(this, "Suppression", "Article supprimé !");
    CorbeilleEditeur* c = new CorbeilleEditeur (&(Corbeille::getInstance()));
    RelationsManager::getInstance().chercherCouple(article);
    c->show();
    this->close();

}

/*********************************************************************
 ***                         Task Editeur                           **
 *********************************************************************/
TaskEditeur::TaskEditeur(Task* t, QWidget *parent) : NoteEditeur(parent), task(t) {

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
}
void TaskEditeur::saveModifications(){
    task->setTitle(title->text());
    task->setAction(action->text());
    task->setPriority(priority->value());
    task->setDateLastModification();
    task->setDeadline(deadline->date());
    task->setState(state->currentText());
    //task->setDeadline(deadline->text().t);
    QMessageBox::information(this, "Sauvegarde", "Tâche sauvegardée !");
    sauver->setDisabled(true);
}

void TaskEditeur::supprimer(){
    Singleton<Corbeille>::getInstance().addNoteCorbeille(task);
    Singleton<NotesManager>::getInstance().supprimerNote(task->getId());
    QMessageBox::information(this, "Suppression", "Article supprimé !");
    CorbeilleEditeur* c = new CorbeilleEditeur (&(Corbeille::getInstance()));
    RelationsManager::getInstance().chercherCouple(task);
    c->show();
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

    sauver->setDisabled(true);
    layout->addWidget(sauver);
    layout->addWidget(bsupprimer);
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


}

void ImageEditeur::saveModifications(){

    fichierImage->setDateLastModification();
    fichierImage->setTitle(title->text());
    fichierImage->setDescription(description->text());
    fichierImage->setImage(image->text());

    //task->setDeadline(deadline->text().t);
    QMessageBox::information(this, "Sauvegarde", "Image sauvegardée !");
    sauver->setDisabled(true);
}

void ImageEditeur::supprimer(){
    Corbeille::getInstance().addNoteCorbeille(fichierImage);
    NotesManager::getInstance().supprimerNote(fichierImage->getId());
    QMessageBox::information(this, "Suppression", "Article supprimé !");
    CorbeilleEditeur* c = new CorbeilleEditeur (&(Corbeille::getInstance()));
    RelationsManager::getInstance().chercherCouple(fichierImage);
    c->show();
    this->close();
}

/*********************************************************************/


/*********************************************************************/



/********************************************************************
***                          Video Editeur                         **
*********************************************************************/

VideoEditeur::VideoEditeur(Video*i, QWidget*parent) : MultimediaEditeur(parent), fichierVideo(i) {

    sauver->setDisabled(true);
    layout->addWidget(sauver);
    layout->addWidget(bsupprimer);
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

}

void VideoEditeur::saveModifications(){

    fichierVideo->setDateLastModification();
    fichierVideo->setTitle(title->text());
    fichierVideo->setDescription(description->text());
    fichierVideo->setImage(image->text());

    //task->setDeadline(deadline->text().t);
    QMessageBox::information(this, "Sauvegarde", "Vidéo sauvegardée !");
    sauver->setDisabled(true);
}

void VideoEditeur::supprimer(){
    Corbeille::getInstance().addNoteCorbeille(fichierVideo);
    NotesManager::getInstance().supprimerNote(fichierVideo->getId());
    QMessageBox::information(this, "Suppression", "Article supprimé !");
    CorbeilleEditeur* c = new CorbeilleEditeur (&(Corbeille::getInstance()));
    RelationsManager::getInstance().chercherCouple(fichierVideo);
    c->show();
    this->close();
}

/*********************************************************************/



/********************************************************************
***                          Audio Editeur                         **
*********************************************************************/

AudioEditeur::AudioEditeur(Audio*i, QWidget*parent) : MultimediaEditeur(parent), fichierAudio(i) {

    //sauver->setDisabled(true);
    layout->addWidget(sauver);
    layout->addWidget(bsupprimer);
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

}

void AudioEditeur::saveModifications(){

    fichierAudio->setDateLastModification();
    fichierAudio->setTitle(title->text());
    fichierAudio->setDescription(description->text());
    fichierAudio->setImage(image->text());

    //task->setDeadline(deadline->text().t);
    QMessageBox::information(this, "Sauvegarde", "Audio sauvegardé !");
    sauver->setDisabled(true);
}

void AudioEditeur::supprimer(){
    Corbeille::getInstance().addNoteCorbeille(fichierAudio);
    NotesManager::getInstance().supprimerNote(fichierAudio->getId());
    QMessageBox::information(this, "Suppression", "Article supprimé !");
    CorbeilleEditeur* c = new CorbeilleEditeur (&(Corbeille::getInstance()));
    RelationsManager::getInstance().chercherCouple(fichierAudio);
    c->show();
    this->close();
}



