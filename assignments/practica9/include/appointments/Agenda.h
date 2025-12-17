/**
 * \file Agenda.h
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Agenda class keeps track of the Appointments
 *        using pointers, so that each Appointment object
 *        handles its own methods.
 * \param timeOfArrival
 * \param timeOfLeaving
 * \param doctor The doctor id as std::string
 */

#ifndef AGENDA_H
#define AGENDA_H

#include <memory>

#include "Appointment.h"

class Agenda {
 private:
  int timeOfArrival;
  int timeOfLeaving;
  std::string doctor;

 public:
  Agenda();

  /**
   * \return int Doctor's arrival time
   */
  int getTimeA();

  /**
   * \return int Doctor's leaving time
   */
  int getTimeL();

  /**
   * \brief Sets the doctor's leaving time.
   * \param t The new leaving time.
   */
  void setTimeL(int t);

  /**
   * \brief Sets the doctor's arrival time.
   * \param t The new arrival time.
   */
  void setTimeA(int t);

  /**
   * \brief Assigns the doctor's name to this agenda.
   * \param id The doctor's name or identifier.
   */
  void setDoctor(std::string id);

  /**
   * \return std::string The doctor's name.
   */
  std::string getDoctor();
};

#endif  // AGENDA_H
