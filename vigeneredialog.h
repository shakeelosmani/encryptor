#ifndef VIGENEREDIALOG_H
#define VIGENEREDIALOG_H

#include "encryptdialog.h"

class VigenereDialog : public EncryptDialog
{
    Q_OBJECT

    public:
        VigenereDialog(QWidget* parent = 0);

    public slots:
        void update();

    protected:
        std::string encryptalgo(std::ifstream& in, std::ofstream& out);
        std::string decryptalgo(std::ifstream& in, std::ofstream& out);

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;

};

#endif // VIGENEREDIALOG_H
