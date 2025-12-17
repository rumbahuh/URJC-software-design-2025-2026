/**
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Pacient class represents a single patient in the system.
 *        It provides methods to interact with appointments, check available
 * time slots, modify personal data, and confirm attendance for scheduled
 * appointments.
 */

#include "users/Pacient.h"

#include "appointments/Appointment.h"

Pacient::Pacient(int id, std::string nombre, std::string mail, std::string pw)
    : User(id, nombre, mail, pw) {}

std::string Pacient::getRole() const { return "Patient"; }

void Pacient::checkTimeSlots() {}

void Pacient::modifyData(std::string id, std::string password) {}

void Pacient::confirmAssistance(const Appointment &p) {}

void Pacient::requestAppointment() {}
void Pacient::seeMyAppointments() {}
void Pacient::showMenu() {
  int menuState = 0;

  while (menuState != 3) {
    std::cout << "\n=== Bienvenido, paciente ===\n"
              << "1. Solicitar Cita\n"
              << "2. Ver Mis Citas\n"
              << "3. Salir\n"
              << "Seleccione una opción: ";
    std::cin >> menuState;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
      continue;
    }

    if (menuState == 1) {
      std::cout << "Elección 1\n";
    } else if (menuState == 2) {
      std::cout << "Elección 2\n";
    } else if (menuState == 3) {
      std::cout << "Exiting menu\n";
    } else {
      std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
    }
  }
}
