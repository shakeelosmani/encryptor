#ifndef ENCRYPTIONALGORITHM_H
#define ENCRYPTIONALGORITHM_H
#include <fstream>
#include <string>

class EncryptionAlgorithm
{
    public:
        EncryptionAlgorithm(std::string name = "unknown");

        virtual void encrypt(std::ifstream& in, std::ofstream& out) = 0;
        virtual void decrypt(std::ifstream& in, std::ofstream& out) = 0;

        std::string getAlgorithmName();

    private:
        std::string name;
};

#endif // ENCRYPTIONALGORITHM_H
