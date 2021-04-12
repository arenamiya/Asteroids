CC = g++
CFLAGS = -Wno-deprecated-declarations -Wdeprecated-declarations
DEPS = 
LDFLAGS = -framework GLUT -framework OpenGL -framework Carbon

.default: all

asteroids: main.o ship.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o asteroids main.o ship.o

main.o: main.cpp ship.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c main.cpp

%.o: %.h

clean:
	rm -rf asteroids *.o