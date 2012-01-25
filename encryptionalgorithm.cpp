#include "encryptionalgorithm.h"

EncryptionAlgorithm::EncryptionAlgorithm(std::string name) : name(name)
{

}

std::string EncryptionAlgorithm::getAlgorithmName()
{
    return name;
}
