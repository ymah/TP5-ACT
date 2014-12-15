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
      printf(RED "Le programme avec l'attribut -sum prend 2 paramètres : l'attribut " BOLDRED "-sum et un entier cible." RESET RED " Veuillez entrer les bon paramètres\n" RESET);
      return 0;
    }
  }
  else if (argc == 2) {
    if(strcmp(argv[1], "-trie") == 0) {
      heuristiqueTrie();
    }
    else if(strcmp(argv[1], "-nonTrie") == 0) {
      heuristiqueNonTrie();
    }
    else {
      printf("argc = %d\n", argc);

      printf(RED "Le programe prend soit 1 argument : " BOLDRED "-nonTrie " RESET RED" (pour le mode online), "BOLDRED" -trie " RESET RED "(pour le mode offline) soit 2 arguments : " BOLDRED "-sum " RESET RED " et un " BOLDRED " entier cible" RESET RED" pour la somme.\nRappel : il faut aussi rediriger l'entrée standard pour scanner les fichier (ex : < < donnees/data_BinPack/exemple1.\n "RESET);
      exit(EXIT_FAILURE);
    }
  }
  else  {
    printf(RED "Le programe prend 1 argument : -nonTrie (pour le mode online), -trie (pour le mode offline) et -sum pour la somme\n"RESET);
    exit(EXIT_FAILURE);
  }

  printf("\nPartition \n");

  return 0;
}
