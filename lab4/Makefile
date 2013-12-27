PROJECT = vjezba4
SOURCE = main.cpp Matrica.cpp Trapezni.cpp RungeKutta4.cpp
HEADERS = Matrica.hpp Trapezni.hpp RungeKutta4.hpp

CC = g++
CFLAGS = -Wall -g 
OBJECTS = ${SOURCE:.cpp=.o}

$(PROJECT): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(PROJECT)

$(OBJECTS): $(HEADERS)

clean:
	-rm -f $(PROJECT) $(OBJECTS) *.core
