#include <stdio.h>
#include <stdlib.h>
#include "heur.h"


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
  printf("Heuristique 1- Capacité de chaque sac %d\n",cap);
  for(i=0;i<nobjet;i++){
    printf("le %d eme de poids %d dans le sac %d\n",i+1,objet[i],res[i]+1);
  }
  printf("\n----------------------\n");

  heuristique2(objet,nobjet,sac,cap);
  printf("Heuristique 2- Capacité de chaque sac %d\n",cap);
  for(i=0;i<nobjet;i++){
    printf("le %d eme de poids %d dans le sac %d\n",i+1,objet[i],res[i]+1);
  }
  printf("\n----------------------\n");

  heuristique3(objet,nobjet,sac,cap);
  printf("Heuristique 3- Capacité de chaque sac %d\n",cap);
  for(i=0;i<nobjet;i++){
    printf("le %d eme de poids %d dans le sac %d\n",i+1,objet[i],res[i]+1);
  }
}





int heuristique1(int *objet,int o_size,int *lsac,int cap_s){
  int i;
  for(i=0;i<o_size;i++){
    lsac[i] = cap_s;
  }
  for(i=0;i<o_size;i++){
    if((lsac[courant] - objet[i]) >= 0){
      lsac[courant] -= objet[i];
      res[i] = courant;
    }else{
      courant++;
      lsac[courant]= cap_s - objet[i];
      res[i] = courant;
    }
  }
  return 0;
}



int heuristique2(int *objet,int o_size,int *lsac,int cap_s){
  int ok,i,j,cptSac;
  for(i=0;i<o_size;i++){
    lsac[i]=cap_s;
  }
  ok = 0;
  cptSac= 1;
  for(i=0;i<o_size;i++){
    if(cptSac > o_size)
      exit(EXIT_FAILURE);
    for(j=0;j<cptSac;j++){
      if((lsac[j] - objet[i]) >= 0){
        lsac[j] -= objet[i];
        res[i] =  j;
        ok = 1;
        break;
      }
    }
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

int heuristique3(int *objet,int o_size,int *lsac,int cap_s){
  int i,j,ok,fort,cptSac;
  for(i=0;i<o_size;i++){
    lsac[i]=cap_s;
  }
  cptSac = 1;
  ok = j=0;
  fort = 0;
  for(i=0;i<o_size;i++){
    if(cptSac > o_size)
      exit(EXIT_FAILURE);
    for(j=0;j<o_size;j++){


      if((lsac[fort] - objet[i]) >= 0){
        if(lsac[j] > lsac[fort]){
          fort =j;
        }
        lsac[fort] -= objet[i];
        res[i] = j;
        ok = 1;
        break;
      }
    }
    if(!ok){
      j++;
      ok=0;
      lsac[j]= cap_s - objet[i];
      res[i] =j ;
      courant = j;
      cptSac++;
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
