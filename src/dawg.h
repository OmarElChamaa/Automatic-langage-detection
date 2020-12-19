#include "utils.h"
#include "hashmap.h"


typedef struct ARETE ARETE;
typedef struct DAWG DAWG ;
typedef struct DATA DATA;
DAWG* newDawg();
ARETE * newARETE();
DATA * newDATA();
// bool isHashmapVide(struct hashmap_s hashmap);
void supprimer_sommet(DAWG * sommet);
char * create_key(DAWG * sommet);
int profondeur(char * word_to_insert);
// bool recherche_mot (DAWG * racine, char * mot);
// DAWG * verifier(char * key,struct hashmap_s hashmap);
// // void mini(DAWG * sommet,struct stack *pile,struct hashmap_s hashmap);
DAWG * dawgInsertion(DAWG * racine ,char * word_to_insert,DATA * data);

