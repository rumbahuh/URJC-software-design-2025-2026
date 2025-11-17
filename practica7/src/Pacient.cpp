/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Pacient class represents a single patient in the system.
  It provides methods to interact with appointments, check available time slots,
  modify personal data, and confirm attendance for scheduled appointments.
*/

#include "Pacient.h"

#include "Appointment.h"

Pacient::Pacient(int id, std::string nombre, std::string mail,
               std::string pw) : User(id, nombre, mail, pw) {}

void Pacient::checkTimeSlots() {}

void Pacient::modifyData(std::string id, std::string password) {}

void Pacient::confirmAssistance(const Appointment &p) {}
