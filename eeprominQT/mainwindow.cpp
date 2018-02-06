#include <QApplication>
#include <QPushButton>
#include <QtGui>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QSlider>
#include <iostream>
#include <fstream>
using namespace std;

#include "mainwindow.h"
extern "C"
{
#include "eeprom.h"
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    resize(1024,600);

    devAddress = new QComboBox;
    devAddress->addItem("A0");
    devAddress->addItem("A1");
    devAddress->addItem("A2");
    devAddress->addItem("A3");
    upperPage = new QComboBox;
    upperPage->addItem("0");
    upperPage->addItem("1");
    upperPage->addItem("2");
    upperPage->addItem("3");
    mainLayout = new QVBoxLayout();
    QPushButton *startButton = new QPushButton("start");
    QPushButton *clearButton = new QPushButton("clear");
    QPushButton *stopButton = new QPushButton("exit");
 //   startButton->resize(200,200);
 //   stopButton->resize(100,100);
    QHBoxLayout *hLayout = new QHBoxLayout();
    QHBoxLayout *hLayoutCombo = new QHBoxLayout();
    QStringList deviceAddress("devAddr");
//    QLineEdit *resultText = new QLineEdit;
    resultText = new QTextBrowser();
    QLabel *resultLabel = new QLabel("read eeprom ");
    QLabel *topLabel = new QLabel("read eeprom ");
//    QSlider *slider = new QSlider();

#if 1
    hLayout->addWidget(startButton);
    hLayout->addWidget(clearButton);
    hLayout->addWidget(stopButton);
//    hLayout->addWidget(slider);
    hLayoutCombo->addWidget(devAddress);
    hLayoutCombo->addWidget(upperPage);

#endif
 //   mainLayout->add(&deviceAddress);
    mainLayout->addWidget(topLabel);
    mainLayout->addLayout(hLayoutCombo);
    mainLayout->addWidget(resultText);

    mainLayout->addLayout(hLayout);
    mainLayout->addWidget(resultLabel);

#if 1
//    mainLayout->addWidget(startButton);
 //   mainLayout->addWidget(stopButton);
#endif
    mainWidget = new QWidget();
    mainWidget->setLayout(mainLayout);
//    mainWidget->setLayout(&hLayout);
    setCentralWidget(mainWidget);
    connect(startButton,SIGNAL(clicked()),this,SLOT(readStart()));
    connect(clearButton,SIGNAL(clicked()),this,SLOT(clearB()));
    connect(stopButton,SIGNAL(clicked()),this,SLOT(exitB()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::readStart()
{
    fd = openEep(DEVICE);
    unsigned char writeBuf[256];
 //   unsigned char readBuf[256] = {0};
    unsigned char lDevAddress = 0,pageNumber = 0;
    lDevAddress = (devAddress->currentText()).toInt(0,16);
    lDevAddress = lDevAddress >> 1;
    pageNumber =  (upperPage->currentText()).toInt(0,16);
    unsigned char readBuf[256];
    cout<<"devAddress->currentText():"<<(devAddress->currentText()).toStdString()<<endl;
    cout<<hex<<"(devAddress->currentText()).toInt():"<<(unsigned int)lDevAddress<<endl;

    resultText->clear();
    memset(writeBuf,0,sizeof(writeBuf));
    writeBuf[0] = pageNumber;
    writeEep(fd,lDevAddress,PAGEADDRESS,writeBuf, 1);
    memset(readBuf,0,sizeof(readBuf));
    readEep(fd,lDevAddress,0,128,(char * )readBuf);
    printBuf(readBuf,0,128);
    memset(readBuf,0,sizeof(readBuf));
    readEep(fd,lDevAddress,128,128,(char * )readBuf);
    printBuf(readBuf,128,128);
    closeEep(fd);

   //#################################
}
void MainWindow::clearB()
{
    resultText->clear();

}
void MainWindow::exitB()
{
    MainWindow::close();
    QApplication::exit();
}
int MainWindow::printBuf(const unsigned char *readBuf,int regAddr,int num)
{
    int i = 0,j = 0;
    unsigned char c = 0;
    char bufStr[2000];
    //##################
       ofstream output("output.ext",ios::out | ios::trunc);

    #if 0
       for (i=0;i<num;i++){
           output.width(2);
           output.fill('0');
    //       output.setf(ios_base::hex);
           output<<hex;
           output<<(int)(*(readBuf+i))<<" ";
           resultText->append(QString(*(readBuf+i)));
       }
    #endif
       output<<"   ";
       for ( i = 0; i < 16;i++) {
           output.width(2);
           output.fill('0');
           output<<hex;
           output<<i<<" ";
       }
       output<<endl;
       for ( i = 0; i < num/16;i++) {
      //     printf("%2x: ",i+regAddr/16);
           output.width(2);
           output.fill('0');
           output<<hex;
           output<<(i+regAddr/16)<<" ";
           for (j = 0;j<16; j++){
               //printf("%2x ",*(buf+i*16+j));
               output.width(2);
               output.fill('0');
               output<<hex;
               output<<int(*(readBuf+i*16+j))<<" ";
           }
           //printf(" ");
           output<<" ";
           for (j = 0;j<16; j++){
               c = *(readBuf+i*16+j);
               output.width(1);
               if(c>='a' && c <= 'z'){
                   //printf("%c ",c);
                   output<<c;
                   output<<" ";
               }else if(c>='A' && c <= 'Z'){
                   //printf("%c ",c);
                   output<<c;
                   output<<" ";
               }else if(c>='0' && c <= '9'){
                   //printf("%c ",c);
                   output<<c;
                   output<<" ";
               }else if(c == '-'){
                   //printf("%c ",c);
                   output<<c;
                   output<<" ";
               }else{
                   output<<" ";
               }
           }
           //printf("\n");
           output<<endl;
       }
       //printf("\n");
       output<<endl;

       output.close();
    //#################################
        ifstream input("output.ext",ios::in);
        for(i=0;i<input.get();i++){
            memset(bufStr,0,sizeof(bufStr));
            input.getline(bufStr,500);
            cout<<bufStr<<endl;
            resultText->append(bufStr);
        }
        input.close();
        return 0;
}
