/**
 * \file Pacient.h
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Pacient class represents a single patient in the system.
 * It provides methods to interact with appointments, check available
 * time slots, modify personal data, and confirm attendance for scheduled
 * appointments.
 */

#ifndef PACIENT_H
#define PACIENT_H

#include <chrono>
#include <iostream>
#include <string>

#include "User.h"

class Appointment;

class Pacient : public User {
 public:
  /**
   * \brief Constructor for Pacient.
   * \param id Patient ID.
   * \param nombre Patient name.
   * \param mail Patient email.
   * \param pw Patient password.
   */
  Pacient(int id, std::string nombre, std::string mail, std::string pw);

  /**
   * \return User* Contructor copy to generate new object instance in dyn mem
   */
  std::unique_ptr<User> clone() const override {
    return std::make_unique<Pacient>(
        *this);  // Pacient constructor requires arguments
  }

  /**
   * \return std::string The role of the user (Pacient).
   */
  std::string getRole() const override;

  /**
   * \brief Checks available time slots from the appointment system database.
   */
  void checkTimeSlots();

  /**
   * \brief Modifies the patient's data.
   * \param name New name.
   * \param email New email.
   */
  void modifyData(std::string, std::string);

  /**
   * \brief Confirms attendance and updates the appointment state.
   * \param p The appointment object.
   */
  void confirmAssistance(const Appointment &p);

  /**
   * \brief Requests a new appointment.
   */
  void requestAppointment();

  /**
   * \brief Views the patient's own appointments.
   */
  void seeMyAppointments();

  /**
   * \brief Displays the patient menu.
   */
  void showMenu();
};

#endif  // PACIENT_H