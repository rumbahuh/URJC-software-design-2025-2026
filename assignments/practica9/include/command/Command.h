/**
 * \file Command.h
 * \author Rebeca Castilla
 * \date 13-15/12/2025
 * \brief Abstract base class that defines the execution interface with a pure
 * virtual execute() method.
 */

#ifndef COMMAND_H
#define COMMAND_H

// Forward declaration to avoid circular dependency
class AppointmentSystem;

/**
 * \class Command
 * \brief Abstract interface for Command pattern.
 */
class Command {
 protected:
  // Receiver: object that actually performs the action
  AppointmentSystem* system;

 public:
  /**
   * \brief Constructor
   * \param sys Pointer to the AppointmentSystem (receiver)
   */
  explicit Command(AppointmentSystem* sys) : system(sys) {}

  /**
   * \brief Executes the command
   */
  virtual void execute() = 0;

  /**
   * \brief Virtual destructor
   */
  virtual ~Command() = default;
};

#endif  // COMMAND_H
