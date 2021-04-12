CC = g++
CFLAGS = -Wno-deprecated-declarations -Wdeprecated-declarations
DEPS = 
LDFLAGS = -framework GLUT -framework OpenGL -framework Carbon

.default: all

asteroids: main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o asteroids main.o

main.o: main.cpp
	$(CC) $(CFLAGS) $(LDFLAGS) -c main.cpp

%.o: %.h

clean:
	rm -rf asteroids *.o