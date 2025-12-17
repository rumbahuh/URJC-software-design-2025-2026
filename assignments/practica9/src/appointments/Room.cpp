/**
 * \file Room.cpp
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Room class represents a physical room in the system, identified by
 * id. Each Room references the Doctor assigned to it, without owning the Doctor
 *        object.
 * \param id
 * \param doctorId
 */

#include "appointments/Room.h"

Room::Room() : id(""), doctorId("") {
  id = "";
  doctorId = "";
}

void Room::setId(std::string id) {}

std::string Room::getId() { return ""; }

void Room::setDoctor(std::string doctorId) {}

std::string Room::getDoctor() { return ""; }
