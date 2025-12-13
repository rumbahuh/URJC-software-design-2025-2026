/**
 * \author Rebeca Castilla
 * \date 13/11/2025
 * \brief The Admin class represents a single person
 *        object that manages its methods.
 */

#include "users/Admin.h"

#include <iostream>
#include <string>
#include <vector>

#include "system/AppointmentSystem.h"
#include "users/Doctor.h"

struct DoctorShow {
  int id;
  std::string name;
};

Admin::Admin(int id, std::string nombre, std::string mail, std::string pw)
    : User(id, nombre, mail, pw) {}

std::string Admin::getRole() const { return "Administrator"; }

void Admin::seeDoctorList(AppointmentSystem& system) {
  int rc;

  const char* sql = "SELECT ID, USERNAME FROM USER WHERE ROLE = 'Doctor';";

  sqlite3_stmt* stmt;
  rc = sqlite3_prepare_v2(system.getDb(), sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    std::cerr << "Error al preparar la sentencia: "
              << sqlite3_errmsg(system.getDb()) << std::endl;
    sqlite3_finalize(stmt);
    return;
  }

  std::vector<DoctorShow> doctors;

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    DoctorShow p;
    p.id = sqlite3_column_int(stmt, 0);
    p.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    doctors.push_back(p);
  }

  sqlite3_finalize(stmt);

  std::cout << "\n--- Datos de Doctores almacenados en std::vector ---\n";
  if (doctors.empty()) {
    std::cout << "No hay doctores registrados.\n";
  } else {
    for (const auto& p : doctors) {
      std::cout << "ID = " << p.id << " | Nombre = " << p.name
                << " (ID: " << p.id << ")" << std::endl;
    }
  }
}

void Admin::assignAgenda(AppointmentSystem& system) {
  int rc;
  char* errMsg = 0;

  // Activar foreign keys
  rc = sqlite3_exec(system.getDb(), "PRAGMA foreign_keys = ON;", NULL, 0,
                    &errMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Error al activar foreign keys: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }

  // Mostramos los doctores disponibles
  std::cout << "=== DOCTORES DISPONIBLES ===" << std::endl;
  const char* sqlSelect =
      "SELECT ID, USERNAME FROM USER WHERE ROLE = 'Doctor';";
  sqlite3_stmt* stmtSelect;

  rc = sqlite3_prepare_v2(system.getDb(), sqlSelect, -1, &stmtSelect, NULL);
  if (rc == SQLITE_OK) {
    while (sqlite3_step(stmtSelect) == SQLITE_ROW) {
      int id = sqlite3_column_int(stmtSelect, 0);
      const unsigned char* nombre = sqlite3_column_text(stmtSelect, 1);
      std::cout << "ID: " << id << " - " << nombre << std::endl;
    }
    sqlite3_finalize(stmtSelect);
  }
  std::cout << "============================\n" << std::endl;

  int idDoctor;
  std::string start, end;

  std::cin.ignore();
  std::cout << "ID: ";
  std::cin >> idDoctor;
  std::cout << "Inicio de jornada:";
  std::cin >> start;
  std::cout << "Final de jornada: ";
  std::cin >> end;

  // Sentencia que coincide con la tabla SCHEDULE
  const char* sql =
      "INSERT INTO SCHEDULE (ID_DOCTOR, START, END) VALUES (?, ?, ?);";

  sqlite3_stmt* stmt;
  rc = sqlite3_prepare_v2(system.getDb(), sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    std::cerr << "Error al preparar la sentencia: "
              << sqlite3_errmsg(system.getDb()) << std::endl;
    return;
  }

  // Enlazamos los valores
  sqlite3_bind_int(stmt, 1, idDoctor);
  sqlite3_bind_text(stmt, 2, start.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, end.c_str(), -1, SQLITE_TRANSIENT);

  // Lo ejecutamos
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::cerr << "Error al asignar agenda: " << sqlite3_errmsg(system.getDb())
              << std::endl;
    if (std::string(sqlite3_errmsg(system.getDb())).find("FOREIGN KEY") !=
        std::string::npos) {
      std::cerr << "La persona con ID " << idDoctor << " no existe."
                << std::endl;
    }
  } else {
    std::cout << "Agenda asignada correctamente.\n";
    std::cout << "ID del doctor: " << idDoctor << std::endl;
  }

  sqlite3_finalize(stmt);
}

void Admin::createDoctor(AppointmentSystem& system) {
  int rc;

  std::string user_name, password;
  std::string type = "Doctor";

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cout << "Nombre de usuario: ";
  std::getline(std::cin, user_name);
  std::cout << "Contraseña: ";
  std::getline(std::cin, password);

  // Sentencia SQL que coincide con la tabla USER
  const char* sql =
      "INSERT INTO USER (USERNAME, PASSWORD, ROLE) VALUES (?, ?, "
      "?);";

  sqlite3_stmt* stmt;
  rc = sqlite3_prepare_v2(system.getDb(), sql, -1, &stmt, NULL);
  if (rc != SQLITE_OK) {
    std::cerr << "Error al preparar la sentencia: "
              << sqlite3_errmsg(system.getDb()) << std::endl;

    sqlite3_finalize(stmt);
    return;
  }

  sqlite3_bind_text(stmt, 1, user_name.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
  sqlite3_bind_text(stmt, 3, type.c_str(), -1, SQLITE_TRANSIENT);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::cerr << "Error al insertar datos: " << sqlite3_errmsg(system.getDb())
              << std::endl;
  } else {
    std::cout << "Datos insertados correctamente.\n";
  }

  sqlite3_finalize(stmt);
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
