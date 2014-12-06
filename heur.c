#include <stdio.h>
#include <stdlib.h>
#include "heur.h"


void heuristiqueNonTrie(){
  int i;
  sac = calloc(nobjet,sizeof(int));
  res = calloc(nobjet,sizeof(int));
  getData();
  sac[0]=cap;
  courant = 0;
  printf("\n----------------------\n");
  for(i=0;i<nobjet;i++)
    if(objet[i] > cap){
      printf("les objets sont trop gros pour les sacs");
      return ;
    }
  heuristique1(objet,nobjet);
  printf("Heuristique 1- Capacité de chaque sac %d\n",cap);
  for(i=0;i<nobjet;i++){
    printf("le %d eme de poids %d dans le sac %d\n",i+1,objet[i],res[i]+1);
  }
  printf("\n----------------------\n");

  heuristique2(objet,nobjet);
  printf("Heuristique 2- Capacité de chaque sac %d\n",cap);
  for(i=0;i<nobjet;i++){
    printf("le %d eme de poids %d dans le sac %d\n",i+1,objet[i],res[i]+1);
  }
  printf("\n----------------------\n");

  heuristique3(objet,nobjet);
  printf("Heuristique 3- Capacité de chaque sac %d\n",cap);
  for(i=0;i<nobjet;i++){
    printf("le %d eme de poids %d dans le sac %d\n",i+1,objet[i],res[i]+1);
  }
}


int heuristique1(int *objet,int o_size){
  int i;
  for(i=0;i<o_size;i++){
    if((sac[courant] - objet[i]) >= 0){
      sac[courant] -= objet[i];
      res[i] = courant;
    }else{
      courant++;
      sac[courant]= cap - objet[i];
      res[i] = courant;
    }
  }
  return 0;
}



int heuristique2(int *objet,int o_size){
  int ok,i,j;
  for(i=0;i<o_size;i++){
    sac[i]=cap;
  }
  for(i=0;i<o_size;i++){
    for(j=0;j<o_size;j++){
      if((sac[j] - objet[i]) >= 0){
        sac[j] -= objet[i];
        res[i] =  j;
        ok = 1;
        break;
      }
    }
    if(!ok){
      j++;
      sac[j]= cap - objet[i];
      res[i] = j;
      courant = j+1;
    }

  }

  return 0;
}

int heuristique3(int *objet,int o_size){
  int i,j,ok,fort;
  for(i=0;i<o_size;i++){
    sac[i]=cap;
  }
  fort = 0;
  for(i=0;i<o_size;i++){
    for(j=0;j<o_size;j++){
      if(sac[j] > sac[fort]){
        fort =j;
      }
      if((sac[fort] - objet[i]) >=0){
          sac[fort] -= objet[i];
          res[i] = j;
          ok = 1;
          break;
      }
    }
    if(!ok){
      j++;
      sac[j]= cap - objet[i];
      res[i] =j ;
      courant = j+1;
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
  getchar();
  getchar();
  getchar();
  cap = getchar() - '0';
}
