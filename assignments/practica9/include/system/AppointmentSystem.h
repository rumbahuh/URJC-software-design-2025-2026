/**
 * \file AppointmentSystem.h
 * \author Rebeca Castilla
 * \date 13-19/12/2025
 * \brief The AppointmentSystem class manages all system objects, including
 * Pacients, Doctors, Admins, RobotAssistants, Tickets, Rooms, Agendas and
 * Appointments. It provides methods to create and cancel appointments, assign
 * doctors, generate tickets, and send notifications.
 *
 * This class owns all objects, creates tables of the database and handles USER.
 * \param db Database sqlite3 pointer
 * \throws DatabaseError If a low-level error occurs while interacting with
 * SQLite3
 */

/**
 * \brief Represents the main appointment management system.
 */
#ifndef APPOINTMENT_SYSTEM_H
#define APPOINTMENT_SYSTEM_H

#include <sqlite3.h>

#include <iostream>
#include <memory>
#include <set>
#include <vector>

#include "appointments/Agenda.h"
#include "appointments/Appointment.h"
#include "appointments/Notification.h"
#include "appointments/Room.h"
#include "appointments/Ticket.h"
#include "robot/Robot.h"
#include "users/Admin.h"
#include "users/Doctor.h"
#include "users/Pacient.h"
#include "users/User.h"

/**
 * \brief Comparator for sorting robots by last activity.
 */
struct RobotCompare {
  bool operator()(const std::unique_ptr<Robot> &a,
                  const std::unique_ptr<Robot> &b) const {
    return a->getUltimaActividad() < b->getUltimaActividad();
  }
};

class AppointmentSystem {
 protected:
  sqlite3 *db;
  AppointmentSystem();  // Crucial for singleton

 private:
  static AppointmentSystem *singleSystem;  // Pointer to the single instance

  static const int MAX_PACIENTS = 100;
  static const int MAX_DOCTORS = 20;
  static const int MAX_ADMINS = 5;
  static const int MAX_TICKETS = 200;
  static const int MAX_ROOMS = 50;
  static const int MAX_APPOINTMENTS = 200;
  static const int MAX_TIME_SLOTS = 14;
  static const int MAX_NOTIFICATIONS = 400;

  std::set<std::unique_ptr<Robot>, RobotCompare> robots;

  std::vector<std::unique_ptr<Pacient>> pacients;
  std::vector<std::unique_ptr<Doctor>> doctors;
  std::unique_ptr<std::unique_ptr<Agenda>[]> agendas;
  std::vector<std::unique_ptr<Admin>> admins;
  std::unique_ptr<std::unique_ptr<Ticket>[]> tickets;
  std::unique_ptr<std::unique_ptr<Room>[]> rooms;
  std::unique_ptr<std::unique_ptr<Appointment>[]> appointments;
  std::unique_ptr<std::string[]> timesSlots;
  std::unique_ptr<std::string[]> notifications;

 public:
  ~AppointmentSystem();

  static AppointmentSystem *getSystem();
  // singletons shoul not be cloneable or assignable:
  AppointmentSystem(AppointmentSystem &otherSystem) = delete;
  void operator=(const AppointmentSystem &) = delete;

  /**
   * \brief Initializes the SQLite database.
   */
  void initDataBase();

  /**
   * \return sqlite3* The database connection pointer.
   */
  sqlite3 *getDb();

  /**
   * \brief Inserts a user safely using prepared statements.
   * \return bool True if insertion succeeded.
   */
  bool insertUser();

  /**
   * \brief Logs in a user and returns a dynamic User instance.
   * \return std::unique_ptr<User> The user object (polymorphic).
   */
  std::unique_ptr<User> login();

  /**
   * \brief Adds a robot to the system.
   * \param robot The robot to add.
   */
  void addRobot(std::unique_ptr<Robot>);

  /**
   * \brief Prints all robots' states and time since last activity.
   */
  void getAllRobotStatesTime();

  /**
   * \return const std::set<std::unique_ptr<Robot>, RobotCompare>& Read-only
   * reference to robots.
   */
  const std::set<std::unique_ptr<Robot>, RobotCompare> &getRobots() const;

  /**
   * \return Robot* The next available inactive robot, or nullptr.
   */
  Robot *getNextAvailableRobot();

  // DE ADMIN -----
  /**
   * \brief Muestra todos los doctores en la base de datos
   */
  void displayAllDoctors();

  /**
   * \brief Crea un nuevo doctor en la base de datos
   */
  void createDoctor();

  /**
   * \brief Asigna agenda a un doctor
   */
  void assignAgenda();
  // -------
  /**
   * \brief Creates an appointment and assigns it.
   */
  void createAppointment();

  /**
   * \brief Cancels an appointment and unassigns it.
   */
  void cancelAppointment();

  /**
   * \brief Assigns a doctor to room, patient, agenda, and/or appointment.
   */
  void assignDoctor();

  /**
   * \brief Generates a ticket for an appointment.
   */
  void generateTicket();

  /**
   * \brief Generates and sends a notification to a user.
   */
  void sendNotification();

  /**
   * \brief Adds a patient to the system.
   * \param p The patient object.
   */
  void addPacient(const Pacient &p);

  /**
   * \brief Adds a time slot to the system.
   * \param p The time slot string.
   */
  void addTime(const std::string &p);

  const std::vector<std::unique_ptr<Pacient>> &getPacients() const;
  std::vector<std::unique_ptr<Doctor>> &getDoctors();
  const std::unique_ptr<std::unique_ptr<Agenda>[]> &getAgendas() const;
  const std::vector<std::unique_ptr<Admin>> &getAdmins() const;
  const std::unique_ptr<std::unique_ptr<Ticket>[]> &getTickets() const;
  const std::unique_ptr<std::unique_ptr<Room>[]> &getRooms() const;
  const std::unique_ptr<std::unique_ptr<Appointment>[]> &getAppointments()
      const;
  const std::unique_ptr<std::string[]> &getTimesSlots() const;
  const std::unique_ptr<std::string[]> &getNotifications() const;
};

#endif  // APPOINTMENT_SYSTEM_H
