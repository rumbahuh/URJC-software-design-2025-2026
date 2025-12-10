/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Pacient class represents a single patient in the system.
  It provides methods to interact with appointments, check available time slots,
  modify personal data, and confirm attendance for scheduled appointments.
*/

#ifndef PACIENT_H
#define PACIENT_H

#include <chrono>
#include <iostream>
#include <string>

#include "User.h"

class Appointment;

class Pacient : public User {
 private:
 public:
  Pacient(int id, std::string nombre, std::string mail, std::string pw);

  std::string getRole() const override;

  // Checks time slots available from appointment system data base
  void checkTimeSlots();
  // Modifies its own data (from user - still to implement inheritance)
  void modifyData(std::string, std::string);
  // Confirms assistance and changes state of Appointment
  void confirmAssistance(const Appointment &p);

  void requestAppointment();
  void seeMyAppointments();
  void showMenu();
};

#endif  // PACIENT_H
