/**
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The User class represents a generic system user with an ID, email, and
 *        password. It serves as the base class (parent) for Pacient, Doctor, and Admin
 *        classes.
 * \param id
 * \param nombre
 * \param mailAddress
 * \param password
 */

/**
 * \brief Represents a generic user in the system.
 */
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
 protected:
  int id;
  std::string nombre;
  std::string mailAddress;

 private:
  std::string password;

 public:
  /**
   * \brief Constructor for User.
   * \param id User ID.
   * \param nombre User name.
   * \param mail User email.
   * \param pw User password.
   */
  User(int id, std::string nombre, std::string mail, std::string pw);

  virtual ~User() = default;

  /**
   * \return std::string The role of the user (pure virtual).
   */
  virtual std::string getRole() const = 0;

  /**
   * \return int The user ID.
   */
  int getId() const;

  /**
   * \return std::string The username.
   */
  std::string getUsername() const;

  /**
   * \return std::string The user email.
   */
  std::string getMail() const;

  /**
   * \return std::string The user password.
   */
  std::string getPassword() const;
};

#endif  // USER_H
