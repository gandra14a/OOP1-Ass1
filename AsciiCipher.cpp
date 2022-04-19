#include "AsciiCipher.hpp"

string AsciiCipher::getCipherTypeString() const
{
  string cipher_type_string = "ASCII";
  return cipher_type_string;
}

string AsciiCipher::encrypt(const string &plain_text)
{
  string prepared_plain_text = preparePlainText(plain_text);
  string encrypted_text;

  for (char c : prepared_plain_text)
  {
    encrypted_text = encrypted_text + to_string(c - key_ % 10) + " ";
  }
  encrypted_text.pop_back();
  return encrypted_text;
}

string AsciiCipher::decrypt(const string &cipher_text)
{
  string decrypted_text;
  unsigned long pos = 0;
  string number_str;
  char number_ch;

  while (pos < cipher_text.length())
  {
    number_str = cipher_text.substr(pos, 2);
    Utils::decimalStringToInt(number_str, number_ch);
    decrypted_text.push_back(number_ch + key_ % 10);
    pos = pos + 3;
  }
  return decrypted_text;
  
}