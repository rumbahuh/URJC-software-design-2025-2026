/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Admin class represents a single person
  object that manages its methods.
*/

#include "Admin.h"

Admin::Admin(int id, std::string nombre, std::string mail,
             std::string pw) : User(id, nombre, mail, pw) {}

void Admin::assignSpecialty() {}

void Admin::manageAgendas() {}

void Admin::manageMedicalCensus() {}
