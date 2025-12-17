/**
 * \file AppointmentSystem.cpp
 * \author Rebeca Castilla
 * \date 13/12/2025
 * \brief The AppointmentSystem class manages all system objects, including
 * Pacients, Doctors, Admins, RobotAssistants, Tickets, Rooms, Agendas and
 * Appointments.
 */

#include "system/AppointmentSystem.h"

#include <sqlite3.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

#include "exceptions/exceptions.h"
#include "users/Admin.h"
#include "users/Doctor.h"
#include "users/PrototypeRegistry.h"
#include "users/User.h"

AppointmentSystem* AppointmentSystem::singleSystem = nullptr;

AppointmentSystem::AppointmentSystem() {
  if (sqlite3_open("appointment_system.db", &db) != SQLITE_OK) {
    std::cerr << "Not possible to open database\n";
    throw std::runtime_error("Database error.");
  }

  initDataBase();

  agendas = std::make_unique<std::unique_ptr<Agenda>[]>(MAX_DOCTORS);
  tickets = std::make_unique<std::unique_ptr<Ticket>[]>(MAX_TICKETS);
  rooms = std::make_unique<std::unique_ptr<Room>[]>(MAX_ROOMS);
  appointments =
      std::make_unique<std::unique_ptr<Appointment>[]>(MAX_APPOINTMENTS);
  timesSlots = std::make_unique<std::string[]>(MAX_TIME_SLOTS);
  notifications = std::make_unique<std::string[]>(MAX_NOTIFICATIONS);
}

AppointmentSystem::~AppointmentSystem() { sqlite3_close(db); }

AppointmentSystem* AppointmentSystem::getSystem() {
  if (singleSystem == nullptr)
    singleSystem = new AppointmentSystem();
  else
    std::cout << "Error: trying to get another AppointmentSystem instance\n";

  return singleSystem;
}

void AppointmentSystem::initDataBase() {
  int exit = 0;
  char* errMsg = 0;

  // IMPORTANT: Activate foreign keys in SQLite (they are disabled by default)
  std::string enableFK = "PRAGMA foreign_keys = ON;";  // Very important
  exit = sqlite3_exec(db, enableFK.c_str(), NULL, 0, &errMsg);

  if (exit != SQLITE_OK) {
    std::cerr << "Error activating foreign keys: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Specification
  const char* sql_user =
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

  const char* sql_schedule =
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

sqlite3* AppointmentSystem::getDb() { return db; }

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

  if (type != "Administrator" && type != "Doctor" && type != "Patient") {
    throw DatabaseError("Invalid user type.");
  }

  const char* sql =
      "INSERT INTO USER (USERNAME, PASSWORD, ROLE) VALUES (?, ?, ?);";

  sqlite3_stmt* stmt;
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) throw DatabaseError(sqlite3_errmsg(db));

  sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, type.c_str(), -1, SQLITE_TRANSIENT);

  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);

  if (rc != SQLITE_DONE) throw DatabaseError(sqlite3_errmsg(db));

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

  const char* sql =
      "SELECT ID, USERNAME, PASSWORD, ROLE FROM USER "
      "WHERE USERNAME = ? AND PASSWORD = ?;";

  sqlite3_stmt* stmt;
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) throw DatabaseError(sqlite3_errmsg(db));

  sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_ROW) {
    sqlite3_finalize(stmt);
    throw InvalidCredentialsError();
  }

  int id = sqlite3_column_int(stmt, 0);
  std::string name =
      reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
  std::string pw = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
  std::string role =
      reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

  sqlite3_finalize(stmt);

  int choice = (role == "Administrator") ? 1 : (role == "Doctor") ? 2 : 3;

  std::unique_ptr<User> u(PrototypeRegistry::makeUser(choice));
  u->setId(id);
  u->setUsername(name);
  u->setPassword(pw);
  u->setMail(name + "@mail.com");

  return u;
}

void AppointmentSystem::addRobot(std::unique_ptr<Robot> r) {
  robots.insert(std::move(r));
}

void AppointmentSystem::getAllRobotStatesTime() {
  const std::set<std::unique_ptr<Robot>, RobotCompare>& robots_ = getRobots();
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
    const std::unique_ptr<Robot>& r_ptr = *it;
    Robot* r = r_ptr.get();

    std::string state = r->getEstado();

    std::chrono::duration ultimaActividad = ahora - r->getUltimaActividad();
    double segundos = std::chrono::duration<double>(ultimaActividad).count();

    std::cout << "[Robot " << r->getId() << "] " << "State: " << state << "\n";
    std::cout << "[Robot " << r->getId() << "] " << "Real time: " << segundos
              << "\n";
  }
}

Robot* AppointmentSystem::getNextAvailableRobot() {
  std::set<std::unique_ptr<Robot>, RobotCompare>::iterator it;
  std::set<std::unique_ptr<Robot>, RobotCompare>::iterator seleccionado_it =
      robots.end();
  std::chrono::steady_clock::time_point ahora =
      std::chrono::steady_clock::now();
  double mayorInactividad = -1.0;

  // We go through all the robots in the set
  for (it = robots.begin(); it != robots.end(); ++it) {
    const std::unique_ptr<Robot>& r_ptr = *it;
    Robot* r = r_ptr.get();

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
    Robot* seleccionado = (*seleccionado_it).get();

    std::cout << "[Robot " << seleccionado->getId()
              << "] selected (most inactive).\n";

    return seleccionado;
  }

  return nullptr;
}

void AppointmentSystem::displayAllDoctors() {
  const char* sql = "SELECT ID, USERNAME FROM USER WHERE ROLE='Doctor';";
  sqlite3_stmt* stmt;

  if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
    std::cerr << sqlite3_errmsg(db) << std::endl;
    return;
  }

  std::cout << "\n--- Lista de Doctores ---\n";
  bool empty = true;

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    empty = false;
    std::cout << "ID: " << sqlite3_column_int(stmt, 0)
              << " | Nombre: " << sqlite3_column_text(stmt, 1) << std::endl;
  }

  if (empty) std::cout << "No hay doctores.\n";

  sqlite3_finalize(stmt);
}

void AppointmentSystem::createDoctor() {
  std::string user_name, password;
  std::string type = "Doctor";

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Nombre de usuario: ";
  std::getline(std::cin, user_name);
  std::cout << "Contraseña: ";
  std::getline(std::cin, password);

  const char* sql =
      "INSERT INTO USER (USERNAME, PASSWORD, ROLE) VALUES (?, ?, ?);";

  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, type.c_str(), -1, SQLITE_TRANSIENT);

  if (sqlite3_step(stmt) == SQLITE_DONE)
    std::cout << "Doctor creado correctamente.\n";
  else
    std::cerr << sqlite3_errmsg(db) << std::endl;

  sqlite3_finalize(stmt);
}

void AppointmentSystem::assignAgenda() {
  int idDoctor;
  std::string start, end;

  displayAllDoctors();

  std::cout << "ID Doctor: ";
  std::cin >> idDoctor;
  std::cout << "Inicio jornada: ";
  std::cin >> start;
  std::cout << "Fin jornada: ";
  std::cin >> end;

  const char* sql =
      "INSERT INTO SCHEDULE (ID_DOCTOR, START, END) VALUES (?, ?, ?);";

  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  sqlite3_bind_int(stmt, 1, idDoctor);
  sqlite3_bind_text(stmt, 2, start.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, end.c_str(), -1, SQLITE_TRANSIENT);

  if (sqlite3_step(stmt) == SQLITE_DONE)
    std::cout << "Agenda asignada correctamente.\n";
  else
    std::cerr << sqlite3_errmsg(db) << std::endl;

  sqlite3_finalize(stmt);
}

const std::set<std::unique_ptr<Robot>, RobotCompare>&
AppointmentSystem::getRobots() const {
  return robots;
}

// --------------------------
void AppointmentSystem::createAppointment() {}
void AppointmentSystem::cancelAppointment() {}
void AppointmentSystem::assignDoctor() {}
void AppointmentSystem::generateTicket() {}
void AppointmentSystem::sendNotification() {}
void AppointmentSystem::addPacient(const Pacient&) {}
void AppointmentSystem::addTime(const std::string&) {}

const std::vector<std::unique_ptr<Pacient>>& AppointmentSystem::getPacients()
    const {
  return pacients;
}

std::vector<std::unique_ptr<Doctor>>& AppointmentSystem::getDoctors() {
  return doctors;
}

const std::unique_ptr<std::unique_ptr<Agenda>[]>&
AppointmentSystem::getAgendas() const {
  return agendas;
}

const std::vector<std::unique_ptr<Admin>>& AppointmentSystem::getAdmins()
    const {
  return admins;
}

const std::unique_ptr<std::unique_ptr<Ticket>[]>&
AppointmentSystem::getTickets() const {
  return tickets;
}

const std::unique_ptr<std::unique_ptr<Room>[]>& AppointmentSystem::getRooms()
    const {
  return rooms;
}

const std::unique_ptr<std::unique_ptr<Appointment>[]>&
AppointmentSystem::getAppointments() const {
  return appointments;
}

const std::unique_ptr<std::string[]>& AppointmentSystem::getTimesSlots() const {
  return timesSlots;
}

const std::unique_ptr<std::string[]>& AppointmentSystem::getNotifications()
    const {
  return notifications;
}
