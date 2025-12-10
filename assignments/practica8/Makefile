CC = g++
CFLAGS = -Wall -Wvla -g -Iinclude
LIBS = -lsqlite3

MAIN_SOURCES = main.cpp \
               src/users/Admin.cpp \
               src/appointments/Agenda.cpp \
               src/appointments/Appointment.cpp \
               src/system/AppointmentSystem.cpp \
               src/users/Doctor.cpp \
               src/appointments/Notification.cpp \
               src/users/Pacient.cpp \
               src/robot/Robot.cpp \
               src/appointments/Room.cpp \
               src/appointments/Ticket.cpp \
               src/users/User.cpp


MAIN_OBJECTS = $(patsubst %.cpp, build/%.o, $(MAIN_SOURCES))

all: main

main: $(MAIN_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJECTS) $(LIBS)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(UTILS): %: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -rf build main
