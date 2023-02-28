CC = gcc
CFLAGS = -l readline
DEBUGFLAGS = -g
SOURCES = main.c
LISTSOURCES = list_queue.c
VECTORSOURCES = vector_queue.c
EXENAME = e
EXEDIR = build

l:
	$(CC) $(SOURCES) $(LISTSOURCES) $(CFLAGS) -o $(EXEDIR)/$(EXENAME) -D LIST

v:
	$(CC) $(SOURCES) $(VECTORSOURCES) $(CFLAGS) -o $(EXEDIR)/$(EXENAME) -D VECTOR