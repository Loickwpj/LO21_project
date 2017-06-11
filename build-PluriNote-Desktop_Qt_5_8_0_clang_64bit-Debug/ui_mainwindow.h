/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainWindow
{
public:
    QAction *actionNote;
    QAction *actionTache;
    QAction *actionImage;
    QAction *actionAudio;
    QAction *actionVideo;
    QAction *nouvelleRelationAction;
    QAction *actionafficher;
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *centralLayout;
    QVBoxLayout *titre;
    QLabel *label;
    QVBoxLayout *partiePrincipale;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QPushButton *pushButtonArticle;
    QPushButton *pushButtonTask;
    QPushButton *pushButtonImage;
    QPushButton *pushButtonVideo;
    QPushButton *pushButtonAudio;
    QSpacerItem *verticalSpacer_2;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *listRelationLayout;
    QLabel *relationLabel;
    QListWidget *listRelation;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *partieGauche;
    QLabel *notesLabel;
    QListWidget *listWidgetNotesActives;
    QLabel *taskLabel;
    QListWidget *listWidgetTasksActives;
    QLabel *archivesLabel;
    QListWidget *listWidgetArchive;
    QMenuBar *menubar;
    QMenu *menuNote;
    QMenu *menunouvelle_note;
    QMenu *menuRelations;
    QMenu *menuCorbeille;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *mainWindow)
    {
        if (mainWindow->objectName().isEmpty())
            mainWindow->setObjectName(QStringLiteral("mainWindow"));
        mainWindow->resize(800, 600);
        actionNote = new QAction(mainWindow);
        actionNote->setObjectName(QStringLiteral("actionNote"));
        actionTache = new QAction(mainWindow);
        actionTache->setObjectName(QStringLiteral("actionTache"));
        actionImage = new QAction(mainWindow);
        actionImage->setObjectName(QStringLiteral("actionImage"));
        actionAudio = new QAction(mainWindow);
        actionAudio->setObjectName(QStringLiteral("actionAudio"));
        actionVideo = new QAction(mainWindow);
        actionVideo->setObjectName(QStringLiteral("actionVideo"));
        nouvelleRelationAction = new QAction(mainWindow);
        nouvelleRelationAction->setObjectName(QStringLiteral("nouvelleRelationAction"));
        actionafficher = new QAction(mainWindow);
        actionafficher->setObjectName(QStringLiteral("actionafficher"));
        centralwidget = new QWidget(mainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(260, 0, 331, 561));
        centralLayout = new QVBoxLayout(verticalLayoutWidget_3);
        centralLayout->setObjectName(QStringLiteral("centralLayout"));
        centralLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        centralLayout->setContentsMargins(0, 0, 0, 0);
        titre = new QVBoxLayout();
        titre->setObjectName(QStringLiteral("titre"));
        titre->setSizeConstraint(QLayout::SetFixedSize);
        label = new QLabel(verticalLayoutWidget_3);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Webdings"));
        font.setPointSize(36);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        titre->addWidget(label);


        centralLayout->addLayout(titre);

        partiePrincipale = new QVBoxLayout();
        partiePrincipale->setObjectName(QStringLiteral("partiePrincipale"));
        partiePrincipale->setSizeConstraint(QLayout::SetMinimumSize);
        partiePrincipale->setContentsMargins(-1, 0, -1, -1);
        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Fixed);

        partiePrincipale->addItem(verticalSpacer);

        label_2 = new QLabel(verticalLayoutWidget_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(18);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);

        partiePrincipale->addWidget(label_2);

        pushButtonArticle = new QPushButton(verticalLayoutWidget_3);
        pushButtonArticle->setObjectName(QStringLiteral("pushButtonArticle"));

        partiePrincipale->addWidget(pushButtonArticle);

        pushButtonTask = new QPushButton(verticalLayoutWidget_3);
        pushButtonTask->setObjectName(QStringLiteral("pushButtonTask"));

        partiePrincipale->addWidget(pushButtonTask);

        pushButtonImage = new QPushButton(verticalLayoutWidget_3);
        pushButtonImage->setObjectName(QStringLiteral("pushButtonImage"));

        partiePrincipale->addWidget(pushButtonImage);

        pushButtonVideo = new QPushButton(verticalLayoutWidget_3);
        pushButtonVideo->setObjectName(QStringLiteral("pushButtonVideo"));

        partiePrincipale->addWidget(pushButtonVideo);

        pushButtonAudio = new QPushButton(verticalLayoutWidget_3);
        pushButtonAudio->setObjectName(QStringLiteral("pushButtonAudio"));

        partiePrincipale->addWidget(pushButtonAudio);

        verticalSpacer_2 = new QSpacerItem(20, 150, QSizePolicy::Minimum, QSizePolicy::Fixed);

        partiePrincipale->addItem(verticalSpacer_2);


        centralLayout->addLayout(partiePrincipale);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(590, 289, 211, 271));
        listRelationLayout = new QVBoxLayout(verticalLayoutWidget);
        listRelationLayout->setObjectName(QStringLiteral("listRelationLayout"));
        listRelationLayout->setContentsMargins(0, 0, 0, 0);
        relationLabel = new QLabel(verticalLayoutWidget);
        relationLabel->setObjectName(QStringLiteral("relationLabel"));

        listRelationLayout->addWidget(relationLabel);

        listRelation = new QListWidget(verticalLayoutWidget);
        listRelation->setObjectName(QStringLiteral("listRelation"));

        listRelationLayout->addWidget(listRelation);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(-1, 0, 261, 561));
        partieGauche = new QVBoxLayout(verticalLayoutWidget_2);
        partieGauche->setObjectName(QStringLiteral("partieGauche"));
        partieGauche->setContentsMargins(0, 0, 0, 0);
        notesLabel = new QLabel(verticalLayoutWidget_2);
        notesLabel->setObjectName(QStringLiteral("notesLabel"));

        partieGauche->addWidget(notesLabel);

        listWidgetNotesActives = new QListWidget(verticalLayoutWidget_2);
        listWidgetNotesActives->setObjectName(QStringLiteral("listWidgetNotesActives"));

        partieGauche->addWidget(listWidgetNotesActives);

        taskLabel = new QLabel(verticalLayoutWidget_2);
        taskLabel->setObjectName(QStringLiteral("taskLabel"));

        partieGauche->addWidget(taskLabel);

        listWidgetTasksActives = new QListWidget(verticalLayoutWidget_2);
        listWidgetTasksActives->setObjectName(QStringLiteral("listWidgetTasksActives"));

        partieGauche->addWidget(listWidgetTasksActives);

        archivesLabel = new QLabel(verticalLayoutWidget_2);
        archivesLabel->setObjectName(QStringLiteral("archivesLabel"));

        partieGauche->addWidget(archivesLabel);

        listWidgetArchive = new QListWidget(verticalLayoutWidget_2);
        listWidgetArchive->setObjectName(QStringLiteral("listWidgetArchive"));

        partieGauche->addWidget(listWidgetArchive);

        mainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuNote = new QMenu(menubar);
        menuNote->setObjectName(QStringLiteral("menuNote"));
        menunouvelle_note = new QMenu(menuNote);
        menunouvelle_note->setObjectName(QStringLiteral("menunouvelle_note"));
        menuRelations = new QMenu(menubar);
        menuRelations->setObjectName(QStringLiteral("menuRelations"));
        menuCorbeille = new QMenu(menubar);
        menuCorbeille->setObjectName(QStringLiteral("menuCorbeille"));
        mainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(mainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        mainWindow->setStatusBar(statusbar);

        menubar->addAction(menuNote->menuAction());
        menubar->addAction(menuRelations->menuAction());
        menubar->addAction(menuCorbeille->menuAction());
        menuNote->addAction(menunouvelle_note->menuAction());
        menunouvelle_note->addAction(actionNote);
        menunouvelle_note->addAction(actionTache);
        menunouvelle_note->addAction(actionImage);
        menunouvelle_note->addAction(actionAudio);
        menunouvelle_note->addAction(actionVideo);
        menuRelations->addAction(nouvelleRelationAction);
        menuCorbeille->addAction(actionafficher);

        retranslateUi(mainWindow);

        QMetaObject::connectSlotsByName(mainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainWindow)
    {
        mainWindow->setWindowTitle(QApplication::translate("mainWindow", "MainWindow", Q_NULLPTR));
        actionNote->setText(QApplication::translate("mainWindow", "Article", Q_NULLPTR));
        actionTache->setText(QApplication::translate("mainWindow", "Tache", Q_NULLPTR));
        actionImage->setText(QApplication::translate("mainWindow", "Image", Q_NULLPTR));
        actionAudio->setText(QApplication::translate("mainWindow", "Audio", Q_NULLPTR));
        actionVideo->setText(QApplication::translate("mainWindow", "Video", Q_NULLPTR));
        nouvelleRelationAction->setText(QApplication::translate("mainWindow", "nouvelle relation", Q_NULLPTR));
        actionafficher->setText(QApplication::translate("mainWindow", "afficher", Q_NULLPTR));
        label->setText(QApplication::translate("mainWindow", "PluriNotes", Q_NULLPTR));
        label_2->setText(QApplication::translate("mainWindow", "Cr\303\251er une nouvelle note :", Q_NULLPTR));
        pushButtonArticle->setText(QApplication::translate("mainWindow", "Article", Q_NULLPTR));
        pushButtonTask->setText(QApplication::translate("mainWindow", "T\303\242che", Q_NULLPTR));
        pushButtonImage->setText(QApplication::translate("mainWindow", "Image", Q_NULLPTR));
        pushButtonVideo->setText(QApplication::translate("mainWindow", "Vid\303\251o", Q_NULLPTR));
        pushButtonAudio->setText(QApplication::translate("mainWindow", "Audio", Q_NULLPTR));
        relationLabel->setText(QApplication::translate("mainWindow", "Relations :", Q_NULLPTR));
        notesLabel->setText(QApplication::translate("mainWindow", "Notes :", Q_NULLPTR));
        taskLabel->setText(QApplication::translate("mainWindow", "T\303\242ches : ", Q_NULLPTR));
        archivesLabel->setText(QApplication::translate("mainWindow", "Notes archiv\303\251es :", Q_NULLPTR));
        menuNote->setTitle(QApplication::translate("mainWindow", "Notes", Q_NULLPTR));
        menunouvelle_note->setTitle(QApplication::translate("mainWindow", "nouvelle note", Q_NULLPTR));
        menuRelations->setTitle(QApplication::translate("mainWindow", "Relations", Q_NULLPTR));
        menuCorbeille->setTitle(QApplication::translate("mainWindow", "Corbeille", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mainWindow: public Ui_mainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
