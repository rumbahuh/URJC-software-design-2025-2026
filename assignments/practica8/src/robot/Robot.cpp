/**
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

#include "robot/Robot.h"

#include <chrono>
#include <iostream>
#include <thread>

#include "appointments/Appointment.h"
#include "users/Pacient.h"

Robot::Robot(int idRobot) : id(idRobot), estado("Libre") {
  ultimaActividad = std::chrono::steady_clock::now();
}

int Robot::getId() const { return id; }

void Robot::dummy(int segundos) {
  // Creo un hilo para simular la tarea sin bloquear el hilo principal
  std::thread([this, segundos]() {
    {
      // Protegemos el acceso al estado con mutex
      std::lock_guard<std::mutex> lock(mtx);
      estado = "Ocupado";
      std::cout << "[Robot " << id << "] acompañado por " << segundos
                << "segundos. \n";
    }

    // Esta linea simula el tiempo de acompañamiento del robot al paciente
    std::this_thread::sleep_for(std::chrono::seconds(segundos));
    {
      // Acá protege el acceso al estado para cambiar el estado
      std::lock_guard<std::mutex> lock(mtx);
      estado = "Libre";
      ultimaActividad = std::chrono::steady_clock::now();
      std::cout << "[Robot " << id << "] Finalizó. Estado: Libre. \n";
    }
  }).detach();  // Hilo separado. No bloquea.
}

std::string Robot::getEstado() const {
  std::lock_guard<std::mutex> lock(mtx);
  return estado;
}

std::chrono::steady_clock::time_point Robot::getUltimaActividad() const {
  std::lock_guard<std::mutex> lock(mtx);
  return ultimaActividad;
}

// ---------------------------------

std::string Robot::requestIds() { return ""; }

void Robot::checkAppointments(std::string pacientId) {}

void Robot::printTicket(const Appointment &p) {}

void Robot::acompanyToRoom() {}

void Robot::updatePosition() {}

void Robot::sendHumanToInfoSpot() {}
