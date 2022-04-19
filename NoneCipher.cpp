#include "NoneCipher.hpp"

string NoneCipher::getCipherTypeString() const
{
  string cipher_type_string = "NONE";
  return cipher_type_string;
}

string NoneCipher::encrypt(const string &plain_text)
{
  string encrypted_text = preparePlainText(plain_text); // not actually encrypted in this case
  return encrypted_text;
}

string NoneCipher::decrypt(const string &cipher_text)
{
  string decrypted_text = cipher_text; // not actually decrypted
  return decrypted_text;
}