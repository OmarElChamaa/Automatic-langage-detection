#include "utils.h"

typedef struct Trie Trie ;
Trie* nouvTrie(void);

void trieInsertion(Trie * racine,const char * mot);
bool trieRecherche(Trie * racine, const char * mot);