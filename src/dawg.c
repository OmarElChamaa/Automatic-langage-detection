#include "dawg.h"
#include "stack.h"
#include "hashmap.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int id_sommet_precedent = 0 ;
char * cle_dernier_sommet ;


typedef struct DAWG
{
    int id ;
    DAWG* enfants[ALPHABET_TAILLE];
    bool finMot;
}DAWG;

typedef struct ARETE{
    char label ;
    struct DAWG * sommetGauche ; 
    struct DAWG * sommetDroit ; 
}ARETE;

DAWG * newDawg() {
    DAWG * dawg=(DAWG * )malloc(sizeof(DAWG));
    if(dawg){
        for(int i = 0 ; i < ALPHABET_TAILLE ;i++){
            dawg->enfants[i]=NULL;
        }
        dawg->finMot=false;
        dawg->id=0;
        return dawg;
    }
    perror("New Dawg malloc \n");
    free(dawg);
    exit(0);
}

ARETE * newARETE(){
    ARETE* arete=(ARETE * )malloc(sizeof(ARETE));
    if(arete){
        arete->sommetDroit=NULL ;
        arete->sommetGauche=NULL ;
        return arete ;
    }
    perror("New ARETE malloc \n");
    free(arete);
    exit(0);
}

/* true if empty , false if not */


bool isHashmapVide(struct hashmap_s hashmap){
    unsigned nbrElem;
    if((nbrElem=hashmap_num_entries(&hashmap))==0){
        printf("nb Mots dans la hashmap = %d \n",nbrElem);
        return true ; 
    }
    return false ;
}


/* 
    on prend une cle de forme :
    0e!50
    
    ou char[0]==0 veut dire que 
    le sommet n'est pas la fin d'un mot

    char[1]==e est le label de l'arete sortante 
    char[2]==! est le separateur, tout ce qui vient apres est l'id 
    du sommet droite 

    si le sommet est la fin d'un mot strlen(key) sera que 1 
    comme elle ne pocede pas d'arete sortante 
*/

char * create_key(DAWG * sommet){
    char * id_sommet_droit;
    asprintf(&id_sommet_droit,"%d",sommet->id);
    char * separator="!";

    char is_word_end;
    if(sommet->finMot==true){
        is_word_end="1";
        return is_word_end;
        
    }else
    {
        is_word_end="0";
    }
    
    char * key =strcat(&is_word_end,separator);

    for(int i = 0 ; i<ALPHABET_TAILLE;i++){
        if(sommet->enfants[i]!=NULL){
            int id_sommet_droit= sommet->enfants[i]->id;
            asprintf(&key,"%s/%d",key,id_sommet_droit);
        }
    }
    
    return key;
}

/*pour supprimer un sommet qui n'est pas encore dans la hashmap */
DAWG * supprimer_sommet(DAWG * sommet){
    free(sommet);
}



DAWG * Minimiser(DAWG * racine ,struct hashmap_s hashmap,char * key,char * word_to_insert,int id,int profondeur,struct stack * pile){
    
    // int n = strlen(word_to_insert);
    // for(int i = 0 ; i<stack_size;i++){
    //     ARETE * arete = stack_pop(pile);

    // }
    
    
}


DAWG * dawgInsertion(DAWG * racine ,char * word_to_insert,struct hashmap_s hashmap,
char * dernier_noeud_inserer,int id_precedent){
    
    int n = strlen(word_to_insert);

    struct stack * pile ;

    int index = 0 ;

    int p = 0 ;

    DAWG * nouvelle_insertion=racine;

    int id_initializer =id_sommet_precedent ;

    for(int i = 0;i<n;i++){

        index=ascii_to_index(word_to_insert[i]);

        if(nouvelle_insertion->enfants[index]==NULL){

            nouvelle_insertion->enfants[index]=newDawg();
            DAWG * tmp = nouvelle_insertion->enfants[index];
            tmp->id=id_initializer++;

            ARETE * arete = newARETE(); 
            arete->label=word_to_insert[i];
            arete->sommetGauche=nouvelle_insertion;
            arete->sommetDroit=tmp;

            stack_push(pile,arete);
        }

        nouvelle_insertion=nouvelle_insertion->enfants[index];  
    }
    nouvelle_insertion->finMot=true ;
}

