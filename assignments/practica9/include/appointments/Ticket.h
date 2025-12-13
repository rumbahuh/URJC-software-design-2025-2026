/**
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Ticket class represents a record for a scheduled appointment,
 *        including the time slot, the assigned Room, Doctor, and Pacient.
 * \param timeSlot
 * \param room
 * \param doctor
 * \param pacient
 */

#ifndef TICKET_H
#define TICKET_H

#include <iostream>

class Room;
class Doctor;
class Pacient;

class Ticket {
 private:
  std::string timeSlot;
  std::string room;
  std::string doctor;
  std::string pacient;

 public:
  Ticket(std::string time, std::string room, std::string doctor,
         std::string pacient);

/**
* \brief Displays ticket information.
*/
  void printTicket();
};

#endif  // TICKET_H
