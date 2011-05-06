#Compiler
CC = gcc

#Compiler flags
CFLAGS = -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT

#Linker flags
LDFLAGS = -L/usr/lib -lSDL -lSDL_image -lSDL_mixer

#Executable name
EXEC = damn-monkey


$(EXEC): main.o main_menu.o main_functions.o menu.o credits.o refresh.o pause_menu.o
	$(CC) -o bin/$(EXEC) $(LDFLAGS) obj/main.o obj/main_menu.o obj/main_functions.o obj/menu.o obj/credits.o obj/refresh.o obj/pause_menu.o

main.o: src/main.c
	$(CC) $(CFLAGS) -o obj/main.o -c src/main.c

main_menu.o: src/main_menu.c
	$(CC) $(CFLAGS) -o obj/main_menu.o -c src/main_menu.c

main_functions.o: src/main_functions.c
	$(CC) $(CFLAGS) -o obj/main_functions.o -c src/main_functions.c

menu.o: src/menu.c
	$(CC) $(CFLAGS) -o obj/menu.o -c src/menu.c

credits.o: src/credits.c
	$(CC) $(CFLAGS) -o obj/credits.o -c src/credits.c

refresh.o: src/refresh.c
	$(CC) $(CFLAGS) -o obj/refresh.o -c src/refresh.c

pause_menu.o: src/pause_menu.c
	$(CC) $(CFLAGS) -o obj/pause_menu.o -c src/pause_menu.c

clean:
	rm -f obj/*
	rm -f bin/*

all: clean $(EXEC)


