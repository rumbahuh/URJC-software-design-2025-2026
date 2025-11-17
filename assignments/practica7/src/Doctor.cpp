/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Doctor class represents a single person
  object with an assigned specialty and its methods.
*/

#include "Doctor.h"

#include "Agenda.h"
#include "Room.h"

Doctor::Doctor(int id, std::string nombre, std::string mail,
               std::string pw, std::string specialty)
    : User(id, nombre, mail, pw), specialty(specialty), room("") {}

void Doctor::editAgenda() {}

void Doctor::markAssistance(bool assitance) {}

void Doctor::checkAgenda() {}
