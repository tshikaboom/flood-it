API = API_Gene_instance.c API_Grille.c Liste_case.c Pile_case.c Zones.c
FILES = Flood-It-1.c
FLAGS = -g -l SDL
CC = gcc

all: Flood

Flood: $(FILES) $(API:c=o)
	$(CC) $(FLAGS)  -o $@ $^

*.o: *.c *.h
	$(CC)  $(FLAGS) -c $<


clean: 
	rm -f Flood *.o 

.PHONY: all clean
