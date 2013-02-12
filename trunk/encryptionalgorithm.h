#ifndef ENCRYPTIONALGORITHM_H
#define ENCRYPTIONALGORITHM_H
#include <fstream>
#include <string>

class EncryptionAlgorithm
{
    public:
        EncryptionAlgorithm(std::string name = "unknown");


        std::string getAlgorithmName();

    private:
        std::string name;
};

#endif // ENCRYPTIONALGORITHM_H
