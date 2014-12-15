CC	= gcc
CFLAGS	= -Wall
CFLAGS += -ansi
CFLAGS += -pedantic
CFLAGS  += -g
#MATH = -lm
###------------------------------
### Main targets
###------------------------------------------------------------
BINARIES= heuristique
OBJECTS	= $(addsuffix .o,\
	  heur heurTri partition sum)

all: $(BINARIES) $(OBJECTS)

###------------------------------
### Binaries
###------------------------------------------------------------
heuristique: heuristique.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(MATH)

###------------------------------
### #include dependences
###------------------------------------------------------------
# you may fill these lines with "make depend"

heur.o: heur.h heur.c colors.h
heurTri.o:  heurTri.c heur.h heurTri.h colors.h
heuristique.o: heuristique.c heurTri.h heur.h partition.h sum.h colors.h
partition.o: partition.c heurTri.h heur.h partition.h
sum.o: sum.c sum.h partition.h colors.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *#* *.o $(BINARIES)
realclean: clean
	$(RM)
depend :
	$(CC) -MM $(INCDIR) *.c

