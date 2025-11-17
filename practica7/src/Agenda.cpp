/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Agenda class keeps track of the Appointments
  using pointers, so that each Appointment object
  handles its own methods.
*/

#include "Agenda.h"

#include <memory>

Agenda::Agenda() : timeOfArrival(0), timeOfLeaving(0), doctor("") {}

int Agenda::getTimeA() { return timeOfArrival; }

int Agenda::getTimeL() { return timeOfLeaving; }

void Agenda::setTimeL(int t) { timeOfLeaving = t; }

void Agenda::setTimeA(int t) { timeOfArrival = t; }

void Agenda::setDoctor(std::string doctor) {}

std::string getDoctor() { return ""; }
