/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Agenda class keeps track of the Appointments
  using pointers, so that each Appointment object
  handles its own methods.
*/

#ifndef AGENDA_H
#define AGENDA_H

#include <memory>

#include "Appointment.h"

class Agenda {
 public:
  Agenda();

  // Returns the doctor's arrival time
  int getTimeA();
  // Returns the doctor's leaving time
  int getTimeL();

  // Sets the doctor's arrival time
  void setTimeL(int t);
  // Sets the doctor's leaving time
  void setTimeA(int t);

  // Assigns the doctor's name to this agenda
  void setDoctor(std::string id);
  // Retrieves the doctor's name
  std::string getDoctor();

 private:
  int timeOfArrival;
  int timeOfLeaving;
  std::string doctor;
};

#endif  // AGENDA_H
