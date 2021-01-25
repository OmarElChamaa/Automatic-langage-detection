#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "dawg.h"
#include "trie.h"
#include "hashmap.h"
#include "stack.h"
#include "math.h"


#define WORDS_MAX 200

/*
 * Copy this function template to construct either a DAWG or a trie 
 * based on the dictionary filename given
 * 
 * Don't forget to change the void return type of this function 
 */
DAWG * construct(char *dict) {
    // Instantiate either a Trie or a DAWG here
    // ...
    
    DAWG * dawg=newDawg();
    DATA * data=newDATA();
    

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
        dawgInsertion(dawg,line,data);
    }
    minimiser(0,data);

    fclose(fp);
    free(line);
    return dawg;
}






Trie * constructTrie(char *dict) {
    // Instantiate either a Trie or a DAWG here
    // ...
    Trie * trie=nouvTrie();

    

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
        trieInsertion(trie,line);
    }
    

    fclose(fp);
    free(line);
    return trie;
}





/* L'inserion manuelle des premiers elements Du Dictionnaire semblents bien marcher pour le Dawg,
Sauf que quand on essaye de charger le dictionnaire avec construct une erreur se passe et 
donc la hashmap devient vide
Je ne vois pas d'ou vient precisement dans l'insertion, ou meme dans la minimisation .
*/
int main(int argc, char* argv[]) {
    char *tab[WORDS_MAX];


    // char time[10];


    double total_time = 0.0 ;
    clock_t start =clock(); 

    if(argc<2 || argc>2){
        printf("Trop ou pas assez d'arguments ! \n utilisation : ./exe \"votre phrase\"  \n");
        exit(0);
    }


    DAWG * dawgFr=newDawg();
    DAWG * dawgAn=newDawg();
    DAWG * dawgAl=newDawg();

/*****************************************/

    double time_spent = 0.0;
    clock_t begin = clock();

    dawgFr=construct("../dict/french-wordlist.txt");

    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("temps insertion Dic Francais dans DAWG %f seconds \n", time_spent);

/*****************************************/

    time_spent = 0.0;
    begin = clock();

    dawgAl=construct("../dict/german-wordlist.txt");

    end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("temps insertion Dic Allemand dans DAWG %f seconds \n", time_spent);
    
/*****************************************/

    time_spent = 0.0;
    begin = clock();

    dawgAn=construct("../dict/english-wordlist.txt");

    end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("temps insertion Dic Anglais dans DAWG %f seconds \n", time_spent);

/*****************************************/

/****************************************/
    
    Trie * TrieFr =nouvTrie();
    Trie * TrieAn =nouvTrie();
    Trie * TrieAl =nouvTrie();

/*****************************************/
    time_spent = 0.0;
    begin = clock();

    TrieFr=constructTrie("../dict/french-wordlist.txt");

    end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("temps insertion Dic Francais dans Trie %f seconds \n", time_spent);

/*****************************************/
    time_spent=0.0;
    begin=clock();
    
    TrieAn=constructTrie("../dict/english-wordlist.txt");

    end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("temps insertion Dic Anglais dans Trie %f seconds \n", time_spent);

/*****************************************/
    time_spent=0.0;
    begin=clock();

    TrieAl=constructTrie("../dict/german-wordlist.txt");

    end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("temps insertion Dic Allemand dans Trie %f seconds \n", time_spent);

/*****************************************/


    printf("Phrase entrée: '%s'\n", argv[1]);


    int nb_mots = 0 ;
    char* ptr =  strtok(argv[1]," ");
    
    tab[0]=ptr ;
    while( ptr != NULL ) {

        if(nb_mots==200){
            printf("La phrase est trop grande ! elle doit etre inferieure a 200 mots\n");
        }
        ptr = strtok(NULL, " ");
        nb_mots ++ ;
        tab[nb_mots]=ptr;
    }

    int allemand =0;
    int francais=0;
    int anglais =0;

    int allemandD =0;
    int francaisD=0;
    int anglaisD =0;

    for(int i=0;i<nb_mots;i++){

        /*****************************************/

        time_spent=0.0;
        begin=clock();
        
        if(trieRecherche(TrieFr,tab[i])==true){
            francais ++ ;
        }

        end = clock();

        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("temps recherche du mot %s Dic Francais dans Trie %f seconds \n", tab[i],time_spent);

        /*****************************************/

        time_spent=0.0;
        begin=clock();

        if(trieRecherche(TrieAl,tab[i])==true){
            allemand ++ ;
        }

        end = clock();

        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("temps recherche du mot %s Dic Allemand dans Trie %f seconds \n", tab[i],time_spent);

        /*****************************************/

        time_spent=0.0;
        begin=clock();

        if(trieRecherche(TrieAn,tab[i])==true ){
            anglais++ ;
        }

        end = clock();

        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("temps recherche du mot %s Dic Anglais dans Trie %f seconds \n", tab[i],time_spent);

        /*****************************************/
        time_spent=0.0;
        begin=clock();

        if(dawgRecherche(dawgAn,tab[i])==true ){
            anglaisD++ ;
        }

        end = clock();

        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("temps recherche du mot %s Dic Anglais dans Dawg %f seconds \n", tab[i],time_spent);
        /*****************************************/
        time_spent=0.0;
        begin=clock();

        if(dawgRecherche(dawgFr,tab[i])==true ){
            francaisD++ ;
        }

        end = clock();

        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("temps recherche du mot %s Dic Francais dans Dawg %f seconds \n", tab[i],time_spent);
        
        /*****************************************/
        time_spent=0.0;
        begin=clock();

        if(dawgRecherche(dawgAl,tab[i])==true ){
            allemandD++ ;
        }

        end = clock();

        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("temps recherche du mot %s Dic Allemand dans Dawg %f seconds \n", tab[i],time_spent);

        /*****************************************/

    } 
    
    if(francais>allemand && francais>anglais){
        printf("la Langue est probablement francais \n");
    }else
    {
        if(francais<allemand && allemand >anglais){
            printf("la Langue est probablement allemand \n");
        }else
        {
            if(anglais>allemand && francais<anglais){
                printf("la Langue est probablement anglais \n");
            }else
            {
                printf("langue non detectee : \n|mots detectes FR :%d\n|mots detectes An : %d\n|mots detectes Al : %d \n",francais,anglais,allemand);
            }
            
        }
        
    }

    if(francaisD>allemandD && francaisD>anglaisD){
        printf("la Langue est probablement francais %d\n",francaisD);
    }else
    {
        if(francaisD<allemandD && allemandD >anglaisD){
            printf("dawg la Langue est probablement allemand %d\n",allemandD);
        }else
        {
            if(anglaisD>allemandD && francaisD<anglaisD){
                printf("dawg la Langue est probablement anglais %d\n",anglaisD);
            }else
            {
                printf("dawg langue non detectee : \n|mots detectes FR :%d\n|mots detectes An : %d\n|mots detectes Al : %d \n",francaisD,anglaisD,allemandD);
            }
            
        }
        
    }
    

    freeTrie(TrieFr);
    freeTrie(TrieAn);
    freeTrie(TrieAl);
    
    clock_t fin = clock();

    total_time += (double)(fin - start) / CLOCKS_PER_SEC;
    printf("temps total des Tries %f secondes \n", total_time);
    
    return 0;
}