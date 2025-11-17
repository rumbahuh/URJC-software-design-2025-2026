/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  The Notification class represents a single message
  object which contains details such as type, time, date, content and id.
*/

#include "Notification.h"

Notification::Notification(std::string type, std::string time, std::string date,
                           std::string message, std::string receiver)
    : type(type),
      time(time),
      date(date),
      message(message),
      receiver(receiver) {}

std::string Notification::getType() { return ""; }

std::string Notification::getTime() { return ""; }

std::string Notification::getDate() { return ""; }

std::string Notification::getMessage() { return ""; }

std::string Notification::getReceiver() { return ""; }
