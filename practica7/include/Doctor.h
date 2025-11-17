/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Doctor class represents a single person
  object with an assigned specialty and its methods.
*/

#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>
#include "User.h"

class Room;
class Agenda;

class Doctor : public User{ // Inherits from User
 public:
  Doctor(int id, std::string nombre, std::string mail,
           std::string pw, std::string specialty = ""); // Usar &?

  // Admin will assign it externally
  std::string specialty;

  // Allows the doctor to edit their agenda in the appointment system
  void editAgenda();

  // Marks patient attendance (assistance) in the appointment system
  void markAssistance(bool a);

  // Checks or reviews the doctor's agenda
  void checkAgenda();

  // Returns the assigned room id
  void getRoom();

 private:
  std::string room;
};

#endif  // DOCTOR_H
