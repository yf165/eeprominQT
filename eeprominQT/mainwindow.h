#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QComboBox>
#define DEVICE "/dev/i2c-0"
#define DEVADDR 0x50
#define PAGEADDRESS 0x7f

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int printBuf(const unsigned char *buf,int regAddr,int num);
private:
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QTextBrowser *resultText;
    int fd ;
    QComboBox *devAddress;
    QComboBox *upperPage;

private slots:
    void readStart();
    void clearB();
    void exitB();
};

#endif // MAINWINDOW_H
