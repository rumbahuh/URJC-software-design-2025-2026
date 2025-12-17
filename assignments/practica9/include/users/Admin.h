/**
 * \file Admin.h
 * \author Rebeca Castilla
 * \date 13-17/12/2025
 * \brief The Admin class with proper memory management
 */

#ifndef ADMIN_H
#define ADMIN_H

#include <map>
#include <memory>
#include <string>

#include "User.h"
#include "command/Command.h"  // MUST include full definition for unique_ptr

// Forward declarations
class AppointmentSystem;

// Note: Admin cannot be copied due to unique_ptr in commandMap
// If you need cloning, commandMap must be reconstructed, not copied

class Admin : public User {
 private:
  /**
   * \brief Maps menu option numbers to Command objects.
   *
   * This allows the Admin to act as an Invoker in the Command Pattern,
   * storing commands that can be executed based on the user's menu choice.
   */
  std::map<int, std::unique_ptr<Command>> commandMap;

  /**
   * \brief Initializes the command map with concrete Command instances.
   * \param sys Pointer to the AppointmentSystem (Receiver)
   *
   * This method sets up the commands so that each menu option corresponds
   * to a Command object, following the Command Pattern.
   */
  void setupCommands(AppointmentSystem* sys);

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
   * \brief Copy constructor - commandMap is left empty, will be set up on
   * showMenu()
   */
  Admin(const Admin& other);

  /**
   * \return User* Constructor copy to generate new object instance in dyn mem
   * Note: The cloned Admin will have an empty commandMap that needs to be set
   * up
   */
  std::unique_ptr<User> clone() const override {
    return std::make_unique<Admin>(*this);
  }

  /**
   * \return std::string The role of the user (Admin).
   */
  std::string getRole() const override;

  /**
   * \brief Shows the admin menu.
   * \param system Reference to AppointmentSystem.
   */
  void showMenu(AppointmentSystem& system);

  /**
   * \brief Creates a doctor in the appointment system.
   * \param system Reference to AppointmentSystem.
   */
  void createDoctor(AppointmentSystem& system);

  /**
   * \brief Assigns agendas in the appointment system.
   * \param system Reference to AppointmentSystem.
   */
  void assignAgenda(AppointmentSystem& system);

  /**
   * \brief Displays the list of doctors.
   * \param system Reference to AppointmentSystem.
   */
  void seeDoctorList(AppointmentSystem& system);

  /**
   * \brief Displays all appointments.
   */
  void seeAppointments();

  /**
   * \brief Destructor - must be defined in .cpp where Command is complete
   */
  ~Admin() override;
};

#endif  // ADMIN_H