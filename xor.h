#ifndef XOR_H
#define XOR_H
#include "encryptionalgorithm.h"


class XOR : public EncryptionAlgorithm
{
    public:
        XOR(const std::string& key = "");

        void encrypt(std::ifstream &in, std::ofstream &out);
        void decrypt(std::ifstream &in, std::ofstream &out);

        std::string getKey();
        void setKey(const std::string& newKey);

    private:
        std::string key;

};

#endif // XOR_H
