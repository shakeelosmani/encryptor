#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("QPushButton {font:bold}");
    encryptionBox = new QComboBox(this);
    encryptionBox->addItem("XOR");
    encryptionBox->addItem("Caesar");
    encryptionBox->addItem("TEA");
    encryptionBox->setFixedWidth(75);
    startButton = new QPushButton("Start!", this);
    startButton->setFixedSize(150, 30);
    encryptorLabel = new QLabel("Encryptor r3");
    encryptorLabel->setStyleSheet("font:bold 30px");

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* encryptLayout= new QHBoxLayout;
    encryptLayout->addWidget(encryptionBox);
    encryptLayout->addWidget(startButton);
    mainLayout->addWidget(encryptorLabel);
    mainLayout->addLayout(encryptLayout);

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
