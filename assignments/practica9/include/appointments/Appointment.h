/**
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Appointment class represents a single scheduled meeting between
 *        Doctor, Pacient, a specific room and a time slot. It stores pointers 
 *        to the atributes with no problem of deletion, since the objects are 
 *        owned elsewhere. Appointment handles its own methods. The usage 
 *        depends on the fact that this class only sends messages if the 
 *        appointment was sucessfully created and storaged in AppointmentSystem 
 *        database.
 * \param roomId
 * \param pacientId
 * \param doctorId
 * \param timeSlot A time string hh:mm
 * \param assistance 
 * \param state
 */

#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>

class Pacient;
class Doctor;
class Room;

class Appointment {
 private:
  std::string roomId;
  std::string pacientId;
  std::string doctorId;

 public:
  Appointment();

  std::string timeSlot;
  bool assistance;
  std::string state;

/**
* \brief Prints a confirmation message when the appointment is created.
*/
  void sendConfirmation();
/**
* \brief Prints a reminder message before the appointment.
*/
  void sendReminder();

/**
* \brief Sets the ID of the doctor assigned to this appointment.
* \param id The doctor's ID.
*/
  void setDoctor(std::string id);
/**
* \return std::string The ID of the assigned doctor.
*/
  std::string getDoctor();

/**
* \brief Sets the current state of the appointment.
* \param st The new state.
*/
  void setState(std::string st);


/**
* \return Returns the current state of the appointment.
*/
  std::string getState();
/**
* \brief Sets the time slot for the appointment.
* \param t The new time slot.
*/
  void setTimeSlot(std::string t);


/**
* \return Returns the scheduled time slot.
*/
  std::string getTimeSlot();
};

#endif  // APPOINTMENT_H
