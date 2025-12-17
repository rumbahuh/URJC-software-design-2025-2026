/**
 * \file exceptions.h
 * \author Rebeca Castilla
 * \date 7-11/12/2025
 * \brief Simple throw class
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

/**
 * \brief Exception for database-related errors.
 */
class DatabaseError : public std::runtime_error {
 public:
  /**
   * \brief Constructor.
   * \param msg Descriptive error message.
   */
  explicit DatabaseError(const std::string& msg) : std::runtime_error(msg) {}
};

/**
 * \brief Exception for invalid user credentials.
 */
class InvalidCredentialsError : public std::runtime_error {
 public:
  /**
   * \brief Constructor.
   * \param msg Error message (default: "Usuario o contraseña incorrectos.").
   */
  explicit InvalidCredentialsError(
      const std::string& msg = "Usuario o contraseña incorrectos.")
      : std::runtime_error(msg) {}
};

#endif  // EXCEPTIONS_H
