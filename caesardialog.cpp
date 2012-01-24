#include "caesardialog.h"

CaesarDialog::CaesarDialog(QWidget* parent)
    : EncryptDialog(parent, "Caesar")
{
    setWindowTitle("Caesar");
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

// Public slots:
void CaesarDialog::encryptalgo(std::ifstream& in, std::ofstream& out)
{
    // Get the key
    bool converted;
    const int key = keyEdit->text().toInt(&converted);
    if(!converted)
        QMessageBox::critical(this, "Wrong key", "The key for the Caesar algorithm has to be an integer");

    // Start the encryption
    char chr;
    while(in.get(chr) && out)
    {
        out<<char(chr + key);
    }
}

void CaesarDialog::decryptalgo(std::ifstream& in, std::ofstream& out)
{
    // Get the key
    bool converted;
    const int key = keyEdit->text().toInt(&converted);
    if(!converted)
        QMessageBox::critical(this, "Wrong key", "The key for the Caesar algorithm has to be an integer");

    // Start the encryption
    char chr;
    while(in.get(chr) && out)
    {
        out<<char(chr - key);
    }
}

void CaesarDialog::update()
{
    const bool enable = isValidFilePath(filePathEdit->text()) && !keyEdit->text().isEmpty() && isValidOutputPath(outputPathEdit->text());
    encryptButton->setEnabled(enable);
    decryptButton->setEnabled(enable);
}

