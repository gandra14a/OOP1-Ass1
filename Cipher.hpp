#ifndef CIPHER_HPP
#define CIPHER_HPP
#define LOW_TO_UPPER 32

#include <string>
using std::string;


enum class CipherType { INVALID, NONE_CIPHER, ASCII_CIPHER, CAESAR_CIPHER };

typedef uint64_t Key;

class Cipher
{
  protected:
    Key key_;
  
  public:
    Cipher(Key key) : key_{key} {}
    Cipher(const Cipher &ciph) = delete;
    virtual ~Cipher() = default;

    Key getKey();
    virtual string getCipherTypeString() const = 0;
    string preparePlainText(const string &plain_text) const;
    virtual string encrypt(const string &plain_text) = 0;
    virtual string decrypt(const string &cipher_text) = 0;
    static CipherType getCipherType(const string &type);

};


#endif