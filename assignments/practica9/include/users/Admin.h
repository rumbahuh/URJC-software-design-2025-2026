/**
 * \author Rebeca Castilla
 * \date 13/11/2025
 * \brief The Admin class represents a single person
 *        object that manages its methods.
 */

#ifndef ADMIN_H
#define ADMIN_H

#include <chrono>
#include <memory>
#include <vector>

#include "User.h"

class AppointmentSystem;

class Admin : public User {
 public:
  /**
   * \brief Constructor for Admin.
   * \param id Admin ID.
   * \param nombre Admin name.
   * \param mail Admin email.
   * \param pw Admin password.
   */
  Admin(int id, std::string nombre, std::string mail, std::string pw);

  /**
   * \return User* Contructor copy to generate new object instance in dyn mem
   */
  std::unique_ptr<User> clone() const override {
    return std::make_unique<Admin>(*this); // Admin constructor requires arguments
  }

  /**
   * \return std::string The role of the user (Admin).
   */
  std::string getRole() const override;

  /**
   * \brief Assigns agendas in the appointment system.
   * \param system Reference to AppointmentSystem.
   */
  void assignAgenda(AppointmentSystem&);

  /**
   * \brief Creates a doctor in the appointment system.
   * \param system Reference to AppointmentSystem.
   */
  void createDoctor(AppointmentSystem&);

  /**
   * \brief Displays the list of doctors.
   * \param system Reference to AppointmentSystem.
   */
  void seeDoctorList(AppointmentSystem&);

  /**
   * \brief Displays all appointments.
   */
  void seeAppointments();

  /**
   * \brief Shows the admin menu.
   * \param system Reference to AppointmentSystem.
   */
  void showMenu(AppointmentSystem&);
};

#endif  // ADMIN_H
