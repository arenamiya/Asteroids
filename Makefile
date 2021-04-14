CC = g++
CFLAGS = -Wno-deprecated-declarations -Wdeprecated-declarations
DEPS = 
LDFLAGS = -framework GLUT -framework OpenGL -framework Carbon

.default: all

game: main.o ship.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o game main.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

%.o: %.h

clean:
	rm -rf asteroids *.o