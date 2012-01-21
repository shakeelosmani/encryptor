#include "caesardialog.h"

CaesarDialog::CaesarDialog(QWidget* parent) : EncryptDialog(parent)
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
void CaesarDialog::encrypt()
{
    // Get the key
    bool converted;
    const int key = keyEdit->text().toInt(&converted);
    if(!converted)
        QMessageBox::critical(this, "Wrong key", "The key for the Caesar algorithm has to be an integer");

    // Start a timer to see how long it takes
    QElapsedTimer timer;
    timer.start();

    // Open the files
    std::ifstream in(filePathEdit->text().toAscii(), std::ios::binary);
    std::ofstream out(outputPathEdit->text().toAscii(), std::ios::binary);

    // Check if the files are opened succesful
    if(!in)
        QMessageBox::critical(this, "Error while opening the file", "The file "+filePathEdit->text()+" couldn't be opened for reading!");
    if(!out)
        QMessageBox::critical(this, "Error while opening the file", "The file "+outputPathEdit->text()+" couldn't be opened for writing!");
    if(!in || !out)
    {
        in.close();
        out.close();
        return;
    }

    // Start the encryption
    char chr;
    while(in.get(chr) && out)
    {
        out<<char(chr + key);
    }

    // Check if everything went well
    if(!in.eof())
        QMessageBox::critical(this, "Error while reading the file", "An error occurred while reading from the file: "+filePathEdit->text());
    else if(!out)
        QMessageBox::critical(this, "Error while writing the file", "An error occurred while writing to the file: "+outputPathEdit->text());
    else
        QMessageBox::information(this, "Successfull Encryption", QString::fromUtf8("The file was succesfully encrypted using the VigenÃ¨re algorithm.\nTime taken: %1 ms").arg(timer.elapsed()));

    // Close the files
    in.close();
    out.close();
}

void CaesarDialog::decrypt()
{
    // Get the key
    bool converted;
    const int key = keyEdit->text().toInt(&converted);
    if(!converted)
        QMessageBox::critical(this, "Wrong key", "The key for the Caesar algorithm has to be an integer");

    // Start a timer to see how long it takes
    QElapsedTimer timer;
    timer.start();

    // Open the files
    std::ifstream in(filePathEdit->text().toAscii(), std::ios::binary);
    std::ofstream out(outputPathEdit->text().toAscii(), std::ios::binary);

    // Check if the files are opened succesful
    if(!in)
        QMessageBox::critical(this, "Error while opening the file", "The file "+filePathEdit->text()+" couldn't be opened for reading!");
    if(!out)
        QMessageBox::critical(this, "Error while opening the file", "The file "+outputPathEdit->text()+" couldn't be opened for writing!");
    if(!in || !out)
    {
        in.close();
        out.close();
        return;
    }

    // Start the encryption
    char chr;
    while(in.get(chr) && out)
    {
        out<<char(chr - key);
    }

    // Check if everything went well
    if(!in.eof())
        QMessageBox::critical(this, "Error while reading the file", "An error occurred while reading from the file: "+filePathEdit->text());
    else if(!out)
        QMessageBox::critical(this, "Error while writing the file", "An error occurred while writing to the file: "+outputPathEdit->text());
    else
        QMessageBox::information(this, "Successfull Encryption", QString::fromUtf8("The file was succesfully decrypted using the VigenÃ¨re algorithm.\nTime taken: %1 ms").arg(timer.elapsed()));

    // Close the files
    in.close();
    out.close();
}

void CaesarDialog::update()
{
    encryptButton->setEnabled(isValidFilePath(filePathEdit->text()) && !keyEdit->text().isEmpty() && isValidOutputPath(outputPathEdit->text()));
    decryptButton->setEnabled(isValidFilePath(filePathEdit->text()) && !keyEdit->text().isEmpty() && isValidOutputPath(outputPathEdit->text()));
}

