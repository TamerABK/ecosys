#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"

float PCHDIR=0.01;
float p_reproduce_proie=0.5;
float p_reproduce_predateur=0.35;
int temps_repousse_herbe=-5;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert(liste_animal);
  assert((x<SIZE_X)&&(y<SIZE_Y));
  Animal* new_animal= creer_animal(x,y,energie);
  *liste_animal= ajouter_en_tete_animal(*liste_animal, new_animal);
  
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  assert(liste);
  assert(animal);

  if (*liste==animal){
    Animal *res= animal->suivant;
    free(animal);
    *liste=res;
  }else{
    Animal* prev;
    Animal* tmp_liste= *liste;
    while(tmp_liste){
      if (tmp_liste==animal){
        prev->suivant=tmp_liste->suivant;
        free(tmp_liste);
        break;
      }
      prev=tmp_liste;
      tmp_liste=tmp_liste->suivant;
    }
  }

  return ;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
   Animal* tmp;
   while(liste){
      tmp=liste->suivant;
      free(liste);
      liste=tmp;
   }

  return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_X; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_X; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
    while (la){
      if ((float)rand()/RAND_MAX<PCHDIR){
        la->dir[0]=(rand()%3)-1;
        la->dir[1]=(rand()%3)-1;
      }
      la->x=(la->x + la->dir[0]+SIZE_X)%SIZE_X;
      la->y=(la->y+la->dir[1]+SIZE_Y)%SIZE_Y;
      la=la->suivant;
    }
    

}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   /*A Completer*/
   Animal *ani=*liste_animal;
   while (ani){
    if (((float)rand()/RAND_MAX)<p_reproduce){
      ajouter_animal(ani->x,ani->y,ani->energie/2.0,liste_animal);
      ani->energie/=2.0;
    }
    ani=ani->suivant;
   }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  
  if (!*liste_proie) return;
    
  bouger_animaux(*liste_proie);
  Animal* ani=*liste_proie;
  Animal* tmp;
  while (ani){
    tmp=ani->suivant;
    if (monde[ani->x][ani->y]>-1) {
      ani->energie+=monde[ani->x][ani->y];
      monde[ani->x][ani->y]=temps_repousse_herbe;
    }
    ani->energie-=1;
    if (ani->energie<0) enlever_animal(liste_proie,ani);
    ani=tmp;
  }

  reproduce(liste_proie,0.5);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    Animal* ani=l;
    while (ani){
      if (ani->x==x && ani->y==y) return ani;
      ani=ani->suivant;
    }
  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   /*A Completer*/
   if (!*liste_predateur) return;

   bouger_animaux(*liste_predateur);
  Animal* ani=*liste_predateur;
  Animal* proie,*tmp;

   while (ani){
    tmp=ani->suivant;
    proie=animal_en_XY(*liste_proie,ani->x,ani->y);
    if (proie){
      ani->energie=ani->energie+proie->energie;
      enlever_animal(liste_proie,proie);
    }
    ani->energie-=1;
    if (ani->energie<0) enlever_animal(liste_predateur,ani);
    ani=tmp;
   }

    reproduce(liste_predateur,0.5);
    
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){

  for (int i=0;i<SIZE_X;i++){
    for (int j=0;j<SIZE_Y;j++){
      monde[i][j]+=1;
    }
  }


}


void ecrire_ecosys(const char *nom_fichier,Animal *liste_pred, Animal *liste_proie){
  
  FILE *f=fopen(nom_fichier,"w");
  if (!f){printf("Erreur ouverture %s \n",nom_fichier); return ; }

  fprintf(f,"<proies> \n");
  Animal *ani=liste_proie;
  while (ani){
    fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n",ani->x,ani->y,ani->dir[0],ani->dir[1],ani->energie);
    ani=ani->suivant;
  }
  fprintf(f,"<\\proies> \n");

  fprintf(f,"<predateurs> \n");
  ani=liste_pred;
  while (ani){
    fprintf(f,"x=%d y=%d dir=[%d %d] e=%f\n",ani->x,ani->y,ani->dir[0],ani->dir[1],ani->energie);
    ani=ani->suivant;
  }
  fprintf(f,"<\\predateurs> \n");

  fclose(f);
  
}

void lire_ecosys(const char *nom_fichier,Animal **liste_pred, Animal **liste_proie){
  FILE *f=fopen(nom_fichier,"r");
  if (!f){printf("Erreur ouverture %s \n",nom_fichier); return ;}

  Animal *ani;
  char buffer[256];
  int x,y;
  int dir[2];
  float e;

  /* Lire Proies*/
  fgets(buffer,256,f);
  assert (strncmp(buffer,"<proies>",8)==0);
  fgets(buffer,256,f);

  while (strncmp(buffer,"<\\proies>",9)!=0){
    sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f",&x,&y,&dir[0],&dir[1],&e);
    ani=creer_animal(x,y,e);
    ani->dir[0]=dir[0];
    ani->dir[1]=dir[1];
    *liste_proie=ajouter_en_tete_animal(*liste_proie,ani);
    fgets(buffer,256,f);
    
  }
  printf("f");
  /*Lire Pred*/

  fgets(buffer,256,f);
  assert (strncmp(buffer,"<predateurs>",12)==0);
  fgets(buffer,256,f);

  while (strncmp(buffer,"<\\predateurs>",13)!=0){
    sscanf(buffer,"x=%d y=%d dir=[%d %d] e=%f",&x,&y,&dir[0],&dir[1],&e);
    ani=creer_animal(x,y,e);
    ani->dir[0]=dir[0];
    ani->dir[1]=dir[1];
    *liste_pred=ajouter_en_tete_animal(*liste_pred,ani);
    fgets(buffer,256,f);
    
  }
  printf("g");
  fclose(f);
}



