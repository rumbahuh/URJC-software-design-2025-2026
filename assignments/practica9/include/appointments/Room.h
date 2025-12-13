/**
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Room class represents a physical room in the system, identified by id.
 *        Each Room references the Doctor assigned to it, without owning the Doctor
 *        object.
 * \param id
 * \param doctorId
 */

#ifndef ROOM_H
#define ROOM_H

#include <iostream>

class Room {
private:
  std::string id;
  std::string doctorId;

 public:
  Room();

  /**
* \brief Sets the room ID.
* \param id The new room ID.
*/
  void setId(std::string id);
 /**
* \return std::string The room ID.
*/
  std::string getId();

 /**
* \brief Sets the doctor ID for the room.
* \param doctorId The doctor's ID.
*/
  void setDoctor(std::string doctorId);
  /**
* \return std::string The doctor ID assigned to the room.
*/
  std::string getDoctor();
};

#endif  // ROOM_H
