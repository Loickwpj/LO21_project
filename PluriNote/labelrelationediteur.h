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
    labelRelationEditeur(Relation*, QWidget* parent=0);
signals:
public slots:
    void saveModification();
    void annuler(){this->close();}
private slots:
    void afficherButton();
};

#endif
