#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QPushButton {font:bold}");
    encryptionBox = new QComboBox(this);
    encryptionBox->addItem("XOR");
    encryptionBox->addItem("Caesar");
    encryptionBox->addItem("TEA");
    startButton = new QPushButton("Start!", this);
    encryptorLabel = new QLabel("Encryptor r3");
    encryptorLabel->setStyleSheet("font:bold 30px");

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(encryptorLabel);
    mainLayout->addWidget(encryptionBox);
    mainLayout->addWidget(startButton);
    setLayout(mainLayout);

    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
}

MainWidget::~MainWidget()
{

}

void MainWidget::start()
{
    if(encryptionBox->currentText() == "XOR")
    {
        XORDialog* dlg = new XORDialog;
        dlg->show();
    }
}
