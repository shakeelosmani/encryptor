#ifndef CAESARDIALOG_H
#define CAESARDIALOG_H

#include "encryptdialog.h"

class CaesarDialog : public EncryptDialog
{
    Q_OBJECT

    public:
        CaesarDialog(QWidget* parent = 0);

        void encrypt(std::ifstream &in, std::ofstream &out);
        void decrypt(std::ifstream &in, std::ofstream &out);

    public slots:
        void update();

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;
};

#endif // CAESARDIALOG_H
