SRC=Zones.c API_Grille.c strategie_coloriage.c Pile_case.c API_Gene_instance.c Liste_case.c Flood-It-1.c 
CFLAGS=-g -Wall
LDFLAGS=-lSDL
CC=gcc

all: Flood

Flood: $(SRC:.c=.o)
	$(CC) $(CFLAGS)  -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS)

clean: 
	rm -f Flood *.o 

.PHONY: all clean

API_Gene_instance.o: API_Gene_instance.c API_Gene_instance.h
API_Grille.o: API_Grille.c API_Grille.h
Backup.Flood-It-1.o: Backup.Flood-It-1.c Flood-It-1.h API_Grille.h \
 API_Gene_instance.h Pile_case.h Liste_case.h Zones.h
Flood-It-1.o: Flood-It-1.c strategie_coloriage.h Flood-It-1.h \
 API_Grille.h API_Gene_instance.h Pile_case.h Liste_case.h Zones.h
Liste_case.o: Liste_case.c Liste_case.h
main.o: main.c Pile_case.h
Pile_case.o: Pile_case.c Pile_case.h
strategie-coloriage.o: strategie-coloriage.c strategie_coloriage.h \
 Flood-It-1.h API_Grille.h API_Gene_instance.h Pile_case.h Liste_case.h \
 Zones.h
Zones.o: Zones.c Liste_case.h Zones.h Pile_case.h
