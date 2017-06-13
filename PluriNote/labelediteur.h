#ifndef labelediteur_h
#define labelediteur_h
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "couple.h"

/** \file labelediteur.h */

/**
 * @class labelEditeur
 * éditeur qui apparaît lorsque l'on souhaite modifier le label d'un
 * couple
 */



class labelEditeur : public QWidget {
    Q_OBJECT
    QLineEdit* label;
    QFormLayout* formulaire;
    QVBoxLayout* layout;
    QPushButton* modifier;
    QPushButton* bannuler;
    Couple* couple;
public:
    ///CONSTRUCTEUR

    /**
     * @fn labelEditeur
     * @param parent
     * @brief constructeur
     */

    labelEditeur(Couple*, QWidget* parent=0);
signals:
public slots:

    /**
     * @fn saveModifications
     * permet, une fois que l'utilisateur a cliqué sur "sauver", d'enregistrer les différentes modifications
     * effectuées
     */
    void saveModification();

    /**
     * @fn annuler
     * @brief fermer la fenêtre
     */

    void annuler(){this->close();}
private slots:

    /**
     * @fn afficherBouton
     * fonction qui rend visible le bouton sauver une fois que deux notes ont été séléctionnées
     * et que le label a été précisé
     */
    void afficherButton();
};
#endif
