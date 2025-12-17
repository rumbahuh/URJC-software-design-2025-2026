/**
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief Diseñar e implementar un sistema de Login y Gestión de
 *        Usuarios utilizando la librería SQLite3 en un proyecto de C++.
 */

#include <chrono>
#include <iostream>
#include <thread>  //biblioteca que permite trabajar con hilos de C++
#include <vector>

#include "exceptions/exceptions.h"
#include "system/AppointmentSystem.h"
#include "users/User.h"

int main() {
  int choice = 0;
  AppointmentSystem* foundation = AppointmentSystem::getSystem();
  // AppointmentSystem* anotherSystem = AppointmentSystem::getSystem(); exec err

  while (choice != 3) {
    std::cout << "\n=== Plataforma gestión de citas ===\n"
              << "1. Registrar nuevo usuario\n"
              << "2. Iniciar Sesión\n"
              << "3. Salir\n"
              << "Seleccione una opción: ";
    std::cin >> choice;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n');  // discard invalid input
      std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
      continue;
    }

    if (choice == 1) {
      std::cout << "Elección 1\n";
      try {
        foundation->insertUser();
        std::cout << "Usuario registrado correctamente.\n";
      } catch (const DatabaseError& e) {
        std::cout << "Error en la base de datos: " << e.what() << "\n";
      }

    } else if (choice == 2) {
      std::cout << "Elección 2\n";
      try {
        std::unique_ptr<User> user = foundation->login();

        std::cout << "Login exitoso. Rol: " << user->getRole() << "\n";

        std::string role = user->getRole();

        if (role == "Doctor") {
          Doctor* d = dynamic_cast<Doctor*>(user.get());
          if (d) {
            d->showMenu();
          }
        } else if (role == "Administrator") {
          Admin* a = dynamic_cast<Admin*>(user.get());
          if (a) {
            a->showMenu(*foundation);
          }
        } else if (role == "Patient") {
          Pacient* p = dynamic_cast<Pacient*>(user.get());
          if (p) {
            p->showMenu();
          }
        } else {
          std::cout << "Rol desconocido.\n";
        }

      } catch (const InvalidCredentialsError& e) {
        std::cout << e.what() << "\n";
      } catch (const DatabaseError& e) {
        std::cout << "Error en la base de datos: " << e.what() << "\n";
      }

    } else if (choice == 3) {
      std::cout << "Terminating program\n";
    } else {
      std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
    }
  }
  
  delete foundation;  // Clean up singleton
  return 0;
}
