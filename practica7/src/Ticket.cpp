/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Ticket class represents a record for a scheduled appointment,
  including the time slot, the assigned Room, Doctor, and Pacient.
*/

#include "Ticket.h"

Ticket::Ticket(std::string time, std::string room, std::string doctor,
               std::string pacient)
    : timeSlot(time), room(room), doctor(doctor), pacient(pacient) {}

void Ticket::printTicket() {}
