#ifndef corbeilleediteur_h
#define corbeilleediteur_h
#include<QWidget>
#include<QListWidget>
#include<QPushButton>
#include<QScrollArea>
#include <QVBoxLayout>

#include "manager.h"

class Corbeille;

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
    CorbeilleEditeur(Corbeille*, QWidget* parent = 0);
    void setList();
signals:
public slots:
    void restaurerNote();
    void afficherBoutons();
    void viderCorbeille();

};

#endif
