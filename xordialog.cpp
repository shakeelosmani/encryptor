#include "xordialog.h"

XORDialog::XORDialog(QWidget *parent) : EncryptDialog(parent)
{
    setWindowTitle("XOR");
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

void XORDialog::encrypt()
{
    std::string path = filePathEdit->text().toStdString();
    std::ifstream file(path.c_str(), std::ifstream::binary);
    std::ofstream out(outputPathEdit->text().toStdString().c_str(), std::ofstream::binary); //output dir and name to be made variable!

    if(!file)
        QMessageBox::critical(this, "Error while opening the file", "The file "+filePathEdit->text()+" couldn't be opened for reading!");
    if(!out)
        QMessageBox::critical(this, "Error while opening the file", "The file "+outputPathEdit->text()+" couldn't be opened for writing!");

    QElapsedTimer timer;
    timer.start();
    const std::string key = keyEdit->text().toStdString();
    std::string::const_iterator keyChr = key.begin();

    // Start the encryption
    char chr;
    while(file.get(chr) && out)
    {
        out<<char(chr ^ *keyChr);
        if(++keyChr == key.end())
            keyChr = key.begin();
    }

    file.close();
    out.close();

    unsigned long elapsedTime = timer.elapsed();
    QMessageBox::information(this, "Successfull Encryption", QString("The file was succesfully converted using the XOR algorithm.\nTime taken: %1 ms").arg(elapsedTime));
}

void XORDialog::update()
{
    if(isValidFilePath(filePathEdit->text()) &&
       isValidOutputPath(outputPathEdit->text()) &&
       !keyEdit->text().isEmpty())
    {
        encryptButton->setEnabled(true);
        decryptButton->setEnabled(true);
        return;
    }

    decryptButton->setEnabled(false);
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

void XORDialog::decrypt()
{
    encrypt();
}