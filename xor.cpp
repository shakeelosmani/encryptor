#include "xor.h"

XOR::XOR(const std::string& key) : EncryptionAlgorithm("XOR"), key(key)
{

}

void XOR::setKey(const std::string& newKey)
{
    key = newKey;
}

std::string XOR::getKey()
{
    return key;
}

void XOR::encrypt(std::ifstream& in, std::ofstream& out)
{
    std::string::const_iterator keyChr = key.begin();

    // Start the encryption
    char chr;
    while(in.get(chr) && out)
    {
        out<<char(chr ^ (*keyChr));
        if(++keyChr == key.end())
            keyChr = key.begin();
    }
}

void XOR::decrypt(std::ifstream &in, std::ofstream &out)
{
    encrypt(in, out);
}
