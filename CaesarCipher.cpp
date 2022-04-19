#include "CaesarCipher.hpp"

string CaesarCipher::getCipherTypeString() const
{
  string cipher_type_string = "CAESAR";
  return cipher_type_string;
}

string CaesarCipher::encrypt(const string &plain_text)
{
  string prepared_plain_text = preparePlainText(plain_text);
  string encrypted_text;
  char encrypted_letter;

  ByteShift bs = 7; // 7 because we take left-most byte first
  int current_key_byte;
  int caesar_shift;

  for (char c : prepared_plain_text)
  {
    current_key_byte = (key_ >> bs * BITS_IN_BYTE) & 0xFF;
    caesar_shift = current_key_byte % 26;

    if (c + caesar_shift > 'Z')
    {
      encrypted_letter = ('A' - 1) + ((c + caesar_shift) - 'Z'); 
    }
    else
    {
      encrypted_letter = c + caesar_shift;
    }
    encrypted_text.push_back(encrypted_letter);

    bs--;
    if (bs < 0)
    {
      bs = 7;
    }
  }
  return encrypted_text;
}

string CaesarCipher::decrypt(const string &cipher_text)
{
  string decrypted_text;
  char decrypted_letter;

  ByteShift bs = 7; // 7 because we take left-most byte first
  int current_key_byte;
  int caesar_shift;

  for (char c : cipher_text)
  {
    current_key_byte = (key_ >> bs * BITS_IN_BYTE) & 0xFF;
    caesar_shift = current_key_byte % 26;

    if (c - caesar_shift < 'A')
    {
      decrypted_letter = ('Z' + 1) - ('A' - (c - caesar_shift)); 
    }
    else
    {
      decrypted_letter = c - caesar_shift;
    }
    decrypted_text.push_back(decrypted_letter);

    bs--;
    if (bs < 0)
    {
      bs = 7;
    }
  }
  return decrypted_text;
}