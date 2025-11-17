/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The AppointmentSystem class manages all system objects, including Pacients,
  Doctors, Admins, RobotAssistants, Tickets, Rooms, Agendas and Appointments.
  It provides methods to create and cancel appointments, assign doctors,
  generate tickets, and send notifications.

  This class owns all objects in the system through unique_ptr.
*/

#ifndef APPOINTMENT_SYSTEM_H
#define APPOINTMENT_SYSTEM_H

#include <sqlite3.h>
#include <vector>
#include <iostream>
#include <memory>
#include <set>

#include "Admin.h"
#include "Agenda.h"
#include "Appointment.h"
#include "Doctor.h"
#include "Notification.h"
#include "Pacient.h"
#include "Robot.h"
#include "Room.h"
#include "Ticket.h"
#include "User.h"

// Comparador que sortea los robots por actividad
struct RobotCompare {
  bool operator()(const std::unique_ptr<Robot> &a,
                  const std::unique_ptr<Robot> &b) const {
    return a->getUltimaActividad() < b->getUltimaActividad();
  }
};

class AppointmentSystem {
 protected:
  sqlite3* db;

 private:
  static const int MAX_PACIENTS = 100;
  static const int MAX_DOCTORS = 20;
  static const int MAX_ADMINS = 5;
  static const int MAX_TICKETS = 200;
  static const int MAX_ROOMS = 50;
  static const int MAX_APPOINTMENTS = 200;
  static const int MAX_TIME_SLOTS = 14;
  static const int MAX_NOTIFICATIONS = 400;

  // Nuevo almacenamiento de STL ordenada automáticamente por el tiempo
  std::set<std::unique_ptr<Robot>, RobotCompare> robots;
  // --------------------------
  // Database of pointers
  std::unique_ptr<std::unique_ptr<Pacient>[]> pacients;
  std::unique_ptr<std::unique_ptr<Doctor>[]> doctors;
  std::unique_ptr<std::unique_ptr<Agenda>[]> agendas;
  std::unique_ptr<std::unique_ptr<Admin>[]> admins;
  std::unique_ptr<std::unique_ptr<Ticket>[]> tickets;
  std::unique_ptr<std::unique_ptr<Room>[]> rooms;
  std::unique_ptr<std::unique_ptr<Appointment>[]> appointments;
  std::unique_ptr<std::string[]> timesSlots;
  std::unique_ptr<std::string[]> notifications;

 public:
  AppointmentSystem();
  ~AppointmentSystem();

  void addRobot(std::unique_ptr<Robot>);

  /*Prints the states of the robots storaged in 
  the vector as well as the real time since last activity*/
  void getAllRobotStatesTime();

  // Devuelve referencias de lectura sobre los robots almacenados
  const std::set<std::unique_ptr<Robot>, RobotCompare> &getRobots() const;

  // Devuelve el robot libre más inactivo (null si no hay ninguno)
  Robot *getNextAvailableRobot();
  // --------------------------
  
  // Generates appointment, assigns it to concerning users and adds it to its
  // pointer
  void createAppointment();

  // Deletes appointment and unassigns it
  void cancelAppointment();

  // Assigns doctor to room, pacient, agenda and/or appointment
  void assignDoctor();

  // Creates a ticket
  void generateTicket();

  /* Generates a notification and adds it to the data base
  It is assigned to a User */
  void sendNotification();

  // Adds pacient to its place on pointer
  void addPacient(const Pacient &p);

  // Adds time slot to its place on pointer
  void addTime(const std::string &p);

  // Checks if user with said credentials exist on database
  bool login(std::string, std::string);
  
  // --------------------------
  const std::unique_ptr<std::unique_ptr<Pacient>[]> &getPacients() const;
  const std::unique_ptr<std::unique_ptr<Doctor>[]> &getDoctors() const;
  const std::unique_ptr<std::unique_ptr<Agenda>[]> &getAgendas() const;
  const std::unique_ptr<std::unique_ptr<Admin>[]> &getAdmins() const;
  const std::unique_ptr<std::unique_ptr<Ticket>[]> &getTickets() const;
  const std::unique_ptr<std::unique_ptr<Room>[]> &getRooms() const;
  const std::unique_ptr<std::unique_ptr<Appointment>[]> &getAppointments()
      const;
  const std::unique_ptr<std::string[]> &getTimesSlots() const;
  const std::unique_ptr<std::string[]> &getNotifications() const;
};

#endif  // APPOINTMENT_SYSTEM_H
