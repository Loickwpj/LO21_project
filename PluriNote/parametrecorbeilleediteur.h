#ifndef parametrecorbeilleediteur_h
#define parametrecorbeilleediteur_h
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>
#include "mainwindow.h"

/** \file parametrecorbeilleediteur.h */

/**
 * @class Editeur
 *
 * Editeur qui fait apparaître une fenêtre
 * disposant d'un question à laquelle on répond par oui ou par non
 *
 * Cette classe est abstraite
 */

class Editeur : public QWidget {
    Q_OBJECT
protected:
    QLabel* question;
    QPushButton* oui;
    QPushButton* non;
    QHBoxLayout* reponse;
    QVBoxLayout* layout;
public:

    /**
     * @fn Editeur
     * @param parent
     * @brief constructeur
     */
    Editeur (QWidget* parent =0);

public slots:
    /**
     * @fn clickOnOui
     * @brief fonction qui se lance lorsqu'on appuie sur
     * le bouton oui, c'est une fonction virtuelle pure
     */

    virtual void clickOnOui() =0;

    /**
     * @fn clickOnNon
     * @brief fonction qui se lance lorsqu'on appuie sur
     * le bouton non, c'est une fonction virtuelle pure
     */

    virtual void clickOnNon() =0;
private slots:
};


/** @class ParametreCorbeille
 * @brief première classe qui hérite d'Editeur
 * Elle affiche un message pour proposer à l'utilisateur de rentrer automatique
 * le vidage de la corbeille chaque fois qu'on quitte l'application
 *
 */

class ParametreCorbeille : public Editeur{
    Q_OBJECT
public:
    /**
     * @fn ParametreCorbeille
     * @param parent
     * @brief constructeur
     */
    ParametreCorbeille (QWidget* parent =0);
public slots:
    /**
     * @fn clickOnOui
     * @brief l'object QSettings chargé d'enregistrer les
     * préférences de l'utilisateur dispose d'un attribut "viderCorbeilleAuto" de type booléen
     * qui passe à true, à chaque sortie de l'applicaiton, la corbeille est automatiquement vidée
     */

    void clickOnOui();

    /**
     * @fn clickOnOui
     * @brief l'object QSettings chargé d'enregistrer les
     * préférences de l'utilisateur dispose d'un attribut "viderCorbeilleAuto" de type booléen
     * qui passe à false, chaque fois que l'uilisateur quitte l'application, on lui propose de
     * vider la corbeille
     */

    void clickOnNon();
};

/**
 * @class QuitterApp
 *
 * @brief Second éditeur qui hérite de Editeur,
 * celui-ci va demander à l'utilisateur lorsqu'il sort de l'application s'il
 * souhaite vider la corbeille ou non
 */


class QuitterApp : public Editeur {
    Q_OBJECT
public :
    /**
     * @fn QuitterApp
     * @brief constructeur
     */
    QuitterApp(QWidget* =0);
public slots:

    /**
     * @fn clickOnOui
     * @brief la corbeille est vidée
     *
     */
    void clickOnOui();

    /**
     * @fn clickOnNon
     * @brief la corbeille n'est pas vidée
     */

    void clickOnNon();

};


#endif
