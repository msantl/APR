PROJECT = vjezba3
SOURCES = main.cpp Jedinka.cpp Funkcija.cpp GenetskiAlgoritam.cpp
HEADERS = Jedinka.hpp Funkcija.hpp GenetskiAlgoritam.hpp

CC = g++
CFLAGS = -Wall -g
LDFLAGS =
OBJECTS = ${SOURCES:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROJECT)

$(OBJECTS): $(HEADERS)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
