#ifndef noteediteur_cpp
#define noteediteur_cpp

#include "noteediteur.h"
#include <QMessageBox>


#endif
/*********************************************************************
 ***                       Note Editeur                             **
 *********************************************************************/

     NoteEditeur::NoteEditeur(QWidget *){
    formulaire = new QFormLayout;
    layout = new QVBoxLayout;

    id = new QLineEdit(this);
    title = new QLineEdit(this);
    dateC = new QLineEdit(this);
    dateM = new QLineEdit(this);
    sauver = new QPushButton("sauver",this);

    formulaire->addRow("Identificateur :", id);
    formulaire->addRow("Titre :", title);
    formulaire->addRow("Date de création :", dateC);
    formulaire->addRow("Date de dernière modification :", dateM);


    layout = new QVBoxLayout;
    layout->addLayout(formulaire);
    layout->addWidget(sauver);


    id->setDisabled(true);
    sauver->setDisabled(true);
    dateC->setDisabled(true);
    dateM->setDisabled(true);


}

void NoteEditeur::afficherBouton(QString){
    sauver->setDisabled(false);
}

/*********************************************************************/



/*********************************************************************
 ***                      Article Editeur                           **
 *********************************************************************/
 ArticleEditeur::ArticleEditeur(Article* a, QWidget *parent) : NoteEditeur(parent), article(a){
        text = new QLineEdit(this);
        formulaire->addRow("Texte :", text);

        dateC->setText(a->getDateC().toString());
        id->setText(a->getId());
        title->setText(a->getTitle());
        text->setText(a->getText());


        layout->addWidget(sauver);

        setLayout(layout);

        QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(saveModifications()));
        QObject::connect(title , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
        QObject::connect(text , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));

}


void ArticleEditeur::saveModifications(){
    article->setTitle(title->text());
    article->setText(text->text());
    article->setDateLastModification();
    sauver->setDisabled(true);
    QMessageBox::information(this, "Sauvegarde", "Article sauvegardé !");
}


/*********************************************************************
 ***                         Task Editeur                           **
 *********************************************************************/
 TaskEditeur::TaskEditeur(Task* t, QWidget *parent) : NoteEditeur(parent), task(t) {

        state = new QComboBox;
        state->addItem("Waiting");
        state->addItem("Ongoing");
        //state->addItem("Done");

        action = new QLineEdit(this);
        priority = new QLineEdit(this);
        deadline = new QLineEdit(this);
        //state = new QLineEdit(this);

        formulaire->addRow("Texte :", action);
        formulaire->addRow("Priorité :", priority);
        formulaire->addRow("Deadline :", deadline);
        formulaire->addRow("Etat :", state);

        dateC->setText(t->getDateC().toString());
        id->setText(t->getId());
        title->setText(t->getTitle());
        action->setText(t->getAction());
        priority->setText(QString::number(t->getPriority()));
        deadline->setText(t->getDeadline().toString());
        //state->setText(QString::fromStdString(toString(t->getState())));

        layout->addWidget(sauver);

        setLayout(layout);

        QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(saveModifications()));
        QObject::connect(title , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
        QObject::connect(action , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
        QObject::connect(priority , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
        QObject::connect(deadline , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
}
void TaskEditeur::saveModifications(){
    task->setTitle(title->text());
    task->setAction(action->text());
    task->setPriority(priority->text().toInt());
    task->setState(state->currentText());
    //task->setDeadline(deadline->text().t);
    QMessageBox::information(this, "Sauvegarde", "Article sauvegardé !");
    sauver->setDisabled(true);
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

     setLayout(layout);

    layout->addWidget(sauver);

    QObject::connect(sauver, SIGNAL(clicked()), this, SLOT(saveModifications()));
    QObject::connect(title , SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(description, SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));
    QObject::connect(image, SIGNAL(textChanged(QString)), this, SLOT(afficherBouton(QString)));

}


/*********************************************************************/



/********************************************************************
***                          Image Editeur                         **
*********************************************************************/

ImageEditeur::ImageEditeur(Image*i, QWidget*parent) : MultimediaEditeur(parent), fichierImage(i) {

    id->setText(fichierImage->getId());
    dateC->setText(fichierImage->getDateC().toString());
    title->setText(fichierImage->getTitle());
    description->setText(fichierImage->getDescription());
    image->setText(fichierImage->getImage());

}

void ImageEditeur::saveModifications(){

    fichierImage->setDateLastModification();
    fichierImage->setTitle(title->text());
    fichierImage->setDescription(description->text());
    fichierImage->setImage(image->text());

    //task->setDeadline(deadline->text().t);
    QMessageBox::information(this, "Sauvegarde", "Article sauvegardé !");
    sauver->setDisabled(true);
}

/*********************************************************************/


/*********************************************************************/



/********************************************************************
***                          Video Editeur                         **
*********************************************************************/

VideoEditeur::VideoEditeur(Video*i, QWidget*parent) : MultimediaEditeur(parent), fichierVideo(i) {

    id->setText(fichierVideo->getId());
    dateC->setText(fichierVideo->getDateC().toString());
    title->setText(fichierVideo->getTitle());
    description->setText(fichierVideo->getDescription());
    image->setText(fichierVideo->getImage());

}

void VideoEditeur::saveModifications(){

    fichierVideo->setDateLastModification();
    fichierVideo->setTitle(title->text());
    fichierVideo->setDescription(description->text());
    fichierVideo->setImage(image->text());

    //task->setDeadline(deadline->text().t);
    QMessageBox::information(this, "Sauvegarde", "Article sauvegardé !");
    sauver->setDisabled(true);
}

/*********************************************************************/



/********************************************************************
***                          Audio Editeur                         **
*********************************************************************/

AudioEditeur::AudioEditeur(Audio*i, QWidget*parent) : MultimediaEditeur(parent), fichierAudio(i) {

    id->setText(fichierAudio->getId());
    dateC->setText(fichierAudio->getDateC().toString());
    title->setText(fichierAudio->getTitle());
    description->setText(fichierAudio->getDescription());
    image->setText(fichierAudio->getImage());

}

void AudioEditeur::saveModifications(){

    fichierAudio->setDateLastModification();
    fichierAudio->setTitle(title->text());
    fichierAudio->setDescription(description->text());
    fichierAudio->setImage(image->text());

    //task->setDeadline(deadline->text().t);
    QMessageBox::information(this, "Sauvegarde", "Article sauvegardé !");
    sauver->setDisabled(true);
}



