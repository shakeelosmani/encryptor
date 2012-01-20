#include "encryptdialog.h"

EncryptDialog::EncryptDialog(QWidget *parent) : QDialog(parent)
{
    encryptButton = new QPushButton("Encrypt");
    encryptButton->setEnabled(false);

    filePathEdit = new QLineEdit(this);
    filePathLabel = new QLabel("Choose file: ");
    fileButton = new QPushButton("...", this);
    fileButton->setFixedWidth(25);
    filePathEdit->setMinimumWidth(250);

    outputPathEdit = new QLineEdit(this);
    outputPathLabel = new QLabel("Output file: ");
    outputButton = new QPushButton("...", this);
    outputButton->setFixedWidth(25);
    outputPathEdit->setMinimumWidth(250);

    decryptButton = new QPushButton("Decrypt", this);
    decryptButton->setEnabled(false);
    connect(filePathEdit, SIGNAL(textChanged(QString)), this, SLOT(update()));
    connect(outputPathEdit, SIGNAL(textChanged(QString)), this, SLOT(update()));
    connect(encryptButton, SIGNAL(clicked()), this, SLOT(encrypt()));
    connect(decryptButton, SIGNAL(clicked()), this, SLOT(decrypt()));
    connect(fileButton, SIGNAL(clicked()), this, SLOT(chooseFile()));
}


void EncryptDialog::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this);
    if(!filePath.isEmpty())
    {
        filePathEdit->setText(filePath);
        if(outputPathEdit->text().isEmpty())
            outputPathEdit->setText(filePath+" - encrypted");
    }
}

bool EncryptDialog::readTextFile(const std::string &path, std::string &text)
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

void EncryptDialog::saveTextFile(const std::string& path, const std::string& text)
{
    std::ofstream file2;
    file2.open(path.c_str(), std::ofstream::binary);
    if(!file2.is_open())
        return;
    file2<<text;
    file2.close();
}

std::string EncryptDialog::getFileExtension(const std::string& path)
{
    if(path.find_last_of('.') != std::string::npos)
        return path.substr(path.find_last_of('.')+1);
    return "";
}

long long EncryptDialog::getFileSize(std::ifstream& file) //why no stat()? to make sure files over 2GB are correctly interpreted on 32-bit machines.
{
    file.seekg(0, std::ios::end);
    long long size = file.tellg();
    file.seekg(0);
    return size;
}

bool EncryptDialog::isValidFilePath(const QString& path)
{
    return QFile::exists(path);
}

bool EncryptDialog::isValidOutputPath(const QString& path)
{
    int pos = path.lastIndexOf('/');
    QString dirpath = path.left(pos+1);
    QDir dir(dirpath);
    return dir.exists(); //no static func avaiblable, sadly
}

