/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The User class represents a generic system user with an ID, email, and
password. It serves as the base class (parent) for Pacient, Doctor, and Admin
classes.
*/

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
 protected:
  int id;
  std::string nombre;
  std::string mailAddress;

 private:
  std::string password;

 public:
  User(int id, std::string nombre, std::string mail, std::string pw);
  virtual ~User() = default; // virtual para herencia segura
  void getPerson();

  // Returns id string
  //std::string getId();
  // Return mail string
  //std::string getMail();
};

#endif  // USER_H
