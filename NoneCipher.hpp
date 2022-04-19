#ifndef NON_CIPH_HPP
#define NON_CIPH_HPP

#include "Cipher.hpp"

class NoneCipher : public Cipher
{
  public:
    NoneCipher(Key key) : Cipher(key) {}
    NoneCipher(const NoneCipher &nc) = delete;
    virtual ~NoneCipher() = default;

    string getCipherTypeString() const override;
    string encrypt(const string &plain_text) override;
    string decrypt(const string &cipher_text) override;



};

#endif