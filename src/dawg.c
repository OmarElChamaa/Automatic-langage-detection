#include "dawg.h"
#include "stack.h"
#include "hashmap.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int id_courant = 1;
char * last_word_inserted;

/**
 * 
 * @brief Structure d'un sommet du DAWG avec un tableau de pointeurs vers ses enfants,
 * son id unique et un bool finMot 
 * @struct DAWG
 */
typedef struct DAWG
{
    int id ;
    DAWG* enfants[ALPHABET_TAILLE];
    bool finMot;
}DAWG;


/**
 * @brief Structure d'une arete avec un pointeur vers le sommet 
 * gauche et un aure vers le sommet Droit, et un label.
 * @struct ARETE
 */
typedef struct ARETE{
    char label ;
    struct DAWG * sommetGauche ; 
    struct DAWG * sommetDroit ; 
}ARETE;


/**
 * @brief Structure qui contient une hashmap et une pile
 * @struct DATA
 */
typedef struct DATA{
    struct hashmap_s hashmap ;
    struct stack *pile ;
}DATA ;


/**
 * @brief Initialise un sommet du Dawg
 * 
 * @return DAWG* 
 */
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

/**
 * @brief Initialise l'arete avec des ponteurs vers NULL
 * et son label a ' ' 
 * @return ARETE* 
 */
ARETE * newARETE(){
    ARETE* arete=(ARETE * )malloc(sizeof(ARETE));
    if(arete){
        arete->sommetDroit=NULL ;
        arete->sommetGauche=NULL ;
        arete->label=' ';
        return arete ;
    }
    perror("New ARETE malloc \n");
    free(arete);
    exit(0);
}


/**
 * @brief initialisation de la struct data 
 * 
 * @return DATA* 
 */
DATA * newDATA(){
    DATA * data=(DATA * )malloc(sizeof(DATA ));
    int size = 1024 ;
    if(hashmap_create(size,&data->hashmap)!=0){
        perror("Creation hashmap \n");
    }
    data->pile=new_stack(128);
    return data;
}

/**
 * @brief Create a key object,
 * Pour la generation de cle, le premier bit est de 1 si le sommet 
 * est la fin d'un mot, et 0 sinon, puis on concatene les aretes sortantes par
 * order alphabetique de leur aretes sortantes, avec chaque arete separe avec un 
 * '/' et un ! entre le premier bit et le reste.
 * @param sommet 
 * @return char* 
 */
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
            asprintf(&key,"%s/%s%d",key,lettre,id_sommet_droit); 
        }
    }
    return key;
    
}

/**
 * @brief renvoie la profondeur a laquelle il faudra minimiser le dawg
 * 
 * @param word_to_insert 
 * @return int 
 */
int profondeur(char * word_to_insert){
    int p=0 ;
    if(last_word_inserted==NULL){
        return 0 ;
    }
    size_t x = 0;
    size_t i = 0;
    while(i<strlen(last_word_inserted) && x<strlen(word_to_insert)
    && word_to_insert[x]==last_word_inserted[i] && word_to_insert[x]!='\0'){
        p++;
        x++;
        i++;
    }
    return p ;
}

/**
 * @brief Supprime un noeud de la hashmap.
 * 
 * @param sommet 
 */
void supprimer_sommet(DAWG * sommet){
    free(sommet);
}


/**
 * @brief Verifie si un sommet avec la cle passe en argument existe deja 
 * dans le dawg.
 * 
 * @param key 
 * @param hashmap 
 * @return DAWG* 
 */

DAWG * verifier(char * key,struct hashmap_s hashmap){
    DAWG * G = newDawg();
    if((G=hashmap_get(&hashmap,key,strlen(key)))==NULL){
        return NULL ;
    }
    return G ;
}

/**
 * @brief recherche dans le dawg en utilisant le tableau de fils(enfants),
 * comme pour le Trie
 * si le mot existe, true si oui,false si non
 * 
 * @param racine 
 * @param mot 
 * @return true 
 * @return false 
 */
bool dawgRecherche(DAWG* racine ,const char * mot){
    size_t niveau = 0 ;
    size_t index =0 ;
    size_t longueurMot = strlen(mot);

    DAWG * copie = racine;

    for(;niveau<longueurMot;niveau++){
        index=ascii_to_index(mot[niveau]);
        //si vide donc automatiquement faux
        if(copie->enfants[index]==NULL){
            return false ;
        }
        copie = copie->enfants[index];
    }
    return (copie->finMot==true );
}

/**
 * @brief suit les etapes de minimisations du pseudo code
 * Pour verifier si un sommet equivalent existe, on cree une cle 
 * et on verifie si une valeur est associee a cette cle dans la hashmap
 * @param profondeur 
 * @param data 
 */
void minimiser(int profondeur,DATA * data){
    while(stack_size(data->pile)>profondeur){     
        ARETE * a = stack_pop(data->pile);
        char * cle = create_key(a->sommetDroit);

        DAWG * G=verifier(cle,data->hashmap);
        if(G==NULL){
            hashmap_put(&data->hashmap,cle,strlen(cle),a->sommetDroit);
        }else{
            supprimer_sommet(a->sommetDroit);
            a->sommetDroit=G;
        }
        free(cle);
        free(a);
    }
}





// DAWG * dawgInsertion(DAWG * racine ,char * word_to_insert,DATA * data){

//     if(word_to_insert[0]=='?'){
//         printf("on est dans le cas '?'\n");
//         for(int i=0 ; i<ALPHABET_TAILLE;i++){
//             if(racine->enfants[i]!=NULL){
//                 char * c =index_to_ascii(i);
//                 printf("|| La lettre %s existe || \n ",c);
//             }
//         }
//         printf("elements in hashmap %d \n",data->hashmap.size);
//         // minimiser(0,data);
//         printf("elements in hashmap %d \n",data->hashmap.size);
//         return racine ;
//     }

//     int p =profondeur(word_to_insert);
//     int index = 0 ;
//     int n = strlen(word_to_insert);

//     minimiser(p,data);

//     if(stack_size(data->pile)==0){  

//         DAWG * nouvelle_insertion=racine;
//         for(int i = p;i<n;i++){
//             // printf("on traite la lettre %c \n",word_to_insert[i]);

//             index=ascii_to_index(word_to_insert[i]);

//             if(nouvelle_insertion->enfants[index]==NULL){

//                 nouvelle_insertion->enfants[index]=newDawg();
            
//                 DAWG * tmp = nouvelle_insertion->enfants[index];
            
//                 tmp->id=id_courant;
//                 id_courant++;

//                 ARETE * arete = newARETE(); 
//                 arete->label=word_to_insert[i];
//                 arete->sommetGauche=nouvelle_insertion;
//                 arete->sommetDroit=tmp;
//                 stack_push(data->pile,arete);
//             } else
//             {
//                 DAWG * tmp = nouvelle_insertion->enfants[index];
            
//                 tmp->id=id_courant;
//                 id_courant++;

//                 ARETE * arete = newARETE(); 
//                 arete->label=word_to_insert[i];
//                 arete->sommetGauche=nouvelle_insertion;
//                 arete->sommetDroit=tmp;
//                 stack_push(data->pile,arete);
//             }
            
//             nouvelle_insertion=nouvelle_insertion->enfants[index];  
//         }
//         nouvelle_insertion->finMot=true ;
//     }else
//     {
//         ARETE * dernier_elem = stack_peek(data->pile);
//         DAWG * nouvelle_insertion=dernier_elem->sommetDroit;
//         for(int i = p;i<n ;i++){

//             // printf("on traite la lettre %c \n",word_to_insert[i]);

//             index=ascii_to_index(word_to_insert[i]);

//             if(nouvelle_insertion->enfants[index]==NULL){

//                 nouvelle_insertion->enfants[index]=newDawg();
            
//                 DAWG * tmp = nouvelle_insertion->enfants[index];
            
//                 tmp->id=id_courant;
//                 id_courant++;

//                 ARETE * arete = newARETE(); 
//                 arete->label=word_to_insert[i];
//                 arete->sommetGauche=nouvelle_insertion;
//                 arete->sommetDroit=tmp;
//                 stack_push(data->pile,arete); 
            
//             }else{
//                 DAWG * tmp = nouvelle_insertion->enfants[index];
            
//                 tmp->id=id_courant;
//                 id_courant++;

//                 ARETE * arete = newARETE(); 
//                 arete->label=word_to_insert[i];
//                 arete->sommetGauche=nouvelle_insertion;
//                 arete->sommetDroit=tmp;
//                 stack_push(data->pile,arete);
//             }
//             nouvelle_insertion=nouvelle_insertion->enfants[index];  
//         }
//         nouvelle_insertion->finMot=true ;
//     }
//     last_word_inserted=word_to_insert;
    
//    return racine ; 

// }


/**
 * @brief cette fonction est suppose suivre les etapes d'insertions
 * qui nous sont donnees dans le pseudo code.
 * 
 * @param racine 
 * @param word_to_insert 
 * @param data 
 * @return DAWG* 
 */
DAWG *dawgInsertion(DAWG * racine ,char * word_to_insert,DATA * data){
    int p=profondeur(word_to_insert);
    
    minimiser(p,data);

    int n= strlen(word_to_insert);

    int index = 0 ;
    DAWG * nouvelle_insertion = newDawg();
    ARETE * a = newARETE();

    for(int i = p;i<n;i++){

        index=ascii_to_index(word_to_insert[i]);

        if(is_stack_empty(data->pile)==true){
            if(racine->enfants[index]==NULL){
                racine->enfants[index]=nouvelle_insertion;
                nouvelle_insertion->id=id_courant;
                id_courant ++ ;
              
            }else // si case prise
            {  
                nouvelle_insertion=racine->enfants[index];
            }  
            a->sommetGauche=racine ;
            a->sommetDroit=nouvelle_insertion;
            a->label=word_to_insert[i];
            stack_push(data->pile,a);
            
        }else
        {   
            a=stack_peek(data->pile);
            if(a->sommetDroit->enfants[index]==NULL){
                a->sommetDroit->enfants[index]=nouvelle_insertion;
                nouvelle_insertion->id=id_courant;
                id_courant ++ ;
              
            }else // si case prise
            {  
                nouvelle_insertion=a->sommetDroit->enfants[index];
            }
            ARETE * b = newARETE();
            b->sommetGauche = a->sommetDroit;
            b->sommetDroit=nouvelle_insertion;
            b->label=word_to_insert[i];
            stack_push(data->pile,b);

        }
        
    }
    nouvelle_insertion->finMot=true;
    int word_to_insert_size=strlen(word_to_insert);
    last_word_inserted=(char*) realloc(last_word_inserted,word_to_insert_size);
    strcpy(last_word_inserted,word_to_insert);
    // last_word_inserted=word_to_insert ;
    return nouvelle_insertion ; 
    
}




void freeDawg(DAWG* dawg)
{
    
    for (int i = 0; i < ALPHABET_TAILLE; i++)
    {
		if (dawg->enfants[i] != NULL)
		{
			freeDawg(dawg->enfants[i]);
		}
		
    }
	
    free(dawg);
}

int freeHashHash(void* const c,struct hashmap_element_s *const e)
{
    (void)c;
	free((char*)e->key);
	free(e->data);
    exit(EXIT_SUCCESS);
}

void freeData(DATA* d)
{
	hashmap_iterate_pairs(&(d->hashmap), freeHashHash, NULL);
	hashmap_destroy(&(d->hashmap));
	free_stack(d->pile);
	//free(d);
}