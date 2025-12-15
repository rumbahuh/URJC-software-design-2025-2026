/**
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Doctor class represents a single person
 *        object with an assigned specialty and its methods.
 * \param room
 * \param specialty
 */

/**
 * \brief Represents a doctor user in the system.
 */
#ifndef DOCTOR_H
#define DOCTOR_H

#include <chrono>
#include <iostream>
#include <string>

#include "User.h"

class Room;
class Agenda;

class Doctor : public User {
 private:
  std::string room;

 public:
  /**
   * \brief Constructor for Doctor.
   * \param id Doctor ID.
   * \param nombre Doctor name.
   * \param mail Doctor email.
   * \param pw Doctor password.
   * \param specialty Doctor specialty (optional).
   */
  Doctor(int id, std::string nombre, std::string mail, std::string pw,
         std::string specialty = "");

  /**
   * \brief The doctor's specialty.
   */
  std::string specialty;

  /**
   * \return User* Contructor copy to generate new object instance in dyn mem
   */
  std::unique_ptr<User> clone() const override {
    return std::make_unique<Doctor>(
        *this);  // Doctor constructor requires arguments
  }

  /**
   * \brief Gets the assigned room ID.
   */
  void getRoom();

  /**
   * \return std::string The role of the user (Doctor).
   */
  std::string getRole() const override;

  /**
   * \brief Confirms patient assistance.
   */
  void confirmAssistance();

  /**
   * \brief Modifies the doctor's agenda.
   */
  void modifyAgenda();

  /**
   * \brief Adds notes to an appointment.
   */
  void addNotesToAppointment();

  /**
   * \brief Displays the doctor's menu.
   */
  void showMenu();
};

#endif  // DOCTOR_H