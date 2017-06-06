#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manager.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

}

mainWindow::~mainWindow()
{
    delete ui;
}


