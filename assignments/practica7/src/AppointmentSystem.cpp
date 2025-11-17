/*
Authoress: Rebeca Castilla
Date: 19-29/10/2025
Objective:
  The AppointmentSystem class manages all system objects, including Pacients,
  Doctors, Admins, RobotAssistants, Tickets, Rooms, Agendas and Appointments.
  It provides methods to create and cancel appointments, assign doctors,
  generate tickets, and send notifications.

  This class owns all objects in the system through unique_ptr.
*/

#include "AppointmentSystem.h"

#include <sqlite3.h>
#include <algorithm>
#include <chrono>
#include <vector>
#include <chrono>
#include <iostream>
#include <set>

AppointmentSystem::AppointmentSystem() {
  // We open the database
  if (sqlite3_open("appointment_system.db", &db) != SQLITE_OK) {
        std::cerr << "No se pudo abrir la base de datos\n";
        throw std::runtime_error("Database error.");
    }
  
  pacients = std::make_unique<std::unique_ptr<Pacient>[]>(MAX_PACIENTS);
  doctors = std::make_unique<std::unique_ptr<Doctor>[]>(MAX_DOCTORS);
  agendas = std::make_unique<std::unique_ptr<Agenda>[]>(MAX_DOCTORS);
  admins = std::make_unique<std::unique_ptr<Admin>[]>(MAX_ADMINS);
  tickets = std::make_unique<std::unique_ptr<Ticket>[]>(MAX_TICKETS);
  rooms = std::make_unique<std::unique_ptr<Room>[]>(MAX_ROOMS);
  appointments =
      std::make_unique<std::unique_ptr<Appointment>[]>(MAX_APPOINTMENTS);
  timesSlots = std::make_unique<std::string[]>(MAX_TIME_SLOTS);
  notifications = std::make_unique<std::string[]>(MAX_NOTIFICATIONS);
}

// The destructor needs to close the database
AppointmentSystem::~AppointmentSystem() {
    sqlite3_close(db);
}

void AppointmentSystem::addRobot(std::unique_ptr<Robot> r) { robots.insert(std::move(r)); }

void AppointmentSystem::getAllRobotStatesTime() {
  const std::set<std::unique_ptr<Robot>, RobotCompare> &robots_ = getRobots();
  std::chrono::steady_clock::time_point ahora =
      std::chrono::steady_clock::now();

  if (robots_.empty()) {
    std::cout << "No hay robots registrados\n";
    return;
  }

  // Por cuestiones estéticas añado un salto de línea
  std::cout << "\n";

  for (std::set<std::unique_ptr<Robot>, RobotCompare>::const_iterator it =
           robots_.begin();
       it != robots_.end(); ++it) {
    const std::unique_ptr<Robot> &r_ptr = *it;
    Robot *r = r_ptr.get();

    std::string state = r->getEstado();

    std::chrono::duration ultimaActividad = ahora - r->getUltimaActividad();
    double segundos = std::chrono::duration<double>(ultimaActividad).count();

    std::cout << "[Robot " << r->getId() << "] " << "Estado: " << state << "\n";
    std::cout << "[Robot " << r->getId() << "] " << "Tiempo real: " << segundos
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

  // Recorremos todos los robots del set
  for (it = robots.begin(); it != robots.end(); ++it) {
    const std::unique_ptr<Robot> &r_ptr = *it;
    Robot *r = r_ptr.get();

    if (r->getEstado() == "Libre") {
      std::chrono::duration<double> tiempoInactivo =
          ahora - r->getUltimaActividad();
      double segundos = tiempoInactivo.count();

      // Si este robot lleva más tiempo libre que los anteriores, lo
      // seleccionamos
      if (segundos > mayorInactividad) {
        mayorInactividad = segundos;
        seleccionado_it = it;
      }
    }
  }

  // Si encontramos algún robot libre, devolvemos un puntero al más inactivo
  if (seleccionado_it != robots.end()) {
    Robot *seleccionado = (*seleccionado_it).get();

    std::cout << "[Robot " << seleccionado->getId()
              << "] seleccionado (más inactivo).\n";

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

bool AppointmentSystem::login(std::string id, std::string password) {
  return false;
}

const std::unique_ptr<std::unique_ptr<Pacient>[]> &
AppointmentSystem::getPacients() const {
  return pacients;
}

const std::unique_ptr<std::unique_ptr<Doctor>[]> &
AppointmentSystem::getDoctors() const {
  return doctors;
}

const std::unique_ptr<std::unique_ptr<Admin>[]> &AppointmentSystem::getAdmins()
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

const std::unique_ptr<std::unique_ptr<Agenda>[]> &
AppointmentSystem::getAgendas() const {
  return agendas;
}
