
#include"trie.h"

/**
 * @brief Sommet Trie comportant un tableau de fils possibles et un 
 * bool finMot
 * @struct Trie
 */
typedef struct Trie
{
    Trie *enfants[ALPHABET_TAILLE];
    bool finMot;
}Trie;

/**
 * @brief Cree un trie vide
 * 
 * @return Trie* 
 */
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


/**
 * @brief Parcours le trie et free toute la memoire allouee. 
 * 
 * @param trie 
 */
void freeTrie(Trie* trie)
{
    for (int i = 0; i < ALPHABET_TAILLE; i++)
    {
        if (trie->enfants[i] != NULL)
        {
            freeTrie(trie->enfants[i]);
        }
        else
        {
            continue;
        }
    }
    free(trie);
}


/**
 * @brief Insere le mot passe en parametre depuis la racine
 * 
 * @param racine 
 * @param mot 
 */
void trieInsertion(Trie * racine,const char * mot){
    size_t niveau = 0 ;
    size_t index =0 ;
    size_t longueurMot = strlen(mot);

    Trie * nouvelleInsertion = racine;

    for(;niveau<longueurMot;niveau++){

        index=ascii_to_index(mot[niveau]);

        if(nouvelleInsertion->enfants[index]==NULL){

            nouvelleInsertion->enfants[index]=nouvTrie();

        }
        nouvelleInsertion=nouvelleInsertion->enfants[index];
    }
    nouvelleInsertion->finMot=true;
}

/**
 * @brief Cherche un mot dans le trie
 * 
 * @param racine 
 * @param mot 
 * @return true si mot existe
 * @return false sinon
 */
bool trieRecherche(Trie * racine ,const char * mot){
    size_t niveau = 0;
    size_t index = 0;
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