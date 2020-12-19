#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "dawg.h"
#include "trie.h"
#include "hashmap.h"
#include "stack.h"


#define WORDS_MAX 200

/*
 * Copy this function template to construct either a DAWG or a trie 
 * based on the dictionary filename given
 * 
 * Don't forget to change the void return type of this function 
 */
void construct(char *dict) {
    // Instantiate either a Trie or a DAWG here
    // ...
    //DAWG * dawg=newDawg(0);

    // Trie * trie=nouvTrie();
    

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    FILE *fp;
    
    // open file 
    fp = fopen(dict, "r"); // read mode
    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    // read file
    while ((read = getline(&line, &len, fp)) != -1) {
        // remove newline
        size_t length = strlen(line);
        if((length > 0) && (line[length-1] == '\n'))
        {
            line[length-1] ='\0';
        }  
        // here insert the word in the trie or in the DAWG
        // To complete ... 
        // printf("%s \n",line);
        // trieInsertion(trie,line);
    }

    fclose(fp);
    free(line);

    // return ...;
}








int main(int argc, char* argv[]) {

    char * tab[WORDS_MAX];


    construct("../dict/french-wordlist.txt");
    construct("../dict/english-wordlist.txt");
    construct("../dict/german-wordlist.txt");

    // Here listen for user input, parse it and detect the language of the given text
    // To complete ...
    //     Trie * trie=nouvTrie();

    // trieInsertion(trie,"pirate");
    // trieInsertion(trie,"patate");
    // trieInsertion(trie,"oracle");


    // if(trieRecherche(trie,"oracle")==false){
    //     printf("not here \n");
    // }
    // else{
    //     printf("here \n");
    // }
    (void)argc;
    (void)argv;

    DAWG * dawg =newDawg();
    DATA * data=newDATA();
    dawgInsertion(dawg,"a",data);
    dawgInsertion(dawg,"abaissa",data);
    // dawgInsertion(dawg,"abaissable",data);
    // dawgInsertion(dawg,"abaissables",data);


    int nb_mots = 0 ;
    char str[]="omar is gay";
    char* ptr =  strtok(str," ");
    tab[0]=ptr ;
    /* walk through other tokens */
    while( ptr != NULL ) {
      printf( " %s\n", ptr );
      ptr = strtok(NULL, " ");
      nb_mots ++ ;
      tab[nb_mots]=ptr;
    }


    int allemand =0;
    int francais=0;
    int anglais =0;

    for(int i=0;i=<nb_mots;i++){

        

        // recherche(dawgF)==true {
        //     francais ++ ;
        // }
        // recherche(dawgD)==true {
        //     allemand ++ ;
        // }
        // recherche(dawgA)==true {
        //     anglais++ ;
        // }

    }
    
    return 0;
}