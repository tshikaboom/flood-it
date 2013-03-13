API = API_Gene_instance.c API_Grille.c Liste_case.c Pile_case.c Zones.c
FILES = Flood-It-1.c
CFLAGS=-g
LDFLAGS =-lSDL
CC = gcc

all: Flood

Flood: $(FILES) $(API:c=o)
	$(CC) $(CFLAGS)  -o $@ $^ $(LDFLAGS)

*.o: *.c *.h
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)


clean: 
	rm -f Flood *.o 

.PHONY: all clean
