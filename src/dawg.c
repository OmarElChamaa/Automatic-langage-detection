#include "dawg.h"
#include "stack.h"
#include "hashmap.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int id_courant = 1;
char * last_word_inserted;


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

typedef struct DATA{
    struct hashmap_s hashmap ;
    struct stack *pile ;
}DATA ;



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

DATA * newDATA(){
    DATA * data=(DATA * )malloc(sizeof(DATA ));
    int size = 64 ;
    hashmap_create(size,&data->hashmap);
    data->pile=new_stack(50);
    return data;
}


char * create_key(DAWG * sommet){
    char * id_sommet_droit;
    asprintf(&id_sommet_droit,"%d",sommet->id);
    char * separator="!";

    char * is_word_end;
    if(sommet->finMot==true){
        is_word_end="1";
        
    }else
    {
        is_word_end="0";
    }

    char * key =concat(is_word_end,separator);


    for(int i = 0 ; i<ALPHABET_TAILLE;i++){    
        if(sommet->enfants[i]!=NULL){
            int id_sommet_droit= sommet->enfants[i]->id; 
            char * lettre=index_to_ascii(i);
            asprintf(&key,"%s/%s!%d",key,lettre,id_sommet_droit); 
        }
    }
    return key;
    
}


int profondeur(char * word_to_insert){
    int p=0 ;
    if(last_word_inserted==NULL){
        return 0 ;
    }
    int x = 0;
    int i = 0;
    while(i<strlen(last_word_inserted) && x<strlen(word_to_insert)
    && word_to_insert[x]==last_word_inserted[i]){
        p++;
        x++;
        i++;
    }
    return p ;
}

/*pour supprimer un sommet qui n'est pas encore dans la hashmap */
void supprimer_sommet(DAWG * sommet){
    free(sommet);
}


DAWG * verifier(char * key,struct hashmap_s hashmap){
    DAWG * G = newDawg();
    if((G=hashmap_get(&hashmap,key,strlen(key)))==NULL){
        return NULL ;
    }
    return G ;
}



DAWG * minimiser(int profondeur,DATA * data){
    while(stack_size(data->pile)>profondeur){
        ARETE * a = stack_pop(data->pile);
        char * cle = create_key(a->sommetDroit);

        DAWG * G=verifier(cle,data->hashmap);
        printf("Arete= %c \n Key =%s \n",a->label,cle);

        if(G==NULL){
            hashmap_put(&data->hashmap,cle,strlen(cle),a->sommetDroit);
            printf("on ajoute dans la hashmap le sommet %c\n",a->label);
        }else{
            supprimer_sommet(a->sommetDroit);
            a->sommetDroit=G;
        }
    }
    return NULL ;
}

DAWG * dawgInsertion(DAWG * racine ,char * word_to_insert,DATA * data){  
    
    int n = strlen(word_to_insert);

    int index = 0 ;
    int p = profondeur(word_to_insert);
    printf("profondeur a minimiser : %d \n",p);

    DAWG * nouvelle_insertion=racine;

    for(int i = 0;i<n;i++){

        index=ascii_to_index(word_to_insert[i]);

        if(nouvelle_insertion->enfants[index]==NULL){

            nouvelle_insertion->enfants[index]=newDawg();
            
            DAWG * tmp = nouvelle_insertion->enfants[index];
            
            tmp->id=id_courant;
            id_courant++;

            ARETE * arete = newARETE(); 
            arete->label=word_to_insert[i];
            arete->sommetGauche=nouvelle_insertion;
            arete->sommetDroit=tmp;
            stack_push(data->pile,arete);
            
        }    
        
        nouvelle_insertion=nouvelle_insertion->enfants[index];  
    }
    printf("stack size is %d \n",stack_size(data->pile));
    nouvelle_insertion->finMot=true ;
    if(p!=0){
        minimiser(p,data);

        for(int i = p; i<strlen(word_to_insert);i++){
        
            ARETE * tmp = stack_peek(data->pile);
            printf("arete depile apres minimisation %c \n ",tmp->label);

            index=ascii_to_index(word_to_insert[i]);
            printf("next letter %c \n",word_to_insert[i]);

            DAWG * d = tmp->sommetDroit->enfants[index];
            ARETE *  a =newARETE();
            a->sommetDroit=d;
            a->sommetGauche=tmp->sommetDroit;
            a->label=word_to_insert[i];

            stack_push(data->pile,a);

        }

        for(int i = 0 ;i<stack_size(data->pile);i++){
            ARETE *  a =stack_pop(data->pile);
            printf("||%c|| \n",a->label);
        }
    }

    


    // printf("stack size is apres minimisation %d \n",stack_size(data->pile));
    // printf("elements in hashmap %d \n",data->hashmap.size);
    last_word_inserted=word_to_insert;
    return nouvelle_insertion ;
}