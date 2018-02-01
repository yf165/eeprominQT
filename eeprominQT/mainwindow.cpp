#include <QPushButton>
#include <QtGui>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    resize(1024,600);
    mainLayout = new QVBoxLayout();
    QPushButton *startButton = new QPushButton("start");
    QPushButton *stopButton = new QPushButton("exit");
 //   startButton->resize(200,200);
 //   stopButton->resize(100,100);
    QVBoxLayout vLayout;
    QHBoxLayout *hLayout = new QHBoxLayout();
    QStringList deviceAddress("devAddr");
//    QLineEdit *resultText = new QLineEdit;
    resultText = new QTextBrowser();
    QLabel *resultLabel = new QLabel("reslut");
    QSlider *slider = new QSlider();

#if 1
//    hLayout->addWidget(resultLabel);
//    hLayout->addWidget(resultText);
    hLayout->addWidget(startButton);
    hLayout->addWidget(stopButton);
    hLayout->addWidget(slider);

#endif
 //   mainLayout->add(&deviceAddress);
    mainLayout->addWidget(resultText);
    mainLayout->addLayout(hLayout);

#if 1
//    mainLayout->addWidget(startButton);
 //   mainLayout->addWidget(stopButton);
#endif
    mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
//    mainWidget->setLayout(&hLayout);
    setCentralWidget(mainWidget);
    connect(startButton,SIGNAL(clicked()),this,SLOT(readStart()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(clearExit()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::readStart()
{
    resultText->append("hello world\n");

}
void MainWindow::clearExit()
{
    resultText->clear();

}
