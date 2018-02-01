#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QTextBrowser *resultText;
private slots:
    void readStart();
    void clearExit();
};

#endif // MAINWINDOW_H
