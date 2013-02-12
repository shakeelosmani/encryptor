#include "caesardialog.h"

CaesarDialog::CaesarDialog(QWidget* parent)
: EncryptDialog(parent, "Caesar")
{
    keyEdit = new QLineEdit(this);
    keyEdit->setMaxLength(1);
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

void CaesarDialog::encrypt(std::ifstream &in, std::ofstream &out)
{
    const char key = keyEdit->text().at(0).toAscii();
    char chr;
    while(in.get(chr) && out)
        out << static_cast<char>(chr + key);
}

void CaesarDialog::decrypt(std::ifstream &in, std::ofstream &out)
{
    const char key = keyEdit->text().at(0).toAscii();
    char chr;
    while(in.get(chr) && out)
        out << static_cast<char>(chr - key);
}

void CaesarDialog::update()
{
    const bool enable = !keyEdit->text().isEmpty() && isValidFilePath(filePathEdit->text()) && isValidOutputPath(outputPathEdit->text());
    encryptButton->setEnabled(enable);
    decryptButton->setEnabled(enable);
}
