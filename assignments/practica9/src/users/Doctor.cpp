/**
 * \file Doctor.cpp
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Doctor class represents a single person
 * object with an assigned specialty and its methods.
 * \param room
 * \param specialty
 */

#include "users/Doctor.h"

#include "appointments/Agenda.h"
#include "appointments/Room.h"

Doctor::Doctor(int id, std::string nombre, std::string mail, std::string pw,
               std::string specialty)
    : User(id, nombre, mail, pw), room(""), specialty(specialty) {}

std::string Doctor::getRole() const { return "Doctor"; }

void Doctor::confirmAssistance() {}
void Doctor::modifyAgenda() {}
void Doctor::addNotesToAppointment() {}

void Doctor::showMenu() {
  int menuState = 0;

  while (menuState != 4) {
    std::cout << "\n=== Bienvenido, doctor ===\n"
              << "1. Confirmar Asistencia\n"
              << "2. Modificar Agenda\n"
              << "3. Añadir Notas a Cita\n"
              << "4. Salir\n"
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
      confirmAssistance();

    } else if (menuState == 2) {
      std::cout << "Elección 2\n";
      modifyAgenda();

    } else if (menuState == 3) {
      std::cout << "Elección 3\n";
      addNotesToAppointment();

    } else if (menuState == 4) {
      std::cout << "Exiting menu\n";
    } else {
      std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
    }
  }
}
