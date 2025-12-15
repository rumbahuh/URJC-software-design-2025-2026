/**
 * \file ViewDoctorsCommand.h
 * \author Rebeca Castilla
 * \date 13/12/2025
 * \brief Concrete Command to view all doctors.
 */

#ifndef VIEW_DOCTORS_COMMAND_H
#define VIEW_DOCTORS_COMMAND_H

#include "Command.h"
#include "system/AppointmentSystem.h"

class ViewDoctorsCommand : public Command {
 public:
  /**
   * \brief Constructor
   * \param sys Pointer to the AppointmentSystem (Receiver)
   */
  explicit ViewDoctorsCommand(AppointmentSystem* sys) : Command(sys) {}

  /**
   * \brief Executes the command
   */
  void execute() override {
    system->getDoctors();  // o displayAllDoctors()
  }
};

#endif  // VIEW_DOCTORS_COMMAND_H
