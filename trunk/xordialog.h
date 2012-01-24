#ifndef XORDIALOG_H
#define XORDIALOG_H
#include "encryptdialog.h"

class XORDialog : public EncryptDialog
{
    Q_OBJECT
    public:
        XORDialog(QWidget *parent = 0);

    public slots:
        void update();
        void testKey();

    protected:
        void encryptalgo(std::ifstream& in, std::ofstream& out);
        void decryptalgo(std::ifstream& in, std::ofstream& out);

    private:
        QLabel* keyLabel;
        QLineEdit* keyEdit;
        QLabel* approveLabel;

    
};

#endif // XORDIALOG_H
