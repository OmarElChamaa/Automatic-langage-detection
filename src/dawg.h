#include "utils.h"
#include "hashmap.h"


typedef struct ARETE ARETE;
typedef struct DAWG DAWG ;
DAWG* newDawg();
bool isHashmapVide(struct hashmap_s hashmap);
DAWG * Minimiser(DAWG * racine ,struct hashmap_s hashmap,char * key,char * word_to_insert,int id,int profondeur,struct stack * pile);
char * create_key(DAWG * sommet);
DAWG * dawgInsertion(DAWG * racine ,char * word_to_insert,struct hashmap_s hashmap,
char * dernier_noeud_inserer,int id_precedent);