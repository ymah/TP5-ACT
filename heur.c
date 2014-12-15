#include <stdio.h>
#include <stdlib.h>
#include "heur.h"
#include "colors.h"

void heuristiqueNonTrie(){
  int i;
  sac = calloc(nobjet,sizeof(int));
  res = calloc(nobjet,sizeof(int));
  getData();

  courant = 0;

  printf("\n----------------------\n");
  for(i=0;i<nobjet;i++)
    if(objet[i] > cap){
      printf("les objets sont trop gros pour les sacs");
      return ;
    }
  heuristique1(objet,nobjet,sac,cap);
  printf(BOLDWHITE "Heuristique 1" RESET "- Capacité de chaque sac %d\n",cap);
  for(i=0;i<nobjet;i++){
    printf("le %d eme de poids %d dans le sac %d\n",i+1,objet[i],res[i]+1);
  }
  printf("\n----------------------\n");

  heuristique2(objet,nobjet,sac,cap);
  printf(BOLDWHITE "Heuristique 2- " RESET "Capacité de chaque sac %d\n",cap);
  for(i=0;i<nobjet;i++){
    printf("le %d eme de poids %d dans le sac %d\n",i+1,objet[i],res[i]+1);
  }
  printf("\n----------------------\n");

  heuristique3(objet,nobjet,sac,cap);
  printf(BOLDWHITE "Heuristique 3- " RESET "Capacité de chaque sac %d\n",cap);
  for(i=0;i<nobjet;i++){
    printf("le %d eme de poids %d dans le sac %d\n",i+1,objet[i],res[i]+1);
  }
}




/* à chaque objet, on le met dans le sac courant si il y a assez de place. Sinon , on crée un nouveau sac courant et on y met l’objet */
int heuristique1(int *objet,int o_size,int *lsac,int cap_s){
  int i;
  /* on remplit tout les sacs avec leur capacité  */
  for(i=0;i<o_size;i++){
    lsac[i] = cap_s;
  }
  /* pour chaque objets : si on peut le mettre dans le sac courant, on le fait et on s'occupe du prochain objet */
  for(i=0;i<o_size;i++){
    if((lsac[courant] - objet[i]) >= 0){
      lsac[courant] -= objet[i];
      res[i] = courant;
    }
    /* sinon on créé un nouveau sac et on met l'objet dans ce nouveau sac */
    else{
      courant++;
      lsac[courant]= cap_s - objet[i];
      res[i] = courant;
    }
  }
  return 0;
}


/* Pour chaque objet, on regarde si il rentre dans un des sacs créés: si oui, on le met dans le premier qui convient; sinon, on créee un nouveau sac et on y met l’objet; */
int heuristique2(int *objet,int o_size,int *lsac,int cap_s){
  int ok,i,j,cptSac;
  /* on remplit tout les sacs avec leur capacité  */
  for(i=0;i<o_size;i++){
    lsac[i]=cap_s;
  }
  ok = 0;
  cptSac= 1; /* permet de savoir combien de sacs nous avons déjà créé */
  for(i=0;i<o_size;i++){
    /* pour chaque objets: on vérifir que le nombre de sacs n'est pas superieur au nbr d'objets (normalement, notre algorithme fait en sorte que cela ne doti jamais arriver) */
    if(cptSac > o_size)
      exit(EXIT_FAILURE);
    /* on va parcourir tous les sacs déjà créé. Si un des objets rentre dans ce sac, on le met et on s'occupe du prochain objet */
    for(j=0;j<cptSac;j++){
      if((lsac[j] - objet[i]) >= 0){
        lsac[j] -= objet[i];
        res[i] =  j;
        ok = 1;
        break;
      }
    }
    /* si on a parcourus tous les sacs et que l'on a pas réussi à y ranger l'objet, on créé un nouveau sac et on y range l'objet courant */
    if(!ok){
      ok=0;
      j++;
      lsac[j]= cap_s - objet[i];
      res[i] = j;
      cptSac++;
    }
  }

  return 0;
}

/* Pour chaque objet, on regarde si il rentre dans un des sacs créés: si oui, on le met dans le celui qui est le plus rempli parmi ceux qui conviennent. Sinon, on crée un nouveau sac et on y met l’objet. */



int heuristique3(int *objet,int o_size,int *lsac,int cap_s){
  int i,j,ok,fort,cptSac;
  for(i=0;i<o_size;i++){
    lsac[i]=cap_s;
  }
  ok=fort=0;
  cptSac = 0;
  for(i=0;i<o_size;i++){
    ok=fort=0;
    for(j=0;j<=cptSac;j++)
      if(lsac[fort] < lsac[j] && lsac[j] - objet[i] >= 0 )
          fort =j;
    if((lsac[fort] - objet[i]) >= 0 ){
      lsac[fort] -= objet[i];
      ok=1;
      res[i] = fort;
    }
    if(!ok){
      cptSac++;
      lsac[cptSac] -= objet[i];
      res[i] = cptSac;
      ok = 1;
    }
  }

  return 0;
}



void getData(){
  char c;
  int i;
  i=0;
  if((c=getchar()) == EOF)
    exit(EXIT_FAILURE);
  nobjet =c -'0';
  if((c=getchar()) != 10){
    nobjet *= 10;
    nobjet+= c - '0';
  }
  printf("\nNombre d'objets : %d\n",nobjet);
  objet = calloc(nobjet,sizeof(int));
  while(i!=nobjet){
    if((c=getchar()) == EOF)
      exit(EXIT_FAILURE);
    if(c==10 || c==32)
      continue;
    objet[i]= c - '0';
    printf("%d ",objet[i]);
    i++;
  }
  printf("\n");
  getchar();
  getchar();
  getchar();
  cap = getchar() - '0';
}
