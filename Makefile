CC=gcc
CFLAGS=-I.
DEPS = Food.h GamePiece.h SnakeGame.h Snake.h SnakeSection.h
OBJ = main.o Food.o GamePiece.o SnakeGame.o Snake.o SnakeSection.o
LIBS=-lsfml-graphics

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

Snake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
clean:
	rm -f *.o *~ Snake
