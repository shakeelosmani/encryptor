#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QPushButton {font:bold}");
    encryptButton = new QPushButton("Encrypt", this);
    decryptButton = new QPushButton("Decrypt", this);
    copyrightLabel = new QLabel("Copryright Winand. All rights preserved.");
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(encryptButton);
    buttonLayout->addWidget(decryptButton);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(copyrightLabel);
    setLayout(mainLayout);



    connect(encryptButton, SIGNAL(clicked()), this, SLOT(encrypt()));
    connect(decryptButton, SIGNAL(clicked()), this, SLOT(decrypt()));
}

MainWidget::~MainWidget()
{

}

void MainWidget::encrypt()
{
    encryptWidget encryptdialog;
    encryptdialog.exec();
}

void MainWidget::decrypt()
{

}
