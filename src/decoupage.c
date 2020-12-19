#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "dawg.h"
#include "trie.h"
#include "hashmap.h"
#define MAX 100

/**
 * @brief Découpe une phrase en plusieurs mots
 * @param phrase
 * @return void
 * @warning Marche avec char [] et non avec char* ! Si problème
 * 			alors utiliser taille MAX !
 */

void cut(char* phrase)
{
   const char s[2] = " ";
   char *ptr;
   
   /* get the first token */
   ptr= strtok(phrase, s);
   
   /* walk through other tokens */
   while( ptr != NULL ) {
      printf( " %s\n", ptr );
      ptr = strtok(NULL, s);
   }
   
   return(0);
}