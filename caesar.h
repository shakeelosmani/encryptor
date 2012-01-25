#ifndef CAESAR_H
#define CAESAR_H
#include "encryptionalgorithm.h"

class Caesar : public EncryptionAlgorithm
{
    public:
        Caesar(const char& key = NULL);

        void encrypt(std::ifstream &in, std::ofstream &out);
        void decrypt(std::ifstream &in, std::ofstream &out);

        char getKey();
        void setKey(const char& newKey);

    private:
        char key;
};

#endif // CAESAR_H
