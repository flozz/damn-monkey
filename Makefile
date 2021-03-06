#Compiler
CC = gcc

#Compiler flags
CFLAGS = -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT

#Linker flags
LDFLAGS = -L/usr/lib/x86_64-linux-gnu/ -lSDL -lSDL_image -lSDL_mixer

#Executable name
EXEC = damn-monkey


$(EXEC): main.o main_menu.o main_functions.o menu.o credits.o refresh.o parser.o sprite.o game.o level_01.o pause_menu.o
	$(CC) -o bin/$(EXEC) obj/main.o obj/main_menu.o obj/main_functions.o obj/menu.o obj/credits.o obj/refresh.o obj/parser.o obj/sprite.o obj/game.o obj/level_01.o obj/pause_menu.o $(LDFLAGS)

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

parser.o: src/parser.c
	$(CC) $(CFLAGS) -o obj/parser.o -c src/parser.c

sprite.o: src/sprite.c
	$(CC) $(CFLAGS) -o obj/sprite.o -c src/sprite.c

game.o: src/game.c
	$(CC) $(CFLAGS) -o obj/game.o -c src/game.c

level_01.o: src/levels/level_01.c
	$(CC) $(CFLAGS) -o obj/level_01.o -c src/levels/level_01.c

pause_menu.o: src/pause_menu.c
	$(CC) $(CFLAGS) -o obj/pause_menu.o -c src/pause_menu.c


clean:
	rm -f obj/*
	rm -f bin/*

all: clean $(EXEC)


