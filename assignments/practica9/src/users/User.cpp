/**
 * \file User.cpp
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The User class represents a generic system user with an ID, name,
 * email, and password. It serves as the base class (parent) for Pacient,
 * Doctor, and Admin classes. \param id \param nombre \param mailAddress \param
 * password.
 */

#include "users/User.h"

#include <iostream>
#include <string>

User::User(int id, std::string nombre, std::string mail, std::string pw)
    : id(id), nombre(nombre), mailAddress(mail), password(pw) {}

int User::getId() const { return id; }
std::string User::getUsername() const { return nombre; }
std::string User::getMail() const { return mailAddress; }
std::string User::getPassword() const { return password; }

void User::setId(int newId) { id = newId; }
void User::setUsername(const std::string &newName) { nombre = newName; }
void User::setMail(const std::string &newMail) { mailAddress = newMail; }
void User::setPassword(const std::string &newPw) { password = newPw; }
