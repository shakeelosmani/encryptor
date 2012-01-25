#ifndef VIGENERE_H
#define VIGENERE_H
#include "encryptionalgorithm.h"

class Vigenere : public EncryptionAlgorithm
{
    public:
        Vigenere(const std::string& key = "");

        void encrypt(std::ifstream &in, std::ofstream &out);
        void decrypt(std::ifstream &in, std::ofstream &out);

        std::string getKey();
        void setKey(const std::string& newKey);

    private:
        std::string key;
};

#endif // VIGENERE_H
