#ifndef CAESARDIALOG_H
#define CAESARDIALOG_H
#include "encryptdialog.h"

class CaesarDialog : public EncryptDialog
{
    public:
        CaesarDialog(QWidget* parent = 0);

    public slots:
        void encrypt();
        void decrypt();
        void update();

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;
};

#endif // CAESARDIALOG_H
