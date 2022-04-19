#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "User.hpp"
using std::fstream;
using std::string;
using std::vector;
using std::hex;
using std::setfill;
using std::setw;


class Config
{
  private:
    fstream file_;
    string filename_;
    bool modified_;
    vector<User*> users_;

  public:
    Config(const string &filename);
    Config(const Config &config) = delete;
    ~Config();

    void setConfigModified();
    bool isOpen();
    bool parseFile();
    bool containsUser(const string &name) const;
    User* getUser(const string &name) const;
    User* registerUser(const string &name, const string &password);
    User* loginUser(const string &name, const string &password) const;
    bool updateConfigFile();



};



#endif
