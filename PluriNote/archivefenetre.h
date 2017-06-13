#ifndef archivefenetre_h
#define archivefenetre_h

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

//#include "relation.h"
#include "mainwindow.h"
#include "note.h"

class Corbeille;
class Note;

class ArchiveFenetreEditeur : public QWidget {
    Q_OBJECT
    QLabel* question;
    QVBoxLayout* layout;
    QHBoxLayout* reponses;
    QPushButton* oui;
    QPushButton* non;
    Note* note;

public:
    ArchiveFenetreEditeur(Note*, QWidget* parent=0);
signals:
public slots:
    void clickOnOui();
    void clickOnNon();
private slots:
};


#endif
