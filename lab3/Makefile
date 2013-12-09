PROJECT = vjezba3
SOURCES = main.cpp
HEADERS = 

CC = g++
CFLAGS = -Wall -g
LDFLAGS =
OBJECTS = ${SOURCES:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(PROJECT)

$(OBJECTS): $(HEADERS)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
