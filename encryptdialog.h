#ifndef ENCRYPTDIALOG_H
#define ENCRYPTDIALOG_H
#include <QtGui>
#include <QDialog>
#include <QTime>
#include <QFile>
#include <fstream>

class EncryptDialog : public QDialog
{
    Q_OBJECT
    public:
        EncryptDialog(QWidget *parent = 0, const QString& algorithmName = "unknown");

        virtual void encryptalgo(std::ifstream& in, std::ofstream& out) = 0;
        virtual void decryptalgo(std::ifstream& in, std::ofstream& out) = 0;

    public slots:
        void encrypt();
        void decrypt();
        virtual void update() = 0;
        void chooseFile();

    protected:
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

        std::string getFileExtension(const std::string& path);
        long long getFileSize(std::ifstream &file);
        bool isValidFilePath(const QString& path);
        bool isValidOutputPath(const QString& path);
};

#endif // ENCRYPTDIALOG_H
