#ifndef coupleediteur_h
#define coupleediteur_h
#include <QWidget>
#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QScrollArea>
#include <QLabel>
#include <QLineEdit>

/** \file coupleediteur.h */

#include "manager.h"
#include "couple.h"

class Couple;
/**
 * @class CoupleEditeur
 * classe qui nous permet d'afficher un éditeur présentant deux listes de toutes les
 * notes du notesmanager afin de créer des couples en cliquant sur les notes et en ajoutant un label
 */


class CoupleEditeur : public QWidget{
    Q_OBJECT
    QListWidget* note1;
    QListWidget* note2;
    QScrollArea* scroll1;
    QScrollArea* scroll2;
    QLabel* note1l;
    QLabel* note2l;
    QLabel* labell;
    QVBoxLayout* note1Layout;
    QVBoxLayout* note2Layout;
    QHBoxLayout* notes;
    QHBoxLayout* label;
    QVBoxLayout* layout;
    QLineEdit* labelEdit;
    QPushButton* sauver;
    Couple* couple;

public:
    ///CONSTRUCTEUR
    /**
     * @fn CoupleEditeur
     * @param parent
     * constructeur
     */

    CoupleEditeur(Couple*, QWidget *parent = 0);

    ///SET

    /**
     * @fn setList1
     * @brief fonction qui nous permet d'afficher une première liste des notes de notesmanager
     * qui correspondra à la note 1 du couple sur le point d'être créé
     */

    void setList1();

    /**
     * @fn setList2
     * @brief fonction qui nous permet d'afficher une première liste des notes de notesmanager
     * qui correspondra à la note 2 du couple sur le point d'être créé
     */

    void setList2();
signals:
public slots:

    /**
     * @fn saveModifications
     * permet, une fois que l'utilisateur a cliqué sur "sauver", d'enregistrer les différentes modifications
     * effectuées
     */

    void saveModifications();
private slots:

    /**
     * @fn afficherBouton
     * fonction qui rend visible le bouton sauver une fois que deux notes ont été séléctionnées
     * et que le label a été précisé
     */

    void afficherBouton();

    /**
     * @fn afficherLabel1
     * fonction qui rend la saisi possible du label si
     * deux notes ont été séléctionné au préalable
     */

    void afficherLabel1();

    /**
     * @fn afficherLabel2
     * fonction qui rend la saisi possible du label si
     * deux notes ont été séléctionné au préalable
     */

    void afficherLabel2();
};

#endif

