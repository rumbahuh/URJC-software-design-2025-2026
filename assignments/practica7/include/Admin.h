/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Admin class represents a single person
  object that manages its methods.
*/

#ifndef ADMIN_H
#define ADMIN_H

#include <chrono>
#include <memory>
#include <vector>

#include "User.h"

class AppointmentSystem;

class Admin : public User {
 private:
 public:
  Admin(int id, std::string nombre, std::string mail, std::string pw);

  std::string getRole() const override;

  void assignAgenda(AppointmentSystem&);
  void createDoctor(AppointmentSystem&);
  void seeDoctorList(AppointmentSystem&);
  void seeAppointments();
  void showMenu(AppointmentSystem&);
};

#endif  // ADMIN_H
