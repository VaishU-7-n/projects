# Makefile for C-Unplugged

CC = gcc
CFLAGS = -Wall -Wextra
OBJS = main.o song.o album.o playlist.o logger.o

all: c_unplugged

c_unplugged: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o c_unplugged

main.o: main.c song.h album.h playlist.h logger.h
	$(CC) $(CFLAGS) -c main.c

song.o: song.c song.h
	$(CC) $(CFLAGS) -c song.c

album.o: album.c album.h song.h
	$(CC) $(CFLAGS) -c album.c

playlist.o: playlist.c playlist.h song.h
	$(CC) $(CFLAGS) -c playlist.c

logger.o: logger.c logger.h
	$(CC) $(CFLAGS) -c logger.c

clean:
	rm -f *.o c_unplugged
