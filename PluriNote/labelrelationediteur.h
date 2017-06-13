#ifndef labelrelationediteur_h
#define labelrelationediteur_h

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

//#include "relation.h"
#include "mainwindow.h"

class Relation;

class labelRelationEditeur : public QWidget {
    Q_OBJECT
    QLineEdit* titre;
    QLineEdit* description;
    QFormLayout* formulaire;
    QVBoxLayout* layout;
    QPushButton* creer;
    QPushButton* bannuler;
    Relation* relation;
public:
    ///CONSTRUCTEUR
    /**
     * @fn labelRelationEditeur
     * @param parent
     * @brief constructeur
     */

    labelRelationEditeur(Relation*, QWidget* parent=0);
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
