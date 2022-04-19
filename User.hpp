#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <map>
#include <fstream>
#include "NoneCipher.hpp"
#include "AsciiCipher.hpp"
#include "CaesarCipher.hpp"
#include "Utils.hpp"

using std::string;
using std::map;
using std::pair;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::getline;


class User
{
  private:
    string name_;
    string password_;
    map<User*, Cipher*, bool(*)(User*, User*)> contacts_;


  public:
    User(const string &name, const string &password)
      : name_{name}, password_{password}, contacts_{Utils::sortContactsAlphabetically} {}
    User(const User &other_user) = delete;
    ~User();

    string getName() const;
    string getPassword() const;
    const auto& getContacts() const
    {
      return contacts_;
    }
    bool verifyPassword(const string &password) const;
    bool hasContact(const string &name) const;
    void addContact(User* contact, CipherType type, Key key);
    bool sendMessage(const string &recipient, const string &filename,
                    const string &plain_text) const;
    bool readMessage(const string &filename) const;

};

#endif