/*
Authoress: Rebeca Castilla
Date: 17-27/11/2025
Objective:
  Diseñar e implementar un sistema de Login y Gestión de
  Usuarios utilizando la librería SQLite3 en un proyecto de C++.
*/

#include <vector>
#include <thread> //biblioteca que permite trabajar con hilos de C++
#include <chrono>
#include <iostream>

#include "AppointmentSystem.h"

int main() {
  AppointmentSystem foundationTest = AppointmentSystem();

  User userTest = User(1, "jason", "rh@gmail.com", "1234");
  Admin adminTest = Admin(2, "tim", "rdbin@gmail.com", "-Uw.#Hlñ12");
  Agenda agendaTest = Agenda();
  Appointment appointmentTest = Appointment();
  Notification notificationTest = Notification(
      "type_1", "11:30", "27-10-2025", "Appointment programmed", "doctor_1");
  Doctor doctorTest = Doctor(0, "alfred", "ab@gmail.com", "bruce");
  Room roomTest = Room();
  Ticket ticketTest = Ticket("11:30", "2", "doctor_1", "jason");
  Pacient pacientTest = Pacient(3, "brown", "btg@gmail.com", "hjda");

  //---------------------------------------
  //  Robot class main
  
  // Creamos 3 robots para las pruebas
  std::unique_ptr<Robot> r1 = std::make_unique<Robot>(1);
  std::unique_ptr<Robot> r2 = std::make_unique<Robot>(2);
  std::unique_ptr<Robot> r3 = std::make_unique<Robot>(3);
  
  //Simulo tareas recurrentes invocando al método dummy para cada robot
  r1->dummy(20); //asigno 4 segudnos
  r2->dummy(2); //2 segs.
  r3->dummy(3); //3segs
  
  //Esperar a que todos terminen sus actividades
  std::this_thread::sleep_for(std::chrono::seconds(6));

  // Para trabajar con los robots deben estar almacenados en el sistema
  foundationTest.addRobot(std::move(r1));
  foundationTest.addRobot(std::move(r2));
  foundationTest.addRobot(std::move(r3));

  // Enseñamos los estados y los tiempos reales de cada robot
  foundationTest.getAllRobotStatesTime();

  // Intentamos acceder a un puntero del siguiente robot con estado libre
  Robot *next = foundationTest.getNextAvailableRobot();
  if (next) {
    std::cout << "\nAsignando Robot " << next->getId()
              << " al nuevo acompañamiento.\n";
    next->dummy(30);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  } else {
    std::cout << "\nNo hay robots libres disponibles en este momento.\n";
  }

  // Esperamos para simular el paso del tiempo
  std::this_thread::sleep_for(std::chrono::seconds(6));

  // Mostramos los estados finales tras la nueva asignación
  // y observamos que el nuevo robot está ocupado ocupado
  foundationTest.getAllRobotStatesTime();
  // --------------------------------------
  foundationTest.addPacient(pacientTest);

  userTest.getPerson();

  adminTest.assignSpecialty();

  agendaTest.setTimeL(22);

  appointmentTest.setState("confirmed");

  doctorTest.markAssistance(true);

  roomTest.setDoctor("doctor_2");

  ticketTest.printTicket();

  pacientTest.checkTimeSlots();

  return 0;
}
