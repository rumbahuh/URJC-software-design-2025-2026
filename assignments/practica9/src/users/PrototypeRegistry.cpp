/**
 * \file PrototypeRegistry.cpp
 * \author Rebeca Castilla
 * \date 13/12/2025
 * \brief Prototype registry implementation using unique_ptr.
 */

#include "users/PrototypeRegistry.h"

std::unique_ptr<User> PrototypeRegistry::userTypes[N] = {
    nullptr,  // 0 = not used
    std::make_unique<Admin>(0, "admin", "admin@mail.com", "pw"),
    std::make_unique<Doctor>(0, "doctor", "doc@mail.com", "pw", ""),
    std::make_unique<Pacient>(0, "pacient", "pac@mail.com", "pw")};

std::unique_ptr<User> PrototypeRegistry::makeUser(int choice) {
  if (choice <= 0 || choice >= N || !userTypes[choice]) {
    return nullptr;  // invalid choice
  }
  return userTypes[choice]->clone();
}
