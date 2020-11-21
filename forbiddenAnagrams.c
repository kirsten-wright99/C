#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE   0
#define TRUE    1
//#define DEBUG
//#define DEBUG2

// function prototype
void permute(int * usedLetters, char * setLetters, int wordLen, int emptySpot, char ** banned, char * s);

// global variables 
int perNum;
int banNum;
int n;

int main()
{
    char s[12];
    int * usedLetters; // Which letters have been used
    char * setLetters;  // The current arrangement of letters
    int i, j;
    char ** banned;

    scanf(" %s", s);
    int wordLen = strlen(s);
    scanf("%d", &n);
    banned = (char **) calloc(n, sizeof(char *));
    banNum = 0; // no permutations containing banned words have been seen yet

    // Create memory
    usedLetters = (int *) calloc(wordLen, sizeof(int));
    setLetters = (char *) calloc(wordLen, sizeof(char));

    for (i = 0; i < n; i++)
    {   
        perNum = 0; // we've seen no permutations yet  
        banned[i] = (char *) calloc(12, sizeof(char));
        scanf(" %s", banned[i]);
    }

    // Fill the arrays
    for (j = 0; j < wordLen; j++) 
    {
        usedLetters[j] = FALSE; // no letters have been used yet
        setLetters[j] = '\0';// no letters have been set yet
    }
        
    permute(usedLetters, setLetters, wordLen, 0, banned, s);
    
    // the next 7 lines free any dynamically allocated memory used 
    // throughout the program
    free(usedLetters);
    free(setLetters);
    for (i = 0; i < n; i++)
    {   
        free(banned[i]);
    }
    free(banned);

    printf("%d\n", perNum - banNum);

    return 1;
}

// this function loops through the banned words and determines if the 
// setLetters contains them.
int banCheck(char * setLetters, char ** banned)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (strstr(setLetters, banned[i]) != NULL)
            return 0;
    }

    return 1;
}

// The recursive method that computes the permuations
void permute(int * usedLetters, char * setLetters, int wordLen, int emptySpot, char ** banned, char * s)
{
    int i;

    if (wordLen == emptySpot) 
    { 
        perNum++;
        if (banCheck(setLetters, banned))
        {
            #ifdef DEBUG
                for (i = 0; i < wordLen; i++) // Print the string
                printf("%c", setLetters[i]);
                printf("\n"); 
            #endif
        }

        else 
        {
            banNum++;
             #ifdef DEBUG2
                for (i = 0; i < wordLen; i++) // Print the string
                printf("%c", setLetters[i]);
                printf("\n"); 
            #endif
        }

        return; 
    }
    
    int dupeLet[26] = {0};

    for (i = 0; i < wordLen; i++) 
    {   
        setLetters[emptySpot] = s[i];

        if (usedLetters[i] == FALSE && dupeLet[setLetters[emptySpot]-'a'] == FALSE) 
        {
            usedLetters[i] = TRUE;// Set the value to used
            dupeLet[setLetters[emptySpot]-'a'] = TRUE;
            // Assign the value
            permute(usedLetters, setLetters, wordLen, emptySpot + 1, banned, s); // Recurse
            // Undo the changes
            usedLetters[i] = FALSE;
            setLetters[emptySpot] = '\0';
        }
    }
    return;
}