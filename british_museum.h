#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include <math.h>
#include "colors.h"
#include "limits.h"



#ifndef _BM
#define _BM
int* lireCertif(char *path);
int* recupereCertificat();
int verifCertificat(int * certif, int * objets);
int* randomCertificat();
void printCretif(int * certificat);
int exhaustive(int * objets);
int partition(int * objets);
int sum(int * objets);

#endif
