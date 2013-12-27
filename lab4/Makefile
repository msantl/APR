PROJECT = vjezba4
SOURCE = main.cpp Matrica.cpp
HEADERS = Matrica.hpp

CC = g++
CFLAGS = -Wall -g 
OBJECTS = ${SOURCE:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT)

$(OBJECTS): $(HEADERS)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
