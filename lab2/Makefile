PROJECT = vjezba2
SOURCES = HookeJeeves.cpp BoxMethod.cpp Function.cpp main.cpp
HEADERS = HookeJeeves.hpp BoxMethod.hpp Function.hpp Vektor.hpp

CC = g++
CFLAGS = -Wall -g
LDFLAGS =
OBJECTS = ${SOURCES:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROJECT)

$(OBJECTS): $(HEADERS)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
