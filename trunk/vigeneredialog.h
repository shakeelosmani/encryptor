#ifndef VIGENEREDIALOG_H
#define VIGENEREDIALOG_H

#include "encryptdialog.h"

class VigenereDialog : public EncryptDialog
{
    Q_OBJECT

    public:
        VigenereDialog(QWidget* parent = 0);

    public slots:
        void encrypt();
        void decrypt();
        void update();

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;

};

#endif // VIGENEREDIALOG_H
