#ifndef ENCRYPTDIALOG_H
#define ENCRYPTDIALOG_H

#include <QtGui>
#include <QDialog>
#include <QTime>
#include <QFile>
#include <fstream>
#include "encryptionalgorithm.h"

class EncryptDialog : public QDialog
{
    Q_OBJECT

    public:
        EncryptDialog(QWidget *parent = 0, const QString& algorithmName = "unknown");

        // Use the encryption/decryption algorithm on the given istream and write to the given ostream
        virtual void encrypt(std::ifstream& in, std::ofstream& out) = 0;
        virtual void decrypt(std::ifstream& in, std::ofstream& out) = 0;

    public slots:
        // Encrypt or decrypt the
        void doEncrypt();
        void doDecrypt();

        // Called when the contents of one of the fields has changed
        virtual void update() = 0;

        // Let the user choose an input or output file
        void chooseFile();
        void chooseOutput();

    protected:
        // Encrypt or decrypt the chosen file and save it to the chosen location
        // If ENCRYPT is true, the file is encrypted, if it's false the file is decrypted
        void crypt(const bool& ENCRYPT);

        QLineEdit* filePathEdit;
        QLabel* filePathLabel;
        QPushButton* fileButton;

        QLineEdit* outputPathEdit;
        QLabel* outputPathLabel;
        QPushButton* outputButton;

        QPushButton* encryptButton;
        QPushButton* decryptButton;

        QString algorithmName;

        QString getFileExtension(const QString& path);          // Returns the extension, including the (i.e. ".avi" is returned, not only "avi")
        long long getFileSize(std::ifstream &file);             // Get the size of a file (in bytes)
        bool isValidFilePath(const QString& path);              // Check whether the given path is valid (i.e. it exists)
        bool isValidOutputPath(const QString& path);            // Check whether the given output path is valid (i.e. the directory exists)
};

#endif // ENCRYPTDIALOG_H
