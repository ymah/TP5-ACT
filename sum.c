#include "sum.h"

int sumHeuristique1(int *objet, int s) {
  int i, resTmp = s;

  for(i = 0; i < nobjet; i++) {
    /* on verifie que on a encore de la place dans le sac pour placer l'objet courant */
    if((resTmp - objet[i]) >= 0)
      resTmp -= objet[i];      
  }
      
  if(resTmp == 0)
    return 1;
  else
    return 0;

}

int sumHeuristique1Bis(int *objet, int s) {
  int i = 0;
  int resTmp = 0;
  for(i = 0; i < nobjet; i++) {
    if(resTmp == s)
      return 1;
    else {
      resTmp += objet[i];
    }
  }
  return 0;
}



int checkDigit(char * digit) {
  int i = 0;
  while(digit[i] != '\0') {
    if(!isdigit(digit[i]))
       return 0;
    i++;
  }
    return 1;
}
