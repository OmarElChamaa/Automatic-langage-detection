

#include "utils.h"

/**
 * Change ASCII char (a-z) to array index
 * a -> 0, b -> 1, c -> 2, ..., z -> 25
 */
size_t ascii_to_index(char c) {
    size_t index = (size_t) c;

    if(index < 97 || index > 122) {
        perror("ascii_to_index function can only read lowercase letter a-z.\n");
        exit(EXIT_FAILURE);
    }

    return index - 97;
}

/**
 * Change array index to ASCII character
 */

char * index_to_ascii(int index){
    switch (index)
    {
    case 0:
        return "a" ;
        break;
    case 1:
        return "b" ;
        break;
    case 2:
        return "c" ;
        break;
    case 3:
        return "d" ;
        break; 
    case 4:
        return "e" ;
        break;
    case 5:
        return "f" ;
        break;
    case 6:
        return "g" ;
        break;
    case 7:
        return "h" ;
        break;
    case 8:
        return "i" ;
        break;
    case 9:
        return "j" ;
        break;
    case 10:
        return "k" ;
        break;
    case 11:
        return "l" ;
        break;
    case 12:
        return "m" ;
        break;
    case 13:
        return "n" ;
        break;
    case 14:
        return "o" ;
        break;
    case 15:
        return "p" ;
        break;
    case 16:
        return "q" ;
        break;
    case 17:
        return "r" ;
        break;
    case 18:
        return "s" ;
        break;
    case 19:
        return "t" ;
        break;
    case 20:
        return "u" ;
        break;
    case 21:
        return "v" ;
        break;
    case 22:
        return "w" ;
        break;
    case 23:
        return "x" ;
        break;
    case 24:
        return "y" ;
        break;
    case 25:
        return "z" ;
        break;
    default:
        perror("character not found \n");
        break;
    }
}

/**
 * Remove char from string at the given index
 */
void remove_char(char *word, size_t index) {
    memmove(&word[index],&word[index+1],strlen(word)-index);
}

/**
 * Remove all char from given string that aren't a-z 
 */
void parse_word(char *word) {
    for(size_t i = 0; i < strlen(word); i++) {
        size_t index = (size_t) word[i];
        if(index < 97 || index > 122) {
            remove_char(word, i);
        }
    }
}

/**
 * Concat two strings together
 */
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}