CC = gcc
CFLAGS = -l readline
DEBUGFLAGS = -g
SOURCES = main.c #menu.c
LIBSOURCES = interface.c
EXENAME = e
EXEDIR = build

default:
	$(CC) $(SOURCES) -g $(LIBSOURCES) $(CFLAGS) -o $(EXEDIR)/$(EXENAME)

lib:
	gcc $(LIBSOURCES) -c -o build/int.o
	ar -rc build/libmap.a build/int.o

with_lib:
	$(CC) $(SOURCES) -lmap -Lbuild/ $(CFLAGS) -o $(EXEDIR)/$(EXENAME)

t:
	$(CC) $(LIBSOURCES) test.c $(CFLAGS) -o $(EXEDIR)/t
