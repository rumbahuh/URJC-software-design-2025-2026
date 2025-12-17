/**
 * \author Rebeca Castilla
 * \date 15/12/2025
 * \brief The Admin class with proper command memory management
 */
#include "users/Admin.h"
#include <iostream>
#include <limits>
#include "command/AssignAgendaCommand.h"
#include "command/CreateDoctorCommand.h"
#include "command/ViewDoctorsCommand.h"
#include "system/AppointmentSystem.h"

Admin::Admin(int id, std::string nombre, std::string mail, std::string pw)
    : User(id, nombre, mail, pw) {}

// Copy constructor - commandMap cannot be copied (unique_ptr), so leave it empty
// It will be set up when showMenu() is called
Admin::Admin(const Admin& other) 
    : User(other) {
  // commandMap is intentionally left empty
  // It will be populated by setupCommands() when needed
}

std::string Admin::getRole() const { return "Administrator"; }

void Admin::createDoctor(AppointmentSystem& system) { 
  system.createDoctor(); 
}

void Admin::assignAgenda(AppointmentSystem& system) { 
  system.assignAgenda(); 
}

void Admin::seeDoctorList(AppointmentSystem& system) {
  system.displayAllDoctors();
}

void Admin::seeAppointments() {
  std::cout << "Ver citas - funcionalidad pendiente\n";
}

void Admin::setupCommands(AppointmentSystem* sys) {
  // Clear existing commands (unique_ptr automatically deletes old ones)
  commandMap.clear();
  
  // Create new commands using make_unique (C++14) or unique_ptr with new
  commandMap[1] = std::unique_ptr<Command>(new CreateDoctorCommand(sys));
  commandMap[2] = std::unique_ptr<Command>(new AssignAgendaCommand(sys));
  commandMap[3] = std::unique_ptr<Command>(new ViewDoctorsCommand(sys));
  
  // Or with C++14:
  // commandMap[1] = std::make_unique<CreateDoctorCommand>(sys);
  // commandMap[2] = std::make_unique<AssignAgendaCommand>(sys);
  // commandMap[3] = std::make_unique<ViewDoctorsCommand>(sys);
}

void Admin::showMenu(AppointmentSystem& system) {
  setupCommands(&system);
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
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
      continue;
    }
    
    if (menuState == 5) {
      std::cout << "Saliendo del menú.\n";
      break;
    }
    
    if (menuState == 4) {
      seeAppointments();
    } else {
      auto it = commandMap.find(menuState);
      if (it != commandMap.end() && it->second != nullptr) {
        it->second->execute();
      } else {
        std::cout << "Opción inválida.\n";
      }
    }
  }
  
  // Commands are automatically deleted when commandMap goes out of scope
}

// Destructor must be defined in .cpp where Command is fully defined
Admin::~Admin() {
  // unique_ptr automatically cleans up commands
}