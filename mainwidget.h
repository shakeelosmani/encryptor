#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "encryptdialog.h"
#include <QMainWindow>

class MainWidget : public QMainWindow
{
    Q_OBJECT

    public:
        MainWidget(QWidget* parent = 0);
        ~MainWidget();

    public slots:
        void start();

    private:
        QLabel* encryptorLabel;
        QComboBox* encryptionBox;
        QPushButton* startButton;
        EncryptDialog* dlgEncrypt;
};

#endif // MAINWINDOW_H
