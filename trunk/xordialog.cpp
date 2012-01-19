#include "xordialog.h"

XORDialog::XORDialog(QWidget *parent) : EncryptDialog(parent)
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
    gridLayout->addWidget(keyLabel, 1, 0);
    gridLayout->addWidget(keyEdit, 1, 1);
    gridLayout->addWidget(approveLabel, 1, 2);
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    connect(encryptButton, SIGNAL(clicked()), this, SLOT(encrypt()));
    connect(decryptButton, SIGNAL(clicked()), this, SLOT(encrypt()));
    connect(keyEdit, SIGNAL(textChanged(QString)), this, SLOT(testKey()));
    connect(keyEdit, SIGNAL(textChanged(QString)), this, SLOT(update()));
}

void XORDialog::encrypt()
{
    std::string path = filePathEdit->text().toStdString();
    std::ifstream file(path.c_str(), std::ifstream::binary);
    std::ofstream out((path+" - encrypted."+getFileExtension(path)).c_str(), std::ofstream::binary | std::ofstream::app); //output dir and name to be made variable!

    long long fileSize = getFileSize(file);
    QElapsedTimer timer;
    timer.start();
    std::string key = keyEdit->text().toStdString();

    while(fileSize > 0)
    {
        long blocksize = 5000000; //standard blocksize (50 megabyte (ridiculously large, i know!) can be made variable later on)
        if(fileSize < 5000000) //the total size is smaller, we obviously change it to the full file size!
            blocksize = fileSize;
        fileSize -= 5000000; //decrement the total size with 50 mega each time

        char* buffer = new char[blocksize];
        file.read(buffer, blocksize);

        //start encryption
        unsigned i = 0;
        for(long long j = 0; j < blocksize; j++)
        {
            i++;
            if(i > key.size())
                i = 0;
            buffer[j] = key[i] ^ buffer[j];
        }

        out.write(buffer, blocksize);
        delete[] buffer;
    }
    file.close();
    out.close();

    unsigned long elapsedTime = timer.elapsed();
    QMessageBox::information(this, "Successfull Encryption", QString("The file was succesfully converted using the XOR algorithm.\nTime taken: %1 ms").arg(elapsedTime));
}

void XORDialog::update()
{
    if(!filePathEdit->text().isEmpty() && !keyEdit->text().isEmpty())
    {
        encryptButton->setEnabled(true);
    }
    else
        encryptButton->setEnabled(false);
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
