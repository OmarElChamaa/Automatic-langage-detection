#include "dawg.h"



typedef struct ARETE{
    char label ;
    struct ARETE * sommetGauche ; 
    char * sommetDroit ; 
}ARETE;

typedef struct DAWG
{
    char id ;
    char enfants[ALPHABET_TAILLE];
    bool finMot;
}DAWG;

DAWG * newDawg(double id) {
    DAWG * dawg=(DAWG * )malloc(sizeof(DAWG));
    if(dawg){
        dawg->finMot=false;
        for(int i = 0 ; i < ALPHABET_TAILLE ;i++){
            dawg->enfants[i]=NULL;
        }
        dawg->id=0;
        return dawg;
    }
    perror("New Dawg malloc \n");
    free(dawg);
    exit(0);
}
/*
DAWG * dawgInsertion(char * wordToInsert){

}*/