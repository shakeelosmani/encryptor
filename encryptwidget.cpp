#include "encryptwidget.h"
#include <fstream>
#include <istream>
#include <QTime>

encryptWidget::encryptWidget()
{
    encryptButton = new QPushButton("Start encryption");
    encryptButton->setFixedSize(150, 30);
    encryptButton->setStyleSheet("font:bold");
    encryptButton->setEnabled(false);
    encryptionLabel = new QLabel("Encryption: ", this);
    encryptionBox = new QComboBox(this);
    encryptionBox->addItem("XOR");
    encryptionBox->addItem("Caesar");
    encryptionBox->addItem("TEA");

    filePathEdit = new QLineEdit(this);
    filePathLabel = new QLabel("Choose file: ");
    fileButton = new QPushButton("Choose...", this);
    filePathEdit->setFixedWidth(250);

    keyEdit = new QLineEdit(this);
    keyLabel = new QLabel("Key: ");
    approveLabel = new QLabel;

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(encryptionLabel, 0, 0);
    gridLayout->addWidget(encryptionBox, 0, 1);
    gridLayout->addWidget(filePathLabel, 1, 0);
    gridLayout->addWidget(filePathEdit, 1, 1);
    gridLayout->addWidget(fileButton, 1, 2);
    gridLayout->addWidget(keyLabel, 2, 0);
    gridLayout->addWidget(keyEdit, 2, 1);
    gridLayout->addWidget(approveLabel, 2, 2);

    QGroupBox* groupBox = new QGroupBox;

    groupBox->setLayout(gridLayout);
    mainLayout->addWidget(groupBox, 0, Qt::AlignCenter);
    mainLayout->addWidget(encryptButton, 0, Qt::AlignCenter);
    setLayout(mainLayout);

    connect(keyEdit, SIGNAL(textChanged(QString)), this, SLOT(testKey()));
    connect(keyEdit, SIGNAL(textChanged(QString)), this, SLOT(update()));
    connect(filePathEdit, SIGNAL(textChanged(QString)), this, SLOT(update()));
    connect(encryptButton, SIGNAL(clicked()), this, SLOT(encrypt()));
    connect(fileButton, SIGNAL(clicked()), this, SLOT(chooseFile()));

}

void encryptWidget::encrypt()
{
    if(encryptionBox->currentText() == "XOR")
        XOR();
    else if(encryptionBox->currentText() == "Caesar")
        Caesar();

}

bool encryptWidget::readTextFile(const std::string &path, std::string &text)
{
    std::ifstream file;
    file.open(path.c_str());
    if(!file.is_open())
        return false;

    text = "";
    char c;
    while(!file.eof())
    {
        file.get(c);
        text += c;
    }
    return true;
}

void encryptWidget::saveTextFile(const std::string& path, const std::string& text)
{
    std::ofstream file2;
    file2.open(path.c_str(), std::ofstream::binary);
    if(!file2.is_open())
        return;
    file2<<text;
    file2.close();
}

void encryptWidget::Caesar()
{
    bool isInt = false;
    unsigned int key = keyEdit->text().toUInt(&isInt);
    if(!isInt || (isInt && key > 25))
    {
        QMessageBox::critical(this, "Wrong key", "Key must be an unsigned integer no higher than 25.");
        return;
    }

    std::string path = filePathEdit->text().toStdString();
    if(getFileExtension(path) != "txt")
    {
        QMessageBox::critical(this, "Wrong file type", "You must select a text file.");
        return;
    }
    std::string text;
    if(!readTextFile(path, text))
    {
        QMessageBox::critical(this, "Error", "Could not read file.\nPerhaps the path was not correct or it was not a text file.");
        return;
    }

    for(int i = 0; i < text.size(); i++)
    {
        if(text[i] != ' ' && text[i] != '\n') //check for spaces and newlines and let them be
        text[i] += key;
    }

    saveTextFile(path, text);
}

std::string encryptWidget::getFileExtension(const std::string& path)
{
    if(path.find_last_of('.') != std::string::npos)
        return path.substr(path.find_last_of('.')+1);
    return "";
}

long long encryptWidget::getFileSize(std::ifstream& file) //why no stat()? to make sure files over 2GB are correctly interpreted on 32-bit machines.
{
    file.seekg(0, std::ios::end);
    long long size = file.tellg();
    file.seekg(0);
    return size;
}

void encryptWidget::XOR()
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
        int i = 0;
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

void encryptWidget::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this);
    if(!filePath.isEmpty())
        filePathEdit->setText(filePath);
}

void encryptWidget::update()
{
    if(!filePathEdit->text().isEmpty() && !keyEdit->text().isEmpty())
    {
        encryptButton->setEnabled(true);
    }
    else
        encryptButton->setEnabled(false);
}

void encryptWidget::testKey()
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
