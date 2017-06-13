#ifndef corbeilleediteur_h
#define corbeilleediteur_h
#include<QWidget>
#include<QListWidget>
#include<QPushButton>
#include<QScrollArea>
#include <QVBoxLayout>

/** @file corbeilleeidteur.h
 */


#include "manager.h"

class Corbeille;

/**
 * @class CorbeilleEditeur
 * @brief Cette éditeur de corbeille va afficher la liste des notes dans la corbeille
 * et nous permettre de restaurer une note ou vider la corbeille.
 */


class CorbeilleEditeur : public QWidget{
private:
    Q_OBJECT
    QListWidget* list;
    QVBoxLayout* layout;
    QScrollArea* scroller;
    QPushButton* vider;
    QPushButton* restaurer;

    Corbeille* corbeille;
public:
    ///CONSTRUCTEUR

    /**
     * @fn CorbeilleEditeur
     * @param parent
     * @brief constructeur
     */
    CorbeilleEditeur(Corbeille*, QWidget* parent = 0);

    /**
     * @fn setList
     * @brief fonction qui nous permet de mettre à jour l'affichage de la liste
     * des notes du tableau de corbeille
     */

    void setList();
signals:
public slots:
    /**
     * @fn restaurerNote
     * fonction qui permet de restaurer la note sur laquelle on clique dans la liste
     * des notes de la corbeille
     */
    void restaurerNote();

    /**
     * @fn afficherBoutons
     * @brief rend visible le bouton "restaurer" quand on séléctionne
     * une note de la liste de la corbeille
     */

    void afficherBoutons();

    /**
     * @fn viderCorbeille
     * @brief vide la corbeille et supprime définitivement toutes les notes
     * du tableau de note de la corbeille
     */

    void viderCorbeille();

};

#endif
