/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  Diseñar e implementar un sistema de Login y Gestión de
  Usuarios utilizando la librería SQLite3 en un proyecto de C++.
*/

#include <vector>
#include <thread> //biblioteca que permite trabajar con hilos de C++
#include <chrono>
#include <iostream>

int main() {
  int choice = 0;

  while(choice != 3) {
    std::cout << "\n=== Plataforma gestión de citas ===\n"
              << "1. Registrar nuevo usuario\n"
              << "2. Iniciar Sesión\n"
              << "3. Salir\n"
              << "Seleccione una opción: ";
    std::cin >> choice;
    if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
            continue;
        }
    
        if (choice == 1) {
          std::cout << "Elección 1\n";
        } else if (choice == 2) {
          std::cout << "Elección 2\n";
        } else if (choice == 3){
          std::cout << "Terminating program\n";
        } else {
          std::cout << "Entrada inválida. Por favor, ingrese un número.\n";
        }
  }

  return 0;
}
