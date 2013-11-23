PROJECT = naziv_projekta
SOURCE = main.cpp pomocni.cpp
HEADERS = pomocni.hpp

CC = g++
CFLAGS = -Wall -g
LDFLAGS =
OBJECTS = ${SOURCE:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROJECT)

$(OBJECTS): $(HEADERS)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
