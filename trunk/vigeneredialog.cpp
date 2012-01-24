// File encoding: UTF-8
#include "vigeneredialog.h"

// Public:
    VigenereDialog::VigenereDialog(QWidget* parent)
    : EncryptDialog(parent, QString::fromUtf8("Vigenère"))
    {
        setWindowTitle(QString::fromUtf8("Vigenère"));
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
    void VigenereDialog::encryptalgo(std::ifstream& in, std::ofstream& out)
    {
        // Get the key
        const std::string key = keyEdit->text().toStdString();
        std::string::const_iterator keyChr = key.begin();

        // Start the encryption
        char chr;
        while(in.get(chr) && out)
        {
            out<<char(chr + *keyChr);
            if(++keyChr == key.end())
                keyChr = key.begin();
        }
    }

    void VigenereDialog::decryptalgo(std::ifstream& in, std::ofstream& out)
    {
        // Get the key
        const std::string key = keyEdit->text().toStdString();
        std::string::const_iterator keyChr = key.begin();

        // Start the encryption
        char chr;
        while(in.get(chr) && out)
        {
            out<<char(chr - *keyChr);
            if(++keyChr == key.end())
                keyChr = key.begin();
        }
    }

    void VigenereDialog::update()
    {
        const bool enable = isValidFilePath(filePathEdit->text()) && !keyEdit->text().isEmpty() && isValidOutputPath(outputPathEdit->text());
        encryptButton->setEnabled(enable);
        decryptButton->setEnabled(enable);
    }
