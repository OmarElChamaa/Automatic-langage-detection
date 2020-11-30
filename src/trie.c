
#include"trie.h"



/*
    finMot =true si la lettre est 
    la fin d'un mot
*/

typedef struct Trie
{
    Trie *enfants[ALPHABET_TAILLE];
    bool finMot;
}Trie;


Trie * nouvTrie(void){
    Trie * noeud = (Trie *)malloc(sizeof(Trie));

    if(noeud){//noeud!=NULL
        noeud->finMot=false;
        //initialisation tableau a NULL 
        for(int i = 0 ; i < ALPHABET_TAILLE ;i++){
            noeud->enfants[i]=NULL;
        }
        return noeud ;
    }

    perror("Malloc nouvTrie");
    free(noeud);
    exit(0);
}


void trieInsertion(Trie * racine,const char * mot){
    size_t niveau = 0 ;
    size_t index =0 ;
    size_t longueurMot = strlen(mot);

    Trie * nouvelleInsertion = racine;
    // printf("Longueur mot %ld \n",longueurMot);

    for(;niveau<longueurMot;niveau++){
        // fprintf(stdout,"%c \n",mot[niveau]);
        index=ascii_to_index(mot[niveau]);
        if(nouvelleInsertion->enfants[index]==NULL){
			
            // printf("index is boucle for %ld",index);
            nouvelleInsertion->enfants[index]=nouvTrie();
        }
        // printf("index is %ld \n",index);
        nouvelleInsertion=nouvelleInsertion->enfants[index];
    }
    nouvelleInsertion->finMot=true;
}

bool trieRecherche(Trie * racine ,const char * mot){
    size_t niveau = 0 ;
    size_t index =0 ;
    size_t longueurMot = strlen(mot);

    Trie * nouvelleInsertion = racine;

    for(;niveau<longueurMot;niveau++){
        index =ascii_to_index(mot[niveau]);

        //si vide donc automatiquement faux
        if(nouvelleInsertion->enfants[index]==NULL){
            return false ;
        }
        nouvelleInsertion = nouvelleInsertion->enfants[index];
    }
    return (nouvelleInsertion->finMot==true && nouvelleInsertion != NULL );
}
