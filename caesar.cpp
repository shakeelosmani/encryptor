#include "caesar.h"

Caesar::Caesar(const char& key) : EncryptionAlgorithm("Caesar"), key(key)
{

}

void Caesar::setKey(const char& newKey)
{
    key = newKey;
}

char Caesar::getKey()
{
    return key;
}

void Caesar::encrypt(std::ifstream &in, std::ofstream &out)
{
    char chr;
    while(in.get(chr) && out)
    {
        out<<char(chr + key);
    }
}

void Caesar::decrypt(std::ifstream &in, std::ofstream &out)
{
    char chr;
    while(in.get(chr) && out)
    {
        out<<char(chr - key);
    }
}
