CC = g++
CFLAGS = -Wall -Wvla -g -Iinclude
LIBS = -lsqlite3

SOURCES = main.cpp src/Admin.cpp src/Agenda.cpp src/Appointment.cpp \
          src/AppointmentSystem.cpp src/Doctor.cpp src/Notification.cpp \
          src/Pacient.cpp src/Robot.cpp src/Room.cpp src/Ticket.cpp src/User.cpp

HEADERS = include/Admin.h include/Agenda.h include/Appointment.h \
          include/AppointmentSystem.h include/Doctor.h include/Notification.h \
          include/Pacient.h include/Robot.h include/Room.h include/Ticket.h include/User.h

OBJECTS = $(patsubst %.cpp, build/%.o, $(SOURCES))

TARGETS = main createTables

all: $(TARGETS)

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) $(LIBS)

# Pattern rule for building all objects
build/%.o: %.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# createTables target, matching the style of the second Makefile
createTables: src/createTableUsers.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -rf build $(TARGETS)
	