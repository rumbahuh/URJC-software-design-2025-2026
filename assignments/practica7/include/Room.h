/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Room class represents a physical room in the system, identified by id.
  It storages strings for it to check with Appointment system, not own other
class objects.
*/

#ifndef ROOM_H
#define ROOM_H

#include <iostream>

class Room {
 public:
  Room();

  // Sets room id
  void setId(std::string id);
  // Returns id
  std::string getId();

  // Sets doctor id to room
  void setDoctor(std::string doctorId);
  // Returns doctor id of room
  std::string getDoctor();

 private:
  std::string id;
  std::string doctorId;
};

#endif  // ROOM_H
