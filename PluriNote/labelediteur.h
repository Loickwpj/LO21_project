#ifndef labelediteur_h
#define labelediteur_h
#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>

#include "couple.h"




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
    labelEditeur(Couple*, QWidget* parent=0);
signals:
public slots:
    void saveModification();
    void annuler(){this->close();}
private slots:
    void afficherButton();
};
#endif
