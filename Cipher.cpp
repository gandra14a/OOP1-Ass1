#include "Cipher.hpp"


Key Cipher::getKey() {return key_;}

string Cipher::preparePlainText(const string &plain_text) const
{
  string prepared_plain_text;
  char new_sym;
  for (char sym : plain_text)
  {
    if (sym >= 'a' && sym <= 'z')
    {
      new_sym = sym - LOW_TO_UPPER;
      prepared_plain_text.push_back(new_sym);
    }
    else if (sym == ' ')
    {
    }
    else
    {
      prepared_plain_text.push_back(sym);
    }
  }
  return prepared_plain_text;
}

CipherType Cipher::getCipherType(const string &type)
{
  CipherType cipher_type;
  if (!type.compare("NONE"))
  {
    cipher_type = CipherType::NONE_CIPHER;
  }
  else if (!type.compare("ASCII"))
  {
    cipher_type = CipherType::ASCII_CIPHER;
  }
  else if (!type.compare("CAESAR"))
  {
    cipher_type = CipherType::CAESAR_CIPHER;
  }
  else 
  {
    cipher_type = CipherType::INVALID;
  }
  return cipher_type;
}
