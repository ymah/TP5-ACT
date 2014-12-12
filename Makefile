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
#OBJECTS	= $(addsuffix .o,\
	  drive mbr vol)

all: $(BINARIES) #$(OBJECTS)

###------------------------------
### Binaries
###------------------------------------------------------------
# british_museum: british_museum.o
# 	$(CC) $(CFLAGS) -o $@ $^ $(MATH)
heuristique:sum.o partition.o heur.o heurTri.o heuristique.o
	$(CC) $(CFLAGS) -o $@ $^ $(MATH)
# %:%.o
# 	$(CC) $(CFLAGS) -o $@ $< $(MATH)
###------------------------------
### #include dependences
###------------------------------------------------------------
# you may fill these lines with "make depend"
# british_museum.o: british_museum.c british_museum.h

heur.o: heur.h heur.c
heurTri.o:  heur.h heurTri.h heurTri.c
heuristique.o: heurTri.h heur.h heuristique.c
partition.o: heurTri.h heur.h partition.h
sum.o: heurTri.h heur.h sum.h

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

