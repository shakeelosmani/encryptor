#include "caesardialog.h"

CaesarDialog::CaesarDialog(QWidget* parent)
    : EncryptDialog(parent, "Caesar")
{
    algorithm = new Caesar;

    keyEdit = new QLineEdit(this);
    keyLabel = new QLabel("Key: ");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(encryptButton);
    buttonLayout->addWidget(decryptButton);
    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->addWidget(filePathLabel, 0, 0);
    gridLayout->addWidget(filePathEdit, 0, 1);
    gridLayout->addWidget(fileButton, 0, 2);
    gridLayout->addWidget(outputPathLabel, 1, 0);
    gridLayout->addWidget(outputPathEdit, 1, 1);
    gridLayout->addWidget(outputButton, 1, 2);
    gridLayout->addWidget(keyLabel, 2, 0);
    gridLayout->addWidget(keyEdit, 2, 1);
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(keyEdit, SIGNAL(textChanged(QString)), this, SLOT(update()));
}

void CaesarDialog::update()
{
    const bool enable = isValidFilePath(filePathEdit->text()) && isValidOutputPath(outputPathEdit->text());
    encryptButton->setEnabled(enable);
    decryptButton->setEnabled(enable);
    if(enable)
    {
        delete algorithm;
        algorithm = new Caesar;
    }
}

