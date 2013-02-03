#include "vigenere.h"

Vigenere::Vigenere(const std::string& key) : EncryptionAlgorithm("Vigenere"), key(key)
{

}

void Vigenere::setKey(const std::string& newKey)
{
    key = newKey;
}

std::string Vigenere::getKey()
{
    return key;
}

void Vigenere::encrypt(std::ifstream &in, std::ofstream &out)
{
    std::string::const_iterator keyChr = key.begin();

    // Start the encryption
    char chr;
    while(in.get(chr) && out)
    {
        out<<char(chr + (*keyChr));
        if(++keyChr == key.end())
            keyChr = key.begin();
    }
}

void Vigenere::decrypt(std::ifstream &in, std::ofstream &out)
{
    std::string::const_iterator keyChr = key.begin();

    // Start the encryption
    char chr;
    while(in.get(chr) && out)
    {
        out<<char(chr - *keyChr);
        if(++keyChr == key.end())
            keyChr = key.begin();
    }
}
