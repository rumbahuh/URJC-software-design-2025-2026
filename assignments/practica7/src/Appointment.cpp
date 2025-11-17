/*
Author: Rebeca Castilla
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

#include "Appointment.h"

#include <iostream>

Appointment::Appointment()
    : timeSlot(""),
      assistance(false),
      state(""),
      roomId(""),
      pacientId(""),
      doctorId("") {}

void Appointment::sendConfirmation() {}

void Appointment::sendReminder() {}

void Appointment::setDoctor(std::string id) {}

std::string Appointment::getDoctor() { return ""; }

void Appointment::setState(std::string st) {}

std::string Appointment::getState() { return ""; }

void Appointment::setTimeSlot(std::string t) {}

std::string Appointment::getTimeSlot() { return ""; }
