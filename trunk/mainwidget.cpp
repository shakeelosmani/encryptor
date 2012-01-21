// File encoding: UTF-8
#include "mainwidget.h"
#include "xordialog.h"
#include "vigeneredialog.h"
#include "caesardialog.h"

// Public:
    MainWidget::MainWidget(QWidget* parent)
    : QMainWindow(parent), dlgEncrypt(0)
    {
        // Some general settings for this window
        setWindowTitle("Encryptor");
        setStyleSheet("QPushButton {font:bold}");

        // Create the interface
        encryptionBox = new QComboBox(this);
        encryptionBox->addItem("XOR");
        encryptionBox->addItem("Caesar");
        encryptionBox->addItem("TEA");
        encryptionBox->addItem(QString::fromUtf8("Vigenère"));
        startButton = new QPushButton("Start!", this);
        encryptorLabel = new QLabel("Encryptor r3");
        encryptorLabel->setStyleSheet("font:bold 30px");

        // Create the central widget
        QWidget* centWidget = new QWidget(this);
        QVBoxLayout* mainLayout = new QVBoxLayout();
        QHBoxLayout* encryptLayout= new QHBoxLayout();
        mainLayout->addWidget(encryptorLabel);
        encryptLayout->addWidget(encryptionBox);
        encryptLayout->addWidget(startButton);
        mainLayout->addLayout(encryptLayout);
        centWidget->setLayout(mainLayout);
        setCentralWidget(centWidget);

        // Connect the interface to the necessary slots
        connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    }

    MainWidget::~MainWidget()
    {
        delete encryptionBox;
        delete startButton;
        delete encryptorLabel;
        if(dlgEncrypt)  delete dlgEncrypt;
    }

// Public slots:
    void MainWidget::start()
    {
        // Clean up the old dialog
        if(dlgEncrypt)
        {
            delete dlgEncrypt;
            dlgEncrypt = 0;
        }

        // Determine what type of dialog should be created
        if(encryptionBox->currentText() == "XOR")
        {
            dlgEncrypt = new XORDialog(this);
            dlgEncrypt->show();
        }
        else if(encryptionBox->currentText() == QString::fromUtf8("Vigenère"))
        {
            dlgEncrypt = new VigenereDialog(this);
            dlgEncrypt->show();
        }
        else if(encryptionBox->currentText() == "Caesar")
        {
            dlgEncrypt = new CaesarDialog(this);
            dlgEncrypt->show();
        }
    }
