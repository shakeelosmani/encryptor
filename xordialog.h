#ifndef XORDIALOG_H
#define XORDIALOG_H
#include "encryptdialog.h"

class XORDialog : public EncryptDialog
{
    Q_OBJECT
    public:
        XORDialog(QWidget *parent = 0);

    public slots:
        void encrypt();
        void update();
        void testKey();

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;
        QLabel* approveLabel;

    
};

#endif // XORDIALOG_H
