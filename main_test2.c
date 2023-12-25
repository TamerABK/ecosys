#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "ecosys.h"

#define NUM_PRED 20
#define NUM_PROI 20


int main(void){
    
    srand(time(NULL));
    
    int energie=10;
    Animal *liste_proie = creer_animal((rand() % SIZE_X),(rand() % (SIZE_Y)),energie);
    Animal *liste_predateur = creer_animal((rand() % (SIZE_X)),(rand() % (SIZE_Y)),energie);
    


    for (int i=0; i<NUM_PRED-1;i++){
        ajouter_animal(rand()%SIZE_X, (rand() % (SIZE_Y)),energie,&liste_predateur);
    }

    for (int i=0; i<NUM_PROI-1;i++){
        ajouter_animal((rand() % (SIZE_X)),(rand() % (SIZE_Y)),energie,&liste_proie);
    }

     //afficher_ecosys(liste_proie,liste_predateur); 

     liste_proie=liberer_liste_animaux(liste_proie);

    Animal *a1 = creer_animal(0,10, energie);
    Animal *a2 = creer_animal(15,35, energie);
    Animal *a3 = creer_animal(2,42, energie);
    Animal *a4 = creer_animal(18,13, energie);
  
    a1->suivant=a2;
    a2->suivant=a3;
    a3->suivant=a4;

    liste_proie=a1;

    enlever_animal(&liste_proie, a2);
    

    //afficher_ecosys(liste_proie,liste_predateur); 
    bouger_animaux(liste_predateur);
    reproduce(&liste_predateur,0.5);
    
    afficher_ecosys(liste_proie,liste_predateur); 

    ecrire_ecosys("test.txt",liste_predateur,liste_proie);

    liste_proie=liberer_liste_animaux(liste_proie);
    liste_predateur=liberer_liste_animaux(liste_predateur);

    lire_ecosys("test.txt",&liste_predateur,&liste_proie);

    afficher_ecosys(liste_proie,liste_predateur); 

    liberer_liste_animaux(liste_proie);
    liberer_liste_animaux(liste_predateur);

     return 0;
}


