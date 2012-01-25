#ifndef VIGENEREDIALOG_H
#define VIGENEREDIALOG_H
#include "vigenere.h"
#include "encryptdialog.h"

class VigenereDialog : public EncryptDialog
{
    Q_OBJECT

    public:
        VigenereDialog(QWidget* parent = 0);

    public slots:
        void update();

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;

};

#endif // VIGENEREDIALOG_H
