#ifndef CAESAR_CIPH_HPP
#define CAESAR_CIPH_HPP

#define BITS_IN_BYTE 8

#include "Cipher.hpp"

typedef char ByteShift;



class CaesarCipher : public Cipher
{
  public:
    CaesarCipher(Key key) : Cipher(key) {}
    CaesarCipher(const CaesarCipher &cc) = delete;
    virtual ~CaesarCipher() = default;

    string getCipherTypeString() const override;
    string encrypt(const string &plain_text) override;
    string decrypt(const string &cipher_text) override;

};

#endif