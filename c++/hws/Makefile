CC = g++
CFLAGS =
LIBS = -lm

circle: Circle.o main.C
	$(CC) $(CFLAGS) -o circle Circle.o main.C $(LIBS)

Circle.o: Circle.H Circle.C
	$(CC) $(CFLAGS) -c Circle.C
