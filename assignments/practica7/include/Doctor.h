/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Doctor class represents a single person
  object with an assigned specialty and its methods.
*/

#ifndef DOCTOR_H
#define DOCTOR_H

#include <chrono>
#include <iostream>
#include <string>

#include "User.h"

class Room;
class Agenda;

class Doctor : public User {  // Inherits from User
 private:
  std::string room;

 public:
  Doctor(int id, std::string nombre, std::string mail, std::string pw,
         std::string specialty = "");  // Usar &?

  // Admin will assign it externally
  std::string specialty;

  // Returns the assigned room id
  void getRoom();

  std::string getRole() const override;

  void confirmAssistance();
  void modifyAgenda();
  void addNotesToAppointment();

  void showMenu();
};

#endif  // DOCTOR_H
