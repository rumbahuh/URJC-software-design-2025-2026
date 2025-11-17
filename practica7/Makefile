CC = g++
CFLAGS = -Wall -Wvla -g -Iinclude
LDFLAGS = -lsqlite3

SOURCES = main.cpp src/Admin.cpp src/Agenda.cpp src/Appointment.cpp \
          src/AppointmentSystem.cpp src/Doctor.cpp src/Notification.cpp \
          src/Pacient.cpp src/Robot.cpp src/Room.cpp src/Ticket.cpp src/User.cpp
HEADERS = include/Admin.h include/Agenda.h include/Appointment.h \
          include/AppointmentSystem.h include/Doctor.h include/Notification.h \
          include/Pacient.h include/Robot.h include/Room.h include/Ticket.h include/User.h

OBJECTS = $(patsubst src/%.cpp, build/%.o, $(SOURCES))

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS) $(LDFLAGS)

build/%.o: src/%.cpp $(HEADERS)
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build main