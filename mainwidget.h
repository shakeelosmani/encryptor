#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "decryptwidget.h"
#include "encryptwidget.h"
#include <QtGui>

class MainWidget : public QWidget
{
    Q_OBJECT

    public:
        MainWidget(QWidget *parent = 0);
        ~MainWidget();

    private:
        QPushButton* encryptButton;
        QPushButton* decryptButton;
        QLabel* copyrightLabel;


    public slots:
        void encrypt();
        void decrypt();
};

#endif // MAINWINDOW_H
