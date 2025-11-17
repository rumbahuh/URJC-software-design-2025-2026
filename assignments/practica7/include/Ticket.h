/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Ticket class represents a record for a scheduled appointment,
  including the time slot, the assigned Room, Doctor, and Pacient.
*/

#ifndef TICKET_H
#define TICKET_H

#include <iostream>

class Room;
class Doctor;
class Pacient;

class Ticket {
 public:
  Ticket(std::string time, std::string room, std::string doctor,
         std::string pacient);

  // Displays ticket information directly as a whole
  void printTicket();

 private:
  std::string timeSlot;
  std::string room;
  std::string doctor;
  std::string pacient;
};

#endif  // TICKET_H
