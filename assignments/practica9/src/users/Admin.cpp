/**
 * \author Rebeca Castilla
 * \date 15/12/2025
 * \brief The Admin class represents a single person
 *        object that manages its methods.
 */

#include <iostream>

#include "system/AppointmentSystem.h"
#include "users/Admin.h"

Admin::Admin(int id, std::string nombre, std::string mail, std::string pw)
    : User(id, nombre, mail, pw) {}

std::string Admin::getRole() const { return "Administrator"; }

void Admin::createDoctor(AppointmentSystem& system) { system.createDoctor(); }

void Admin::assignAgenda(AppointmentSystem& system) { system.assignAgenda(); }

void Admin::seeDoctorList(AppointmentSystem& system) {
  system.displayAllDoctors();
}

void Admin::seeAppointments() {}

void Admin::showMenu(AppointmentSystem& system) {
  int menuState = 0;

  while (menuState != 5) {
    std::cout << "\n=== Bienvenido, admin ===\n"
              << "1. Crear Doctor\n"
              << "2. Asignar Agenda\n"
              << "3. Ver Lista Doctores\n"
              << "4. Ver Citas\n"
              << "5. Salir\n"
              << "Seleccione una opción: ";

    std::cin >> menuState;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore();
      std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
      continue;
    }

    if (menuState == 1) {
      std::cout << "Elección 1\n";
      createDoctor(system);
    } else if (menuState == 2) {
      std::cout << "Elección 2\n";
      assignAgenda(system);
    } else if (menuState == 3) {
      std::cout << "Elección 3\n";
      seeDoctorList(system);
    } else if (menuState == 4) {
      std::cout << "Elección 4\n";
      seeAppointments();
    } else if (menuState == 5) {
      std::cout << "Exiting menu\n";
    } else {
      std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
    }
  }
}
