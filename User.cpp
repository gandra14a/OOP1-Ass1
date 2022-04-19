#include "User.hpp"
#include "IO.hpp"
#define REC_NAME_OFFSET 11
#define SEN_NAME_OFFSET 8



User::~User()
{
  for (pair<User*, Cipher*>  contact : contacts_)
  {
    delete contact.second;
  }
}

string User::getName() const
{
  return name_;
}

string User::getPassword() const
{
  return password_;
}

bool User::verifyPassword(const string &password) const
{
  bool correct_password = false;
  if (password_.compare(password) == 0)
  {
    correct_password = true;
  }
  return correct_password;
}

bool User::hasContact(const string &name) const
{
  bool is_in_contacts = false;
  for (pair<User*, Cipher*>  contact : contacts_)
  {
    if (name.compare(contact.first -> name_) == 0)
    {
      is_in_contacts = true;
      break;
    }
  }
  return is_in_contacts;
}

void User::addContact(User* contact, CipherType type, Key key)
{
  if (type == Cipher::getCipherType("NONE"))
  {
    contacts_.insert({contact, new NoneCipher(key)});
  }

  if (type == Cipher::getCipherType("ASCII"))
  {
    contacts_.insert({contact, new AsciiCipher(key)});
  }

  if (type == Cipher::getCipherType("CAESAR"))
  {
    contacts_.insert({contact, new CaesarCipher(key)});
  }

}

bool User::sendMessage(const string &recipient, const string &filename,
                const string &plain_text) const
{
  ofstream text_file(filename);
  if (!text_file.is_open())
  {
    return false;
  }
  if (!hasContact(recipient))
  {
    return false;
  }
  Cipher* recipient_cipher;
  for (pair<User*, Cipher*> contact : contacts_)
  {
    if (recipient.compare(contact.first -> name_) == 0)
    {
      recipient_cipher = contact.second;
      break;
    }
  }
  string prepared_plain_text = recipient_cipher -> preparePlainText(plain_text);
  string encrypted_text = recipient_cipher -> encrypt(prepared_plain_text);
  string message = "Recipient: " + recipient + "\n" + "Sender: " + name_ + "\n" + encrypted_text + "\n";
  text_file << message;
  text_file.close();
  IO::printEncryptedMessage(message);

  return true;
}

bool User::readMessage(const string &filename) const
{
  ifstream text_file(filename);
  if (!text_file.is_open())
  {
    return false;
  }
  string recipient_name;
  string sender_name;
  string encrypted_text;

  string first_line;
  string second_line;

  getline(text_file, first_line);
  getline(text_file, second_line);
  getline(text_file, encrypted_text);

  text_file.close();

  recipient_name = first_line.substr(REC_NAME_OFFSET, first_line.length() - REC_NAME_OFFSET);
  sender_name = second_line.substr(SEN_NAME_OFFSET, second_line.length() - SEN_NAME_OFFSET);

  if ((recipient_name.compare(name_) != 0) || (!hasContact(sender_name)))
  {
    return false;
  }

  Cipher* sender_cipher;
  for (pair<User*, Cipher*> contact : contacts_)
  {
    if (sender_name.compare(contact.first -> name_) == 0)
    {
      sender_cipher = contact.second;
      break;
    }
  }
  string decrypted_text = sender_cipher -> decrypt(encrypted_text);

  IO::printDecryptedMessage(recipient_name, sender_name, decrypted_text);

  return true;


}