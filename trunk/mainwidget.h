#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "xordialog.h"
#include <QtGui>

class MainWidget : public QWidget
{
    Q_OBJECT

    public:
        MainWidget(QWidget *parent = 0);
        ~MainWidget();

    private:
        QLabel* encryptorLabel;
        QComboBox* encryptionBox;
        QPushButton* startButton;
        //QLabel* copyrightLabel;


    public slots:
        void start();
};

#endif // MAINWINDOW_H
