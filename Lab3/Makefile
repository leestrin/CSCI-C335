# Simon Lee (sijlee) / Brandon Burzon (brburzon
# Makefile

CC = gcc
CFLAGS = -g
LDFLAGS =
#we are going to compile with thse objects
poly: poly.o dump.o
	$(CC) $(LDFLAGS) -o poly poly.o dump.o
#poly.o is from poly.c
poly.o: poly.c
	$(CC) $(CFLAGS) -c poly.c
#dump.o is from dump.c
dump.o: dump.c
	$(CC) $(CFLAGS) -c dump.c
