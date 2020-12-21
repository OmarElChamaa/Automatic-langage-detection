#include "utils.h"
#include "hashmap.h"


typedef struct ARETE ARETE;
typedef struct DAWG DAWG ;
typedef struct DATA DATA;
DAWG * newDawg();
ARETE * newARETE();
DATA * newDATA();
void supprimer_sommet(DAWG * sommet);
char * create_key(DAWG * sommet);
int profondeur(char * word_to_insert);
bool dawgRecherche(DAWG* racine ,const char * mot);
DAWG * verifier(char * key,struct hashmap_s hashmap);
void minimiser(int profondeur,DATA * data);
DAWG * dawgInsertion(DAWG * racine ,char * word_to_insert,DATA * data);
void freeDawg(DAWG* dawg);
int freeHashHash(void* const c,struct hashmap_element_s *const e);
void freeData(DATA* d);