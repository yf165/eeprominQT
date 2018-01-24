#include <QPushButton>
#include <QtGui>
#include <QWidget>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QPushButton *startButton = new QPushButton("start");
    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(startButton);

    mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);


//    mainWidget.setLayout(&mainLayout);
//    centralWidget()->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{

}
