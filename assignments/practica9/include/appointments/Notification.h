/**
 * \author Rebeca Castilla
 * \date 17-27/11/2025
 * \brief The Notification class represents a single message
 *        object which contains details such as type, time, 
 *        date, content and id.
 * \param type
 * \param time
 * \param date
 * \param message
 * \param receiver
 */

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <iostream>

class User;

class Notification {
 private:
  std::string type;
  std::string time;
  std::string date;
  std::string message;
  std::string receiver;

 public:
  Notification(std::string type, std::string time, std::string date,
               std::string message, std::string receiver);

/**
* \return std::string The type of notification.
*/
  std::string getType();
/**
* \return std::string The time the notification was sent or scheduled.
*/
  std::string getTime();
 /**
* \return std::string The date the notification was sent or scheduled.
*/
  std::string getDate();
/**
* \return std::string The message content.
*/
  std::string getMessage();
/**
* \return std::string The receiver's identifier (user ID).
*/
  std::string getReceiver();
};

#endif  // NOTIFICATION_H
