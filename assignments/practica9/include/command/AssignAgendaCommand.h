/**
 * \file AssignAgendaCommand.h
 * \author Rebeca Castilla
 * \date 13/12/2025
 * \brief Concrete Command to assign a doctor's agenda.
 */

#ifndef ASSIGN_AGENDA_COMMAND_H
#define ASSIGN_AGENDA_COMMAND_H

#include "Command.h"
#include "system/AppointmentSystem.h"

class AssignAgendaCommand : public Command {
 public:
  /**
   * \brief Constructor
   * \param sys Pointer to the AppointmentSystem (Receiver)
   */
  explicit AssignAgendaCommand(AppointmentSystem* sys) : Command(sys) {}

  /**
   * \brief Executes the command
   */
  void execute() override {
    system->assignDoctor();  // o assignAgenda()
  }
};

#endif  // ASSIGN_AGENDA_COMMAND_H
