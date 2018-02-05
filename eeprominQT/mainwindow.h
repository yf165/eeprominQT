#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>

#define DEVICE "/dev/i2c-0"
#define DEVADDR 0x50


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
private slots:
    void readStart();
    void clearExit();
};

#endif // MAINWINDOW_H
