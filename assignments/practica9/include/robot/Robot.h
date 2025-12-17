/**
 * \file Robot.h
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Robot class represents a robotic assistant that interacts
 *        with Pacients and Rooms. It can retrieve Pacient information, access
 *        appointments, print tickets, and guide users.
 * \param id
 * \param estado
 * \param ultimaActividad
 * \param mtx
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <chrono>
#include <iostream>
#include <mutex>
#include <string>

#include "appointments/Ticket.h"

class Room;
class Pacient;
class Appointment;

class Robot {
 private:
  int id;
  std::string estado;
  std::chrono::steady_clock::time_point ultimaActividad;
  mutable std::mutex mtx;

 public:
  /**
   * \brief Constructor to initialize the Robot.
   * \param id The robot's ID.
   */
  Robot(int id);

  std::string roomId;
  std::string pacientId;
  std::string sensor;

  /**
   * \return int The robot's ID.
   */
  int getId() const;

  /**
   * \brief Simulates the robot accompanying a patient for a given time.
   * \param segundos Duration in seconds.
   */
  void dummy(int segundos);

  /**
   * \return std::string The robot's current state (thread-safe).
   */
  std::string getEstado() const;

  /**
   * \return std::chrono::steady_clock::time_point The time of the robot's last
   * activity.
   */
  std::chrono::steady_clock::time_point getUltimaActividad() const;

  /**
   * \brief Requests user credentials and returns IDs from the
   * AppointmentSystem. \return std::string The IDs or empty string if user is
   * not found.
   */
  std::string requestIds();

  /**
   * \brief Retrieves appointments for a given patient.
   * \param pacientId The patient's ID.
   */
  void checkAppointments(std::string pacientId);

  /**
   * \brief Prints a ticket for the given appointment.
   * \param p The appointment object.
   */
  void printTicket(const Appointment &p);

  /**
   * \brief Guides the patient to a specified room.
   */
  void acompanyToRoom();

  /**
   * \brief Updates the robot's position.
   */
  void updatePosition();

  /**
   * \brief Displays a message guiding a human to an info spot.
   */
  void sendHumanToInfoSpot();
};

#endif  // ROBOT_H
