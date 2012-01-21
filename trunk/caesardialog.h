#ifndef CAESARDIALOG_H
#define CAESARDIALOG_H
#include "encryptdialog.h"

class CaesarDialog : public EncryptDialog
{
    public:
        CaesarDialog(QWidget* parent = 0);

    public slots:
        void update();

    protected:
        std::string encryptalgo(std::ifstream& in, std::ofstream& out);
        std::string decryptalgo(std::ifstream& in, std::ofstream& out);

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;
};

#endif // CAESARDIALOG_H
