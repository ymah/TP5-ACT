#include <stdio.h>
#include <stdlib.h>
#include "heur.h"
#include "heurTri.h"



void heuristiqueTrie(){
  int i;
  sac = calloc(nobjet,sizeof(int));
  res = calloc(nobjet,sizeof(int));

  getData();
  triData();
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




void triData(){
  quickSort(objet,0,nobjet);
  printf("\n\nLes données ont été triée\n");

}


void quickSort( int a[], int l, int r)
{
  int j;

  if( l < r )
    {
      j = partition( a, l, r);
      quickSort( a, l, j-1);
      quickSort( a, j+1, r);
    }

}



int partition( int a[], int l, int r) {
  int pivot, i, j, t;
  pivot = a[l];
  i = l; j = r+1;

  while( 1)
    {
      do ++i; while( a[i] <= pivot && i <= r );
      do --j; while( a[j] > pivot );
      if( i >= j ) break;
      t = a[i]; a[i] = a[j]; a[j] = t;
    }
  t = a[l]; a[l] = a[j]; a[j] = t;
  return j;
}
