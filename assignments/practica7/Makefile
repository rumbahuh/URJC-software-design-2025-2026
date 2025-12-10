CC = g++
CFLAGS = -Wall -Wvla -g -Iinclude
LIBS = -lsqlite3

MAIN_SOURCES = main.cpp \
               src/Admin.cpp src/Agenda.cpp src/Appointment.cpp \
               src/AppointmentSystem.cpp src/Doctor.cpp src/Notification.cpp \
               src/Pacient.cpp src/Robot.cpp src/Room.cpp src/Ticket.cpp src/User.cpp

MAIN_OBJECTS = $(patsubst %.cpp, build/%.o, $(MAIN_SOURCES))

UTILS = createTableUsers

all: main $(UTILS)

main: $(MAIN_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJECTS) $(LIBS)

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(UTILS): %: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -rf build main $(UTILS)
