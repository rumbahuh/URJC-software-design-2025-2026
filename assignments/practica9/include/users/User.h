/**
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The User class represents a generic system user with an ID, email, and
 *        password. It serves as the base class (parent) for Pacient, Doctor,
 * and Admin classes. \param id \param nombre \param mailAddress \param password
 */

/**
 * \brief Represents a generic user in the system.
 */
#ifndef USER_H
#define USER_H

#include <iostream>
#include <memory>
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
   * \return User ptr Cloning interface (pure virtual).
   */
  virtual std::unique_ptr<User> clone() const = 0;

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

  /**
   * \brief Sets the user ID.
   * \param newId The new ID to assign.
   */
  void setId(int newId);

  /**
   * \brief Sets the username.
   * \param newName The new username to assign.
   */
  void setUsername(const std::string &newName);

  /**
   * \brief Sets the user email.
   * \param newMail The new email to assign.
   */
  void setMail(const std::string &newMail);

  /**
   * \brief Sets the user password.
   * \param newPw The new password to assign.
   */
  void setPassword(const std::string &newPw);
};

#endif  // USER_H
