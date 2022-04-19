#ifndef ASCII_CIPH_HPP
#define ASCII_CIPH_HPP

#include "Cipher.hpp"
#include "Utils.hpp"
using std::to_string;


class AsciiCipher : public Cipher
{

  public:
    AsciiCipher(Key key) : Cipher(key) {}
    AsciiCipher(const AsciiCipher &ac) = delete;
    virtual ~AsciiCipher() = default;

    string getCipherTypeString() const override;
    string encrypt(const string &plain_text) override;
    string decrypt(const string &cipher_text) override;




};

#endif