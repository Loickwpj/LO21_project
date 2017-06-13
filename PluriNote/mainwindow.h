#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/** \file mainwindow.h */

#include <QMainWindow>
#include<QListWidgetItem>

#include "manager.h"
#include "noteediteur.h"
#include "relationediteur.h"
#include "labelrelationediteur.h"
#include "archivefenetre.h"
#include "parametrecorbeilleediteur.h"

/**
 * @namespace Ui
 *
 * fait le lien avec l'interface graphique issue de Qt Designer
 *
 */

namespace Ui {

/** @class mainWindow
 *
 */
class mainWindow;
}


/**
 * @class mainWindow
 *
 * fenêtre principale de l'application qui dispose d'une instance unique et hérite de QMainWindow
 */
class mainWindow : public QMainWindow
{
    friend class Note;
    Q_OBJECT

public:

    /**
     * @fn clear
     * permet de vider un layout de tous les widgets dont ils disposent
     */
    void clear();

    /**
     * @fn getInstance
     * @return l'instance unique de la fenêtre principale
     */
    static mainWindow* getInstance();

    /**
     * @fn libererInstance
     * permet de supprimer l'instance unique de la fenêtre principale
     */
    static void libererInstance();

    /**
     * @fn setNotesList
     * permet de mettre à jour le layout présentant l'ensembles des notes actives (notes ou tâches)
     * ainsi que celles qui sont archivées
     */
    void setNotesList();


    /**
     * @fn setRelationsList
     * permet de mettre à jour l'ensemble des relations présentes
     * dans le relationsmanager plus la relation Référence
     */
    void setRelationsList();

    Ui::mainWindow *ui;

private:
    ///CONSTRUCTEUR


    explicit mainWindow(QWidget *parent = 0);

    ///DESTRUCTEUR
    ~mainWindow();

    static mainWindow* instance;

public slots:

    /**
     * @fn createArticle
     * fonction qui va permettre d'afficher un éditeur d'article dont les champs
     * sont remplis par défaut
     */
    void createArticle();

    /**
     * @fn createTask
     * fonciton qui va permettre d'afficher un éditeur de tâche dont les champs
     * sont remplis par défaut
     */

    void createTask();

    /**
     * @fn createAudio
     * fonciton qui va permettre d'afficher un éditeur de fichier audio dont les champs
     * sont remplis par défaut
     *
     */
    void createAudio();

    /**
     * @fn createImage
     * fonciton qui va permettre d'afficher un éditeur de fichier image dont les champs
     * sont remplis par défaut
     */

    void createImage();

    /**
     * @fn createVideo
     * fonciton qui va permettre d'afficher un éditeur de fichier vidéo dont les champs
     * sont remplis par défaut
     */

    void createVideo();

    /**
     * @fn createRelation
     * fonction qui va afficher un éditeur de relation qui
     * va permettre à l'utilisateur de rentrer le titre et la description
     * de la note qu'il souhaite créer
     */

    void createRelation() ;


    /**
     * @fn afficherCorbeille
     * fonction qui fait apparaître un éditeur de la corbeille
     * ainsi que toutes les notes qui sont dedans
     */
    void afficherCorbeille();

    /**
     * @fn afficherParametreCorbeille
     * fonction qui va permettre d'afficher un éditeur permettant à l'utilisateur
     * de choisir s'il veut que le vidage automatique de la corbeille chaque fois que l'on quitte
     * l'application soit activé ou non
     */

    void afficherParametreCorbeille();

    /**
     * @fn afficherRelation
     * permet d'afficher un éditeur de relation comprenant la liste des couples appartenant à la relation
     * choisie
     */

    void afficherRelation();

    /**
     * @fn afficherNote
     * permet d'afficher une note dans le layout central en cliquant sur celle-ci
     */
    void afficherNote();

    /**
     * @fn afficherTask
     * permet d'afficher une tâche dans le layout central en cliquant sur celle-ci
     */
    void afficherTask();

    /**
     * @fn afficherArchive
     * permet d'afficher une note archivée dans le layout central en rendant tous ses champs
     * non modifiables
     */

    void afficherArchive();

    /**
     * @fn quitter
     * permet de quitter l'application
     */
    void quitter();
};

#endif // MAINWINDOW_H
