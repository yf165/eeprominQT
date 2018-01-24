#include <QPushButton>
#include <QtGui>
#include <QWidget>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

//    resize(1024,600);
    mainLayout = new QVBoxLayout();
    QPushButton *startButton = new QPushButton("start");
    QPushButton *stopButton = new QPushButton("exit");
    QVBoxLayout vLayout;
    QHBoxLayout hLayout;
    QStringList deviceAddress("devAddr");


#if 1
    hLayout.addWidget(startButton);
    hLayout.addWidget(stopButton);
#endif
 //   mainLayout->add(&deviceAddress);
    mainLayout->addLayout(&hLayout);

#if 0
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(stopButton);
#endif
    mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
//    mainWidget->setLayout(&hLayout);
    setCentralWidget(mainWidget);
}

MainWindow::~MainWindow()
{

}
