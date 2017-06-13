#ifndef relationediteur_h
#define relationediteur_h
#include <QWidget>
#include <QListWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QLabel>

#include "manager.h"
#include "labelediteur.h"

class Reference;
class Relation;

class RelationEditeur : public QWidget {
    Q_OBJECT
    QLabel* titreRelation;
    QListWidget* list;
    QVBoxLayout* layout;
    QScrollArea* scroller;
    QPushButton* modifier;
    QPushButton* supprimer;
    QPushButton* ajouter;
    QPushButton* rafraichir;
    QCheckBox* oriented;
    QGroupBox* option;
    QVBoxLayout* optionLayout;


    Relation* relation;

public:

    ///DESTRUCTEUR
    ~RelationEditeur() {}

    ///CONSTRUCTEUR
    RelationEditeur(Relation*, QWidget* parent = 0);

    void setList();
signals:
public slots:
    void setOriented();
    void modifierLabel();
    void addCouple();
    void supprimerCouple();
    void ssetList();
private slots:
    void afficherRafraichir();
    void afficherBoutons();

};

class ReferenceEditeur : public QWidget {
    Q_OBJECT
    QLabel* titreRelation;
    QListWidget* list;
    QVBoxLayout* layout;
    QScrollArea* scroller;


    Reference* reference;

public:
    ~ReferenceEditeur() {}
    ReferenceEditeur(Reference*, QWidget* parent = 0);
    void setList();
signals:
public slots:
    //void ssetList();
private slots:

};


#endif
