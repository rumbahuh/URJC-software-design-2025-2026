/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Admin class represents a single person
  object that manages its methods.
*/

#ifndef ADMIN_H
#define ADMIN_H
#include "User.h"

class Admin : public User{
 private:

 public:
  Admin(int id, std::string nombre, std::string mail, std::string pw);

  // Assigns specialty to Doctor
  void assignSpecialty();
  // Direct access to agendas pointer on Appointment system
  void manageAgendas();
  // Manage doctors
  void manageMedicalCensus();

};

#endif  // ADMIN_H
