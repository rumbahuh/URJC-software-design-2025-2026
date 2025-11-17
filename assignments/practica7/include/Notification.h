/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Notification class represents a single message
  object which contains details such as type, time, date, content and id.
*/

#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <iostream>

class User;

class Notification {
 public:
  Notification(std::string type, std::string time, std::string date,
               std::string message, std::string receiver);

  // Returns the type of notification
  std::string getType();
  // Returns the time the notification was sent or scheduled
  std::string getTime();
  // Returns the date the notification was sent or scheduled
  std::string getDate();
  // Returns the message content
  std::string getMessage();
  // Returns the receiver's identifier (user id)
  std::string getReceiver();

 private:
  std::string type;
  std::string time;
  std::string date;
  std::string message;
  std::string receiver;
};

#endif  // NOTIFICATION_H
