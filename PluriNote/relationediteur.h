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
    ~RelationEditeur() {}
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


#endif
