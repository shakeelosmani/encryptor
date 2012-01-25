#ifndef CAESARDIALOG_H
#define CAESARDIALOG_H
#include "caesar.h"
#include "encryptdialog.h"

class CaesarDialog : public EncryptDialog
{
    Q_OBJECT

    public:
        CaesarDialog(QWidget* parent = 0);

    public slots:
        void update();

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;
};

#endif // CAESARDIALOG_H
