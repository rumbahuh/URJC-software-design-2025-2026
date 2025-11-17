/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Room class represents a physical room in the system, identified by id.
  Each Room references the Doctor assigned to it, without owning the Doctor
object.
*/

#include "Room.h"

Room::Room() : id(""), doctorId("") {
  id = "";
  doctorId = "";
}

void Room::setId(std::string id) {}

std::string Room::getId() { return ""; }

void Room::setDoctor(std::string doctorId) {}

std::string Room::getDoctor() { return ""; }
