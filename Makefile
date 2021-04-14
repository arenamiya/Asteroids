CC = g++
CFLAGS = -Wno-deprecated-declarations -Wdeprecated-declarations
DEPS = 
LDFLAGS = -framework GLUT -framework OpenGL -framework Carbon

.default: all

game: main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o game main.o

clean:
	rm -rf game *.o