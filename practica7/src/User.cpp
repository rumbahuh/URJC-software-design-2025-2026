/*
Author: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The User class represents a generic system user with an ID, email, and
password. It provides a login method and serves as the base class (parent) for
Pacient, Doctor, and Admin classes.
*/

#include "User.h"
#include <vector>
#include <iostream>
#include <string>

User::User(int id,  std::string nombre, std::string mail, std::string pw)
    : id(id), nombre(nombre), mailAddress(mail), password(pw) {}

void User::getPerson(){
        struct Persona {
        int id;
        std::string nombre;
        int edad;
    };
  }
//std::string User::getId() { return id; }

//std::string User::getMail() { return mailAddress; }
