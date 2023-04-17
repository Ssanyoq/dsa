CC = gcc
CFLAGS = -l readline
DEBUGFLAGS = -g
SOURCES = main.c menu.c 
INTERFACE = interface.c
EXENAME = e
EXEDIR = build

default:
	$(CC) $(SOURCES) $(INTERFACE) $(CFLAGS) -o $(EXEDIR)/$(EXENAME)

hex:
	$(CC) hexreader.c $(CFLAGS) -o $(EXEDIR)/hex

lib:
	gcc $(INTERFACE) -c -o build/int.o
	ar -rc build/libmap.a build/int.o

with_lib:
	$(CC) $(SOURCES) -lmap -Lbuild/ $(CFLAGS) -o $(EXEDIR)/$(EXENAME)