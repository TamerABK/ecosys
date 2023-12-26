#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 200
#define NB_PREDATEURS 50
#define T_WAIT 40000


/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
/*float PCHDIR=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;*/


int main(void) {
 
  
srand(2);
FILE *f=fopen("data.txt","w");
if (!f){printf("Erreur ouverture %s \n","data.txt"); return 1; }
  
  int monde[SIZE_X][SIZE_Y];

  int i,j;

for (i=0;i<SIZE_X;i++){
  for(j=0;j<SIZE_Y;j++){
    monde[i][j]=0;
  }
}

  Animal *a1 = creer_animal(15,35, 10);
  Animal *a2=  creer_animal(10,6, 10);
  a1->dir[0]=1;
  a1->dir[1]=0;
  a2->dir[0]=0;
  a2->dir[1]=1;
  Animal* liste_proie=a1;
  Animal* liste_predateur=a2;

  for ( i=0; i<NB_PROIES-1;i++){
        ajouter_animal((rand() % (SIZE_X)),(rand() % (SIZE_Y)),50,&liste_proie);
  }
   for ( i=0; i<NB_PREDATEURS-1;i++){
        ajouter_animal((rand() % (SIZE_X)),(rand() % (SIZE_Y)),85,&liste_predateur);
  }

  
  for (i=0;i<100;i++){
    rafraichir_proies(&liste_proie,monde);
    rafraichir_predateurs(&liste_predateur,&liste_proie);
    rafraichir_monde(monde);
    afficher_ecosys(liste_proie,liste_predateur);
    fprintf(f,"%d %d %d\n",i+1,compte_animal_it(liste_proie),compte_animal_it(liste_predateur));
    //usleep(2000000);
  }
  
  fclose(f);

  liberer_liste_animaux(liste_predateur);
  liberer_liste_animaux(liste_proie);
  
  return 0;
}



