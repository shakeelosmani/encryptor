#ifndef CAESARDIALOG_H
#define CAESARDIALOG_H
#include "encryptdialog.h"

class CaesarDialog : public EncryptDialog
{
    Q_OBJECT

    public:
        CaesarDialog(QWidget* parent = 0);

    public slots:
        void update();

    protected:
        void encryptalgo(std::ifstream& in, std::ofstream& out);
        void decryptalgo(std::ifstream& in, std::ofstream& out);

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;
};

#endif // CAESARDIALOG_H
