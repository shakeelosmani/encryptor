#include "encryptdialog.h"

EncryptDialog::EncryptDialog(QWidget *parent, const QString& algorithmName)
    : QDialog(parent), algorithmName(algorithmName)
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
    connect(outputButton, SIGNAL(clicked()), this, SLOT(chooseOutput()));
}

void EncryptDialog::encrypt()
{
    crypt(true);
}

void EncryptDialog::decrypt()
{
    crypt(false);
}

void EncryptDialog::crypt(const bool& ENCRYPT)
{
    // Start a timer to see how long it takes
    QElapsedTimer timer;
    timer.start();
    const std::string filePath = filePathEdit->text().toStdString();
    const std::string outputPath = outputPathEdit->text().toStdString();
    // Open the files
    std::ifstream in(filePath.c_str(), std::ios::binary);
    std::ofstream out((outputPath + " - temp").c_str(), std::ios::binary);

    // Check if the files are opened succesful
    if(!in)
        QMessageBox::critical(this, "Error while opening the file", "The file "+filePathEdit->text()+" couldn't be opened for reading!");
    if(!out)
        QMessageBox::critical(this, "Error while opening the file", "The temporary encryption file couldn't be opened for writing!");
    if(!in || !out)
    {
        in.close();
        out.close();
        return;
    }

    if(ENCRYPT)
        encryptalgo(in, out);
    else
        decryptalgo(in, out);

    // Check if everything went well
    if(!in.eof())
        QMessageBox::critical(this, "Error while reading the file", "An error occurred while reading from the file: "+filePathEdit->text());
    else if(!out)
        QMessageBox::critical(this, "Error while writing the file", "An error occurred while writing to the file: "+outputPathEdit->text());

    // Close the files
    in.close();
    out.close();

    if(QFile::exists(outputPathEdit->text())) //overwrite file?
        if(!QFile::remove(outputPathEdit->text())) //otherwise QFile::rename doesn't work
        {
            QFile::remove(outputPathEdit->text()+ " - temp"); //remove the temp file
            QMessageBox::critical(this, "Error overwriting file", "An error occurred while overwriting the file "+outputPathEdit->text());
        }
    if(QFile::rename(outputPathEdit->text() + " - temp", outputPathEdit->text()))
    {
        if(ENCRYPT)
            QMessageBox::information(this, "Successfull Encryption", QString("The file was succesfully encrypted using the %1 algorithm.\nTime taken: %2 ms").arg(algorithmName).arg(timer.elapsed()));
        else
            QMessageBox::information(this, "Successfull Decryption", QString("The file was succesfully decrypted using the %1 algorithm.\nTime taken: %2 ms").arg(algorithmName).arg(timer.elapsed()));
    }
}

void EncryptDialog::chooseFile()
{
    QString filePath = QFileDialog::getOpenFileName(this);
    if(!filePath.isEmpty())
    {
        filePathEdit->setText(filePath);
        if(outputPathEdit->text().isEmpty())
        {
            const QString extension = getFileExtension(filePath);
            outputPathEdit->setText(filePath.left(filePath.size() - extension.size()) + " - encrypted" + extension);
        }
    }
}

void EncryptDialog::chooseOutput()
{
    QString filePath = QFileDialog::getOpenFileName(this);
    if(!filePath.isEmpty())
        outputPathEdit->setText(filePath);
}

QString EncryptDialog::getFileExtension(const QString& path)
{
    const int lastDot = path.lastIndexOf('.');
    if(lastDot != -1)
        return path.right(path.size() - lastDot);
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

