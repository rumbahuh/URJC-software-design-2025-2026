/**
 * \file CreateDoctorCommand.h
 * \author Rebeca Castilla
 * \date 13/12/2025
 * \brief Concrete Command to create a new doctor.
 */

#ifndef CREATE_DOCTOR_COMMAND_H
#define CREATE_DOCTOR_COMMAND_H

#include "Command.h"
#include "system/AppointmentSystem.h"

class CreateDoctorCommand : public Command {
public:
    /**
     * \brief Constructor
     * \param sys Pointer to the AppointmentSystem (Receiver)
     */
    explicit CreateDoctorCommand(AppointmentSystem* sys)
        : Command(sys) {}

    /**
     * \brief Executes the command
     */
    void execute() override {
        system->insertUser();  // o createDoctor() si lo implementas
    }
};

#endif // CREATE_DOCTOR_COMMAND_H
