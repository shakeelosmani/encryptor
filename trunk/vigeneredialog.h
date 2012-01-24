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
        void encryptalgo(std::ifstream& in, std::ofstream& out);
        void decryptalgo(std::ifstream& in, std::ofstream& out);

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;

};

#endif // VIGENEREDIALOG_H
