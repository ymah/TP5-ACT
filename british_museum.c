#include "british_museum.h"


static int n, k, c = 0; /* nbr objets, nbr sacs, capacite sac */
/* static int cpt = 0; */



int
main(int argc, char *argv[]) {
  /* int i; */
  int * certificat, * objets;
  if(argc != 3) {
    printf("Le prog prend entre 2 et 3 arguments -mode et nom de fichiers (si besoin)\n");
    exit(EXIT_FAILURE);
  }
  objets =lireCertif(argv[2]);
  
  if(strcmp(argv[1], "-v") == 0) {
    certificat =  recupereCertificat(argv[2]);
  }
  else if(strcmp(argv[1], "-nd") == 0) {
    certificat = randomCertificat();    
  }
  else if(strcmp(argv[1], "-exh") == 0) {
    if(exhaustive(objets) == 1) {
      printf(GREEN "un certificat existe.\n" RESET);
      exit(EXIT_SUCCESS);
    }
    else {
      printf(RED "un certificat n'existe pas.\n" RESET);
      exit(EXIT_FAILURE);
    }
  }
  else if(strcmp(argv[1], "-partition") == 0) {
    if(partition(objets) == 1) {
      printf(GREEN "Il existe un sous ensemble tq la somme des x[i] correspondants soit exactement la moitié de la somme des x[i]\n" RESET);
      exit(EXIT_SUCCESS);
    }
    else {
      printf(RED "Il n'existe pas un sous ensemble tq la somme des x[i] correspondants soit exactement la moitié de la somme des x[i]\n" RESET);
      exit(EXIT_FAILURE);
    }
  }  
  else if(strcmp(argv[1], "-sum") == 0) {
    if(sum(objets) == 1) {
      printf(GREEN "il existe un sous-ensemble de [1..n] tel que la somme des x i correspondants soit exactement c\n" RESET);
      exit(EXIT_SUCCESS);
    }
    else {
      printf(RED "Il n'existe pas un sous ensemble tq la somme des x[i] correspondants soit exactement la moitié de la somme des x[i]\n" RESET);
      exit(EXIT_FAILURE);
    }
  }  
  else {
    printf(RED "Vous n'avez pas entré un argument ok.\nLes arguments sont : -v (verif), -nd (non deterministe), -exh (exhaustif)\n" RESET);
    exit(EXIT_FAILURE);
  }

  /* on verifie le certificat */
  if(verifCertificat(certificat, objets) == 1)
    printf(GREEN "Le certificat est valide\n" RESET);
  else
    printf(RED "Le certificat n'est pas valide\n" RESET);

  return 0;
}





int sum(int * objets) {
  int * tmp = calloc(n + 1, sizeof(int));
  int sommeEntier = 0;
  int i;
  /* on doit d'abord overider k et c */
  for(i = 0; i < n; i++) {
    sommeEntier += objets[i];
  }
  for(i = 0; i < n; i++) {
    tmp[i] = objets[i];
  }

  /* on change le nbr d'objets pour pouvoir les utiliser. */
  n += 2;
  
  /* c'est ici que l'initeligence de l'algo fait surface !!! */
 
  tmp[i] = (INT_MAX / 3);
  tmp[i+1] = (INT_MAX / 3) - k + (sommeEntier - k);

  return partition(tmp);
}




int partition(int * objets) {
  int sommeEntier = 0, i = 0;
  /* on doit d'abord overider k et c */
  for(i = 0; i < n; i++) {
    sommeEntier += objets[i];
  }
  k = 2;
  c = sommeEntier/2;
  /* ensuite, il sufiut de tester tous les certificats pour voir si l'un d'entre eux satisfait les contraintes */
  if(exhaustive(objets) != 0) {

    return 1;
  }
  
  return 0;
}




/*  permet de tester tous les certificats possible avec les données fournis en entrés. Si il en existe au moins un qui résout le problème, cette fonciton l'indique à l'utilisateur. */


int exhaustive(int * objets) {
  /* initialisation certificat à 0 */
  int * certificat, i, next = 0;
  certificat = calloc(n, sizeof(int));

  while(verifCertificat(certificat, objets) == 0) {
    /* on verifie que le nombre dans la derniere case est inferieur a k. Si c'est le cas, on l'incremente */
    if(certificat[n - 1] < k - 1) {
      certificat[n - 1] ++;
    }
    else {
      for(i = n - 2; i >= 0; i--) {
        /* si on arrive dans cette fonction, cela veut dire que l'on va incrementer la case en i. Il faut donc réinitialiser celle d'avant pour pouvoir réincréménter le certificat de 1. */

    	/* on parcours le certificat. Si on trouve un objet qui est inferieur à k, cela veut dire que l'on peut encore générer des certificats (on met donc next à 1). */

	certificat[i + 1] = 0; 

    	if(certificat[i] < k - 1) {
    	  certificat[i]++;
    	  next = 1;
    	  break;
    	}
    	/* si on a tout parcouru, cela veut dire qu'i n'y a pas de certificat possible */
    	else {
    	  next = 0;
	}
      }
      /* si on a tout parcourus et que l'on a pas trouvé de certificat valide, on renvoit une erreur */
      if(next == 0)
    	return 0;
    }    
  }
  printf(GREEN "Resultat OK avec le certificat " BOLDWHITE);

  printCretif(certificat);
  printf("donc " RESET);
  return 1;
}


void printCretif(int * certificat) {
  int i;
  for(i = 0; i < n; i++)
    printf("%d ", certificat[i]);
  printf("\n");
}

/* permet de générer un certificat de manière aléatoire */
int* randomCertificat() {
  int i, random;
  int *certif;
  time_t t;
  certif = malloc(n * sizeof(int));
  srand ( (unsigned)time(&t) );
  for(i = 0; i < n; i++) {
    random = rand();
    certif[i] = random % k;
  }
  printf(BOLDWHITE "------ Certificat random ------ \n" RESET); 
  for(i = 0; i < n; i++)
    printf("certif %d\n", certif[i]);
  return certif;
}

/* permets de tester si le certificat est une solution du problème */
int verifCertificat(int * certif, int * objets) {
  int * listeSac, i;
  listeSac = calloc(k, sizeof(int));

  /* on initlaise chaque sac avec la valeur de c */
  for(i = 0; i < k; i++)
    listeSac[i] = c;
  /* on parcours le certificat et on soustrait la valeur de chaque objet dans chaque sacs. */
  /* si un sac a une contenance negative, cela veut dire que l'on a mit trop de poids dans le sac et que le certificat n'est pas valide */
  for(i = 0; i < n; i++) {
    listeSac[certif[i]] -= objets[i];
    if(listeSac[certif[i]] < 0) {
      free(listeSac);
      return 0;
    }
  }
  free(listeSac);

  return 1;
}

/* permets à un utilisateur de rentrer à la main un certificat */
int* recupereCertificat() {
  int * certif, i;
  char * number = malloc(n * sizeof(int));

  i = 0;
  certif = malloc(n * sizeof(int));
  scanf("%s", number);

  /* on recupere le nombre de chiffres pour pouvoir verifier que le nombre entree par l'utilisateur est le même que le nombre de sacs */
  while(number[i] != '\0') {
    if(i > n - 1) {
      printf(RED "Le nbr d'objets entrés est plus important que le nombre objet des données. Veuillez revoir votre certificat.\n" RESET);
      exit(EXIT_FAILURE);
    }
    certif[i] = number[i] - '0';
    i++;
  }

  printCretif(certif);
  return certif;
}

/* permets de construire un certificat à partir des fichiers text fournis */
int* lireCertif(char *path) {
  FILE *input;
  int car, i;
  int *objets = {0};
  input = fopen(path, "r");
  assert(input);


  /* on recupère la variable nous donnant le nombre d'objets */
  while((car = getc(input)) != '\n') {
    n = (n * 10) + (car - '0');
  }
  /* on cree un tableau donnant le poid pour chaque sacs */
  objets = malloc(n * sizeof(int));

  /* on range tous les poid pour chaque sacs */
  i = 0;
  while(i < n) {
    car = getc(input);
    if(car == '\n') {
      i++;
    }
    else {
      objets[i] = (objets[i] * 10 ) + (car - '0');
    }
  }
  
  /* on recupere le nombre de sacs */
  while((car = getc(input)) != '\n') {
    k = (k * 10) + (car - '0');
  }

  /* on recupere la capacite de chaque sac */
  while((car = getc(input)) != '\n') {
    c = (c * 10) + (car - '0');
  }
  
  fclose(input);
  return objets;
} 


/* fonction qui parsait les fichiers texte pour en extraire un certificat */
/* int* recupereCertificat(char *path) { */
/*   FILE *input; */
/*   int car,  index,  valeur, i/\*, tmp *\/; */
/*   int cpt = 0; /\* utilise pour varier entre index et valeur lorsque l'on remplis le certif *\/ */
/*   int *certif = {0}; */
/*   index = valeur = 0; */
/*   certif = malloc(n * sizeof(int)); */
/*   for(i = 0; i < n; i++) */
/*     certif[i] = 0; */
/*   input = fopen(path, "r"); */
/*   assert(input); */
/*   /\* on va jusqu'a l'exemple de certificat *\/ */
/*   while((car = getc(input))) { */
/*     if(car == 'u') */
/*       break; */
/*   } */
/*   /\* on va jusqu'a la permiere ligne du certificat *\/ */
/*   while((car = getc(input))) { */
/*     if(car == '\n') */
/*       break; */
/*   } */

/*   /\* on va remplir le certificat *\/ */
/*   while((car = getc(input)) != EOF) { */
/*     if(car == '\n') { */
/*       cpt = 0; */
/*       index = 0; */
/*       valeur = 0; */
/*     } */
/*     /\* on recupere l'index de l'objet *\/ */
/*     else if(cpt == 0 && car >= '0' && car <= '9') { */
/*       if(cpt == 0) { */
/* 	index = (index * 10) + (car - '0'); */
/*   	while(1) { */
/*   	  car = getc(input); */
/*   	  if(car >= '0' && car <= '9') */
/*   	    index = (index * 10) + (car - '0'); */
/*   	  else */
/*   	    break; */
/*   	} */
/* 	cpt = 1; */
/*       } */
/*     } */
/*     /\* on stoque l'index du sac dans lequel on met l'objet *\/ */
/*     else if (cpt == 1 && car >= '0' && car <= '9'){ */
/*       certif[index] = (certif[index] * 10) + (car - '0'); */
/*     } */
/*   } */


/*   return certif; */
/* } */


