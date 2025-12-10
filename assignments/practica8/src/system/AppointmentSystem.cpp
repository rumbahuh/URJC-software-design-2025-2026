/**
 * \author Rebeca Castilla
 * \date 17-23/11/2025
 * \brief The AppointmentSystem class manages all system objects, including Pacients,
 *        Doctors, Admins, RobotAssistants, Tickets, Rooms, Agendas and Appointments.
 *        It provides methods to create and cancel appointments, assign doctors,
 *        generate tickets, and send notifications.
 *
 *        This class owns all objects, creates tables of the database and handles USER.
 */

#include "system/AppointmentSystem.h"

#include <sqlite3.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <set>
#include <vector>

#include "exceptions/exceptions.h"

#include "users/Admin.h"
#include "users/Doctor.h"
#include "users/User.h"

AppointmentSystem::AppointmentSystem() {
  // We open the database
  if (sqlite3_open("appointment_system.db", &db) != SQLITE_OK) {
    std::cerr << "Not possible to open database\n";
    throw std::runtime_error("Database error.");
  }
  initDataBase();

  agendas = std::make_unique<std::unique_ptr<Agenda>[]>(
      MAX_DOCTORS);  // We no longer use this because of the agenda table
  tickets = std::make_unique<std::unique_ptr<Ticket>[]>(MAX_TICKETS);
  rooms = std::make_unique<std::unique_ptr<Room>[]>(MAX_ROOMS);
  appointments =
      std::make_unique<std::unique_ptr<Appointment>[]>(MAX_APPOINTMENTS);
  timesSlots = std::make_unique<std::string[]>(MAX_TIME_SLOTS);
  notifications = std::make_unique<std::string[]>(MAX_NOTIFICATIONS);
}

// The destructor needs to close the database
AppointmentSystem::~AppointmentSystem() { sqlite3_close(db); }

void AppointmentSystem::initDataBase() {
  int exit = 0;
  char *errMsg = 0;

  // IMPORTANT: Activate foreign keys in SQLite (they are disabled by default)
  std::string enableFK = "PRAGMA foreign_keys = ON;";  // Very important
  exit = sqlite3_exec(db, enableFK.c_str(), NULL, 0, &errMsg);

  if (exit != SQLITE_OK) {
    std::cerr << "Error activating foreign keys: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Specification
  const char *sql_user =
      "CREATE TABLE IF NOT EXISTS USER ("
      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
      "USERNAME TEXT NOT NULL UNIQUE,"
      "PASSWORD TEXT NOT NULL,"
      "ROLE TEXT NOT NULL);";

  errMsg = nullptr;
  exit = sqlite3_exec(db, sql_user, NULL, 0, &errMsg);
  if (exit != SQLITE_OK) {
    std::cerr << "Error creating USER table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  } else {
    std::cout << "USER table created successfully!\n";
  }

  const char *sql_schedule =
      "CREATE TABLE IF NOT EXISTS SCHEDULE ("
      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
      "ID_DOCTOR INTEGER NOT NULL ,"
      "START TEXT NOT NULL ,"
      "END TEXT NOT NULL ,"
      "FOREIGN KEY (ID_DOCTOR) REFERENCES USER (ID) "
      "ON DELETE CASCADE "
      "ON UPDATE CASCADE);";

  exit = sqlite3_exec(db, sql_schedule, NULL, 0, &errMsg);
  if (exit != SQLITE_OK) {
    std::cerr << "Error creating AGENDA table: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  } else {
    std::cout << "AGENDA table created correctly with FK to USER." << std::endl;
  }
}

sqlite3 *AppointmentSystem::getDb() { return db; }

bool AppointmentSystem::insertUser() {
  int rc;

  std::string user_name, password, type;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Nombre de usuario: ";
  std::getline(std::cin, user_name);
  std::cout << "Contraseña: ";
  std::getline(std::cin, password);
  std::cout << "Tipo de usuario: ";
  std::getline(std::cin, type);

  // Validate type
  if (type != "Administrator" && type != "Doctor" && type != "Patient") {
    throw DatabaseError("Invalid user type. Must be Admin, Doctor or Patient.\n");
  }

  // SQL statement matching the USER table
  const char *sql =
      "INSERT INTO USER (USERNAME, PASSWORD, ROLE) VALUES (?, ?, "
      "?);";

  sqlite3_stmt *stmt;

  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    throw DatabaseError("Error preparing statement: " + 
                             std::string(sqlite3_errmsg(db)));
  }

  sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, type.c_str(), -1, SQLITE_TRANSIENT);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
        std::string msg = "Error inserting data: " + std::string(sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        throw DatabaseError(msg);
    }

    sqlite3_finalize(stmt);
    return true;
}

std::unique_ptr<User> AppointmentSystem::login() {
  int rc;
  std::string user_name, password;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Nombre de usuario: ";
  std::getline(std::cin, user_name);
  std::cout << "Contraseña: ";
  std::getline(std::cin, password);

  const char *sql =
      "SELECT ID, USERNAME, PASSWORD, ROLE "
      "FROM USER "
      "WHERE USERNAME = ? AND PASSWORD = ?;";

  sqlite3_stmt *stmt;
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    throw DatabaseError("Error preparing login query: " +
                            std::string(sqlite3_errmsg(db)));
  }

  sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    throw InvalidCredentialsError();
  }

    int id = sqlite3_column_int(stmt, 0);
    std::string nombre =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
    std::string pw =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
    std::string tipo =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));

    sqlite3_finalize(stmt);

    std::string dummy_mail = nombre + "@mail.com";

    // I create a derived type of the User class
    if (tipo == "Administrator") {
      return std::make_unique<Admin>(id, nombre, dummy_mail, pw);
    } else if (tipo == "Doctor") {
      return std::make_unique<Doctor>(id, nombre, dummy_mail, pw,
                                      "");  // add specialty later
    } else if (tipo == "Patient") {
      return std::make_unique<Pacient>(id, nombre, dummy_mail, pw);
    } else {
      throw DatabaseError("Unknown user role in DB: " + tipo);
    }
}

void AppointmentSystem::addRobot(std::unique_ptr<Robot> r) {
  robots.insert(std::move(r));
}

void AppointmentSystem::getAllRobotStatesTime() {
  const std::set<std::unique_ptr<Robot>, RobotCompare> &robots_ = getRobots();
  std::chrono::steady_clock::time_point ahora =
      std::chrono::steady_clock::now();

  if (robots_.empty()) {
    std::cout << "There are no registered robots\n";
    return;
  }

  // For aesthetic reasons I add a line break
  std::cout << "\n";

  for (std::set<std::unique_ptr<Robot>, RobotCompare>::const_iterator it =
           robots_.begin();
       it != robots_.end(); ++it) {
    const std::unique_ptr<Robot> &r_ptr = *it;
    Robot *r = r_ptr.get();

    std::string state = r->getEstado();

    std::chrono::duration ultimaActividad = ahora - r->getUltimaActividad();
    double segundos = std::chrono::duration<double>(ultimaActividad).count();

    std::cout << "[Robot " << r->getId() << "] " << "State: " << state << "\n";
    std::cout << "[Robot " << r->getId() << "] " << "Real time: " << segundos
              << "\n";
  }
}

Robot *AppointmentSystem::getNextAvailableRobot() {
  std::set<std::unique_ptr<Robot>, RobotCompare>::iterator it;
  std::set<std::unique_ptr<Robot>, RobotCompare>::iterator seleccionado_it =
      robots.end();
  std::chrono::steady_clock::time_point ahora =
      std::chrono::steady_clock::now();
  double mayorInactividad = -1.0;

  // We go through all the robots in the set
  for (it = robots.begin(); it != robots.end(); ++it) {
    const std::unique_ptr<Robot> &r_ptr = *it;
    Robot *r = r_ptr.get();

    if (r->getEstado() == "Libre") {
      std::chrono::duration<double> tiempoInactivo =
          ahora - r->getUltimaActividad();
      double segundos = tiempoInactivo.count();

      // If this robot has been free longer than the previous ones, we select it
      if (segundos > mayorInactividad) {
        mayorInactividad = segundos;
        seleccionado_it = it;
      }
    }
  }

  // If we found a free robot, we return a pointer to the most inactive one
  if (seleccionado_it != robots.end()) {
    Robot *seleccionado = (*seleccionado_it).get();

    std::cout << "[Robot " << seleccionado->getId()
              << "] selected (most inactive).\n";

    return seleccionado;
  }

  return nullptr;
}

const std::set<std::unique_ptr<Robot>, RobotCompare> &
AppointmentSystem::getRobots() const {
  return robots;
}

// --------------------------
void AppointmentSystem::createAppointment() {}

void AppointmentSystem::cancelAppointment() {}

void AppointmentSystem::assignDoctor() {}

void AppointmentSystem::generateTicket() {}

void AppointmentSystem::sendNotification() {}

void AppointmentSystem::addPacient(const Pacient &p) {}

void AppointmentSystem::addTime(const std::string &p) {}

const std::vector<std::unique_ptr<Pacient>> &AppointmentSystem::getPacients()
    const {
  return pacients;
}

std::vector<std::unique_ptr<Doctor>> &AppointmentSystem::getDoctors() {
  return doctors;
}

const std::unique_ptr<std::unique_ptr<Agenda>[]> &
AppointmentSystem::getAgendas() const {
  return agendas;
}

const std::vector<std::unique_ptr<Admin>> &AppointmentSystem::getAdmins()
    const {
  return admins;
}

const std::unique_ptr<std::unique_ptr<Ticket>[]> &
AppointmentSystem::getTickets() const {
  return tickets;
}

const std::unique_ptr<std::unique_ptr<Room>[]> &AppointmentSystem::getRooms()
    const {
  return rooms;
}

const std::unique_ptr<std::unique_ptr<Appointment>[]> &
AppointmentSystem::getAppointments() const {
  return appointments;
}

const std::unique_ptr<std::string[]> &AppointmentSystem::getTimesSlots() const {
  return timesSlots;
}

const std::unique_ptr<std::string[]> &AppointmentSystem::getNotifications()
    const {
  return notifications;
}
