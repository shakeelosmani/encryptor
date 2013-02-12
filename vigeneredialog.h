#ifndef VIGENEREDIALOG_H
#define VIGENEREDIALOG_H

#include "encryptdialog.h"

class VigenereDialog : public EncryptDialog
{
    Q_OBJECT

    public:
        VigenereDialog(QWidget* parent = 0);

        virtual void encrypt(std::ifstream& in, std::ofstream& out);
        virtual void decrypt(std::ifstream& in, std::ofstream& out);

    public slots:
        void update();

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;

};

#endif // VIGENEREDIALOG_H
