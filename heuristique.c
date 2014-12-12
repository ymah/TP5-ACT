#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "heurTri.h"
#include "heur.h"
#include "partition.h"
#include "sum.h"
#include "colors.h"


int
main(int argc, char *argv[]) {

  /* MAH :  j'ai fait ça pour ne pas interférer avec ton code. Et puis c'est plus facile à utiliser pour tester. */  
/* si on a 3 arguments (en gros, que l'on utilise sum) */
  if(argc == 3) {
    /* on verifie que l'argument 1 est -sum et que le deuxième argument est bien un nombre */
    if(strcmp(argv[1], "-sum") == 0 && checkDigit(argv[2]) != 0) {
      getData();

      if(sumHeuristique1(objet, atoi(argv[2]))) {
	printf(GREEN "Le nombre %d peut être calculé en faisant une somme des objets\n" RESET, atoi(argv[2]));
	return 0;
      }
      else {
	printf(RED "Le nombre %d ne peut être calculé en faisant une somme des objets\n" RESET, atoi(argv[2]));
	return 0;
      }
    }
    else {
      printf(RED "Le programme avec l'attribut -sum prend 2 paramètres : " BOLDRED "l'attribut -sum et un entier cible." RESET RED " Veuillez entrer les bon paramètres\n" RESET);
      return 0;
    }
  }

  
  printf("\nPartition \n");  
  heuristiqueNonTrie();

  return 0;
}
