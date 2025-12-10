/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  Diseñar e implementar un sistema de Login y Gestión de
  Usuarios utilizando la librería SQLite3 en un proyecto de C++.
*/

#include <chrono>
#include <iostream>
#include <thread>  //biblioteca que permite trabajar con hilos de C++
#include <vector>

#include "AppointmentSystem.h"
#include "User.h"

int main() {
  /*
  To check:

  rumbahuh@stokibot:~/Desktop/URJC/RoboticSoftware_Tercero/DISEÑO/PRACTICAS/URJC-software-design-2025-2026/assignments/practica7$
  sqlite3 appointment_system.db SQLite version 3.45.1 2024-01-30 16:01:20 Enter
  ".help" for usage hints. sqlite> PRAGMA table_info(USUARIOS);
  0|ID|INTEGER|0||1
  1|NOMBRE_USUARIO|TEXT|1||0
  2|CONTRASENA|TEXT|1||0
  3|TIPO|TEXT|1||0
  sqlite> SELECT * FROM USUARIOS;
  1|rebe|rebe|Patient
  sqlite> .quit
  */

  int choice = 0;
  AppointmentSystem foundation = AppointmentSystem();

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
      foundation.insertUser();

    } else if (choice == 2) {
      std::cout << "Elección 2\n";
      std::unique_ptr<User> user = foundation.login();

      if (!user) {
        std::cout << "Usuario o contraseña incorrectos.\n";
        continue;
      }

      std::cout << "Login exitoso. Rol: " << user->getRole() << "\n";

      // --- POLYMORPHIC HANDLING ---
      std::string role = user->getRole();

      if (role == "Doctor") {
        Doctor* d = dynamic_cast<Doctor*>(user.get());
        if (d) {
          d->showMenu();
        }
      } else if (role == "Administrator") {
        Admin* a = dynamic_cast<Admin*>(user.get());
        if (a) {
          a->showMenu(foundation);
        }
      } else if (role == "Patient") {
        Pacient* p = dynamic_cast<Pacient*>(user.get());
        if (p) {
          p->showMenu();
        }
      } else {
        std::cout << "Rol desconocido.\n";
      }
    } else if (choice == 3) {
      std::cout << "Terminating program\n";
    } else {
      std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
    }
  }
  foundation.~AppointmentSystem();
  return 0;
}
