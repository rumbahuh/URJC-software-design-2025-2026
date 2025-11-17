/*
Author: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  File to insert the first functionality of the system, register.
*/

#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3* db;
    int rc;
    char *errMsg = 0;

    // We open the database
    rc = sqlite3_open("appointment_system.db", &db);
    if (rc) {
        std::cerr << "No se pudo abrir la base de datos: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    std::string user_name, password, type;

    std::cout << "Nombre de usuario: ";
    std::getline(std::cin, usuario);
    std::cout << "Contraseña: ";
    std::getline(std::cin, password);
    std::cout << "Tipo de usuario: ";
    std::getline(std::cin, tipo);
    // ------------------------------------------

    // Sentencia SQL que coincide con la tabla USER
    const char* sql = "INSERT INTO USER (NOMBRE_USUARIO, CONTRASEÑA, TIPO) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Error al preparar la sentencia: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, usuario.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, tipo.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Error al insertar datos: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Datos insertados correctamente.\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}
