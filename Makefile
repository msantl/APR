PROJECT = naziv_projekta
SOURCES = main.cpp pomocni.cpp
HEADERS = pomocni.hpp

CC = g++
CFLAGS = -Wall -g
LDFLAGS =
OBJECTS = ${SOURCES:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROJECT)

$(OBJECTS): $(HEADERS)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
