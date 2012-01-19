#ifndef ENCRYPTWIDGET_H
#define ENCRYPTWIDGET_H
#include <QtGui>
#include <QDialog>

class encryptWidget : public QDialog
{
    Q_OBJECT

    public:
        explicit encryptWidget();

        QPushButton* encryptButton;
        QComboBox* encryptionBox;
        QLabel* encryptionLabel;

        QLineEdit* filePathEdit;
        QLabel* filePathLabel;
        QPushButton* fileButton;

        QLabel* keyLabel;
        QLineEdit* keyEdit;
        QLabel* approveLabel;

    public slots:
        void encrypt();
        void chooseFile();
        void update();
        void testKey();

    private:
        //encryption algos
        void XOR();
        void Caesar();
        void saveToFile(std::string path, std::string text);
        std::string findFileExtension(const std::string& path);
        long long getFileSize(std::ifstream &file);


};

#endif // ENCRYPTWIDGET_H
