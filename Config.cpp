#include "Config.hpp"

Config::Config(const string &filename)
{
  file_.open(filename);
  if (isOpen())
  {
    filename_ = filename;
    modified_ = false;
  }

}

Config::~Config()
{
  for (User* user : users_)
  {
    delete user;
  }

}

void Config::setConfigModified()
{
  modified_ = true;
}

bool Config::isOpen()
{
  return file_.is_open();
}

bool Config::parseFile()
{
  bool valid_file = true;

  // check if file empty
  if (file_.peek() == EOF)
  {
    file_.close();
    return valid_file;
  }

  string new_user_info;
  string new_user_name;
  string new_user_password;
  vector<string> all_users_contacts;
  int index;

  while (!file_.eof() )
  {
    getline(file_, new_user_info);
    if (!new_user_info.empty())
    {
      index = new_user_info.find_first_of(";");
      new_user_name = new_user_info.substr(0, index);
      if (containsUser(new_user_name)) // two users with the same name are not allowed
      {
        valid_file = false;
        file_.close();
        return valid_file;
      }
      new_user_info.erase(0, index + 1);
      index = new_user_info.find_first_of(";");
      new_user_password = new_user_info.substr(0, index);
      new_user_info.erase(0, index + 1);

      users_.push_back(new User(new_user_name, new_user_password));
      all_users_contacts.push_back(new_user_info); // because info contains only current user contacts
    }
  }

  int number_of_users = int(users_.size());

  string current_user_contacts;
  string contact_name;
  string cipher_type;
  string cipher_key_str;
  Key cipher_key_num;
  
  for (int usr = 0; usr < number_of_users; usr++)
  {
    current_user_contacts = all_users_contacts[usr];

    while (current_user_contacts.length() > 2) // because of \n which counts for 2 characters
    {
      index = current_user_contacts.find_first_of(":");
      contact_name = current_user_contacts.substr(0, index);
      if (contact_name.compare(users_[usr] -> getName()) == 0 ||
                                  !containsUser(contact_name) ||
                      users_[usr] -> hasContact(contact_name) )
      {
        valid_file = false;
        file_.close();
        return valid_file;
      }

      current_user_contacts.erase(0, index + 1);
      index = current_user_contacts.find_first_of(",");
      cipher_type = current_user_contacts.substr(0, index);
      current_user_contacts.erase(0, index + 1);
      index = current_user_contacts.find_first_of(";");
      cipher_key_str = current_user_contacts.substr(0, index);
      Utils::convertHexTo64BitNumber(cipher_key_str, cipher_key_num);
      current_user_contacts.erase(0, index + 1);

      users_[usr] -> addContact(getUser(contact_name), Cipher::getCipherType(cipher_type), cipher_key_num);
    }
  }

  map<User*, Cipher*, bool(*)(User*, User*)> curr_usr_contacts;

  for (User* usr : users_)
  {
    curr_usr_contacts = usr -> getContacts();
    for (pair<User*, Cipher*> contact : curr_usr_contacts)
    {
      if (!(contact.first -> hasContact(usr -> getName())))
      {
        valid_file = false;
        file_.close();
        return valid_file;
      }
    }
  }
  file_.close();
  return valid_file;
}



bool Config::containsUser(const string &name) const
{
  for (User* user : users_)
  {
    if (name.compare(user -> getName()) == 0)
    {
      return true;
    }
  }
  return false;
}

User* Config::getUser(const string &name) const
{
  for (User* user : users_)
  {
    if (name.compare(user -> getName()) == 0)
    {
      return user;
    }
  }
  return nullptr;
}

User* Config::registerUser(const string &name, const string &password)
{
  User* new_user = new User(name, password);
  users_.push_back(new_user);
  setConfigModified();
  return new_user;
}


User* Config::loginUser(const string &name, const string &password) const
{
  User* current_user = getUser(name);
  if (current_user -> verifyPassword(password))
  {
    return current_user;
  }
  else
  {
    return nullptr;
  }
}

bool Config::updateConfigFile()
{
  file_.open(filename_);
  if (!isOpen())
  {
    return false;
  }

  if (modified_ == true)
  {
    map<User*, Cipher*, bool(*)(User*, User*)> curr_usr_contacts;
    for (User* usr : users_)
    {
      curr_usr_contacts = usr -> getContacts();
      file_ << usr -> getName() << ";" << usr -> getPassword() << ";";
      for (pair<User*, Cipher*> contact : curr_usr_contacts)
      {
        file_ << contact.first -> getName() << ":" << contact.second -> getCipherTypeString() << ",";
        file_ << setfill('0') << setw(16) << hex << contact.second -> getKey() << ";";
      }
      file_ << endl;
    }
  }
  modified_ = false;
  file_.close();
  return true;
}