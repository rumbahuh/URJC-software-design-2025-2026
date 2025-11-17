/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Appointment class represents a single scheduled meeting between
  Doctor, Pacient, a specific room and a time slot.
  It stores pointers to the atributes with no problem of deletion,
  since the objects are owned elsewhere.
  Appointment handles its own methods.

  The usage depends on the fact that this class only sends messages
  if the appointment was sucessfully created and storaged in
  AppointmentSystem database.
*/

#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>

class Pacient;
class Doctor;
class Room;

class Appointment {
 public:
  Appointment();

  std::string timeSlot;
  bool assistance;
  std::string state;

  // Prints a confirmation message when the appointment is created
  void sendConfirmation();
  // Prints a reminder message before the appointment
  void sendReminder();

  // Sets the id of the doctor assigned to this appointment
  void setDoctor(std::string id);
  // Returns the id of the assigned doctor
  std::string getDoctor();

  // Sets the current state of the appointment
  void setState(std::string st);
  // Returns the current state of the appointment
  std::string getState();

  // Sets the time slot for the appointment
  void setTimeSlot(std::string t);
  // Returns the scheduled time slot
  std::string getTimeSlot();

 private:
  std::string roomId;
  std::string pacientId;
  std::string doctorId;
};

#endif  // APPOINTMENT_H
