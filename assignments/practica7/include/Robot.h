/*
Author: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The RobotAssistant class represents a robotic assistant that interacts
  with Pacients and Rooms. It can retrieve Pacient information, access
  appointments, print tickets, and guide users, without owning the
  objects it references.
*/

#ifndef ROBOT_H
#define ROBOT_H

#include <chrono>  //para gestionar los tiempos.
#include <iostream>
#include <mutex>  //para gestionar acciones en paralelo
#include <string>

#include "Ticket.h"

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
  // Constructor para inicializar Robot
  Robot(int id);

  std::string roomId;
  std::string pacientId;
  std::string sensor;

  // Devuelve el int de id
  int getId() const;

  // Este método simula el acompañamiento del robot durante
  // "x" segundos, definidos en la variable "segundos"
  void dummy(int segundos);
  // Devuelve el estado del robot pero protege acceso a estado
  // con mutex para evitar incoherencias
  // en caso de que otro proceso quiera modificar el estado.
  std::string getEstado() const;
  // Este método retorna el tiempo de la última actividad del robot,
  // esto permite que si tengo varios robots libres, podamos
  // asignarle un paciente al que lleve más tiempo inactivo.
  std::chrono::steady_clock::time_point getUltimaActividad() const;
  // ----------------------------------

  /* Requests user credentials and returns IDs from the AppointmentSystem
  Returns empty string if user is not found */
  std::string requestIds();

  // Retrieves Pacient appointments
  void checkAppointments(std::string pacientId);

  // Prints a ticket for the given appointment
  void printTicket(const Appointment &p);

  // Guides the patient to a specified room
  void acompanyToRoom();

  // Updates the position of the robot
  void updatePosition();

  // Displays a message guiding a human to an info spot
  void sendHumanToInfoSpot();
};

#endif  // ROBOT_H
