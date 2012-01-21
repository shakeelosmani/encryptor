#include "encryptdialog.h"

EncryptDialog::EncryptDialog(QWidget *parent) : QDialog(parent)
{
    encryptButton = new QPushButton("Encrypt");
    encryptButton->setEnabled(false);

    decryptButton = new QPushButton("Decrypt", this);
    decryptButton->setEnabled(false);

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

    connect(filePathEdit, SIGNAL(textChanged(QString)), this, SLOT(update()));
    connect(outputPathEdit, SIGNAL(textChanged(QString)), this, SLOT(update()));
    connect(encryptButton, SIGNAL(clicked()), this, SLOT(encrypt()));
    connect(decryptButton, SIGNAL(clicked()), this, SLOT(decrypt()));
    connect(fileButton, SIGNAL(clicked()), this, SLOT(chooseFile()));
}

void EncryptDialog::encrypt()
{
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

    encryptalgo(in, out);

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

void EncryptDialog::decrypt()
{
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

    std::string algorithmname = decryptalgo(in, out);

    // Check if everything went well
    if(!in.eof())
        QMessageBox::critical(this, "Error while reading the file", "An error occurred while reading from the file: "+filePathEdit->text());
    else if(!out)
        QMessageBox::critical(this, "Error while writing the file", "An error occurred while writing to the file: "+outputPathEdit->text());
    else
        QMessageBox::information(this, "Successfull Decryption", QString("The file was succesfully decrypted using the %1 algorithm.\n").arg(algorithmname.c_str()) + QString("Time taken: %1 ms").arg(timer.elapsed()));

    // Close the files
    in.close();
    out.close();
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
    int pos = path.lastIndexOf('/'); //we need to cut the file name out
    QString dirpath = path.left(pos+1);
    QDir dir(dirpath);
    return dir.exists(); //no static func avaiblable, sadly
}

