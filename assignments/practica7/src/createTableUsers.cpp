/*
Author: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  File to create the User tables for the database.
  It runs once at the start of the system.
*/

#include <sqlite3.h>

#include <iostream>

int main() {
  sqlite3* db;
  if (sqlite3_open("appointment_system.db", &db) != SQLITE_OK) {
    std::cerr << "Cannot open database\n";
    return 1;
  }

  // Specification
      const char *sql_user =
      "CREATE TABLE IF NOT EXISTS USER ("
      "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
      "USERNAME TEXT NOT NULL UNIQUE,"
      "PASSWORD TEXT NOT NULL,"
      "ROLE TEXT NOT NULL);";

        char* errMsg = nullptr;
    if (sqlite3_exec(db, sql_user, nullptr, nullptr, &errMsg) != SQLITE_OK) {
      std::cerr << "Error creating USER table: " << errMsg << "\n";
      sqlite3_free(errMsg);
    } else {
      std::cout << "USER table created successfully!\n";
    }

    sqlite3_close(db);
    return 0;
}
