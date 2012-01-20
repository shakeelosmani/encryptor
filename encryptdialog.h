#ifndef ENCRYPTDIALOG_H
#define ENCRYPTDIALOG_H
#include <QtGui>
#include <QDialog>
#include <QTime>
#include <fstream>

class EncryptDialog : public QDialog
{
    Q_OBJECT
    public:
        EncryptDialog(QWidget *parent = 0);

    public slots:
        virtual void encrypt() = 0;
        virtual void decrypt() = 0;
        virtual void update() = 0;
        void chooseFile();

    protected:
        QLineEdit* filePathEdit;
        QLabel* filePathLabel;
        QPushButton* fileButton;

        QLineEdit* outputPathEdit;
        QLabel* outputPathLabel;
        QPushButton* outputButton;

        QPushButton* encryptButton;
        QPushButton* decryptButton;

        bool readTextFile(const std::string& path, std::string& text);
        void saveTextFile(const std::string& path, const std::string& text);
        std::string getFileExtension(const std::string& path);
        long long getFileSize(std::ifstream &file);
        bool isValidFilePath(const QString& path);
        bool isValidOutputPath(const QString& path);
};

#endif // ENCRYPTDIALOG_H
