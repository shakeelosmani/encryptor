#include "xordialog.h"

XORDialog::XORDialog(QWidget *parent)
    : EncryptDialog(parent, "XOR")
{
    keyEdit = new QLineEdit(this);
    keyLabel = new QLabel("Key: ");
    approveLabel = new QLabel(this);

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
    gridLayout->addWidget(approveLabel, 2, 2);
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(keyEdit, SIGNAL(textChanged(QString)), this, SLOT(testKey()));
    connect(keyEdit, SIGNAL(textChanged(QString)), this, SLOT(update()));
}

void XORDialog::encrypt(std::ifstream& in, std::ofstream& out)
{
    const std::string key = keyEdit->text().toStdString();
    std::string::const_iterator keyChr = key.begin();

    // Start the encryption
    char chr;
    while(in.get(chr) && out)
    {
        out << static_cast<char>(chr ^ (*keyChr));
        if(++keyChr == key.end())
            keyChr = key.begin();
    }
}

void XORDialog::decrypt(std::ifstream &in, std::ofstream &out)
{
    // XOR decryption is the same as the encryption
    encrypt(in, out);
}

void XORDialog::update()
{
    const bool enable = isValidFilePath(filePathEdit->text()) && isValidOutputPath(outputPathEdit->text()) && !keyEdit->text().isEmpty();
    encryptButton->setEnabled(enable);
    decryptButton->setEnabled(enable);
}

void XORDialog::testKey()
{
    QString key = keyEdit->text();
    if(key.length() < 6)
    {
        approveLabel->setText("Very Weak");
        approveLabel->setStyleSheet("color:red; font:bold");
    }
    else if(key.length() < 12)
    {
        approveLabel->setText("Weak");
        approveLabel->setStyleSheet("color:red; font:bold");
    }
    else if(key.length() < 18)
    {
        approveLabel->setText("Moderate");
        approveLabel->setStyleSheet("color:yellow; font:bold");
    }
    else if(key.length() < 24)
    {
        approveLabel->setText("Strong");
        approveLabel->setStyleSheet("color:green; font:bold");
    }
    else
    {
        approveLabel->setText("Very Strong");
        approveLabel->setStyleSheet("color:green; font:bold");
    }
}
