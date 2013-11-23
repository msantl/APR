PROJECT = vjezba2
SOURCE = HookeJeeves.cpp Box.cpp Vector.cpp Function.cpp main.cpp
HEADERS = HookeJeeves.hpp Box.hpp Vector.hpp Function.hpp

CC = g++
CFLAGS = -Wall -g
LDFLAGS =
OBJECTS = ${SOURCE:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROJECT)

$(OBJECTS): $(HEADERS)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
