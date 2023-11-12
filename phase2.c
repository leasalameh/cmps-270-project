#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHAR_SIZE 26         // Define the character size
#define MAX_SPELLS 100       // Maximum number of spells
#define MAX_MOVES 100        // Maximum number of moves to check for repetition later
#define MAX_SPELL_LENGTH 100 // Maximum length of a spell
#define MAX_WORD_LENGTH 100
#define ALPHABET_SIZE 26

// Data structure to store a Trie node
struct Trie
{
    int isLeaf; // 1 when the node is a leaf node
    struct Trie *character[CHAR_SIZE];
};

// Function that returns a new Trie node
struct Trie *getNewTrieNode()
{
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->isLeaf = 0;
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        node->character[i] = NULL;
    }
    return node;
}

// Iterative function to insert a string into a Trie
void insert(struct Trie *head, char *str)
{
    struct Trie *curr = head;
    while (*str)
    {
        if (curr->character[*str - 'a'] == NULL)
        {
            curr->character[*str - 'a'] = getNewTrieNode();
            if (curr->character[*str - 'a'] == NULL)
            {
                fprintf(stderr, "Memory allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        curr = curr->character[*str - 'a'];
        str++;
    }
    curr->isLeaf = 1;
}

// Iterative function to search a string in a Trie. It returns 1
// if the string is found in the Trie; otherwise, it returns 0.
int search(struct Trie *head, char *str)
{
    // return 0 if Trie is empty
    if (head == NULL)
    {
        return 0;
    }

    struct Trie *curr = head;
    while (*str)
    {
        // go to the next node
        curr = curr->character[*str - 'a'];

        // if the string is invalid (reached end of a path in the Trie)
        if (curr == NULL)
        {
            return 0;
        }

        // move to the next character
        str++;
    }

    // return 1 if the current node is a leaf and the
    // end of the string is reached
    return curr->isLeaf;
}

// Returns 1 if a given Trie node has any children
int hasChildren(struct Trie *curr)
{
    for (int i = 0; i < CHAR_SIZE; i++)
    {
        if (curr->character[i])
        {
            return 1; // child found
        }
    }

    return 0;
}

// Recursive function to delete a string from a Trie
int deletion(struct Trie **curr, char *str)
{
    // return 0 if Trie is empty
    if (*curr == NULL)
    {
        return 0;
    }

    // if the end of the string is not reached
    if (*str)
    {
        // recur for the node corresponding to the next character in
        // the string and if it returns 1, delete the current node
        // (if it is non-leaf)
        if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
            deletion(&((*curr)->character[*str - 'a']), str + 1) &&
            (*curr)->isLeaf == 0)
        {
            if (!hasChildren(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }

    // if the end of the string is reached
    if (*str == '\0' && (*curr)->isLeaf)
    {
        // if the current node is a leaf node and doesn't have any children
        if (!hasChildren(*curr))
        {
            free(*curr); // delete the current node
            (*curr) = NULL;
            return 1; // delete the non-leaf parent nodes
        }

        // if the current node is a leaf node and has children
        else
        {
            // mark the current node as a non-leaf node (DON'T DELETE IT)
            (*curr)->isLeaf = 0;
            return 0; // don't delete its parent nodes
        }
    }

    return 0;
}

void DFS(struct Trie *node, char *buffer, int depth)
{
    if (node->isLeaf)
    {
        buffer[depth] = '\0';
        printf("%s\n", buffer);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->character[i] != NULL)
        {
            buffer[depth] = i + 'a';
            DFS(node->character[i], buffer, depth + 1);
        }
    }
}

void findMissingAlphabets(struct Trie *root, char missingAlphabets[], int *missingCount)
{
    // Check missing alphabets (a to z)
    for (char ch = 'a'; ch <= 'z'; ch++)
    {
        if (root->character[ch - 'a'] == NULL)
        {
            missingAlphabets[*missingCount] = ch;
            (*missingCount)++;
        }
    }
}

void findWinningWords(struct Trie *node, const char *suffix, const char *missingLetters, char winningWords[MAX_SPELLS][MAX_WORD_LENGTH], int *count)
{
    if (node == NULL)
    {
        return;
    }

    if (node->isLeaf)
    {
        char lastChar = suffix[strlen(suffix) - 1];
        if (strchr(missingLetters, lastChar) != NULL)
        {
            strcpy(winningWords[*count], suffix);
            (*count)++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (node->character[i])
        {
            char newSuffix[MAX_WORD_LENGTH];
            strcpy(newSuffix, suffix);
            strncat(newSuffix, (char[]){(char)(i + 'a')}, 1);
            findWinningWords(node->character[i], newSuffix, missingLetters, winningWords, count);
        }
    }
}

int readSpells(char spells[][MAX_SPELL_LENGTH]);
void storeWords(struct Trie *head, char spells[][MAX_SPELL_LENGTH], int numberOfSpells);
void displaySpells(char spells[][MAX_SPELL_LENGTH], int numberOfSpells);
int isSpellValid(char spell[], char spells[][MAX_SPELL_LENGTH], int numberOfSpells);
int countOccurencies(char spells[][MAX_SPELL_LENGTH], char lastChar, int numberOfSpells);
void special_print(const char *str);
void loading_print(const char *str);
int coinTossWithBot(const char *player_name, const char *difficulty);
int easyBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells);
int mediumBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, char winningWords[], int *count);
int hardBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, int currentplayer, struct Trie *head);
int getSpellIndex(const char *spell, char Spells[][MAX_SPELL_LENGTH], int numberOfSpells){
    for (int i=0; i <numberOfSpells; i++){
        if (strcmp(spell, Spells[i] ==0)){
            return i; // return index of the spell 
        }
        
    }
    return -1; // spell wasnt found 
}


int main()
{
    // 2. GETTING THE NAME OF THE PLAYER AND CHOOSING THE DIFFICULTY welcome
    char player1_name[20];
    char difficulty[7];

    special_print("Welcome to The Spell Game!\n");

    // EXPLAINING THE GAME TO THE PLAYER AND CHOOSING DIFFICULTY.
    special_print("\nYou will be provided with a list of spells you can choose from.\nYou must continue to cast a spell that is more powerful than the one cast by the other player.\nFor a spell to be more powerful, it should satisfy two requirements:\n1- It should not have been cast during the battle before.\n2- The first character of the spell should be the same as the last character of the spell chosen in the previous round by the other player.\n");

    special_print("\nPlease enter your name (no spaces): ");
    scanf("%s", player1_name);
    printf("Hello %s, choose the difficulty level ('easy','medium','hard'): ", player1_name);
    scanf("%s", difficulty);

    while (1)
    {
        if (strcmp("easy", difficulty) == 0)
        {
            special_print("You will be playing against Tim the bot.\n");
            special_print("\nLet's see who's the real SPELL MASTER!\nMay the best player win...\n");

            // 1. READING THE SPELLS FROM THE FILE SPELLS.TXT
            char spells[MAX_SPELLS][MAX_SPELL_LENGTH];
            int numberOfSpells = readSpells(spells);

            // 3. DISPLAYING THE SPELLS
            displaySpells(spells, numberOfSpells);

            // 4. TOSS A COIN TO SEE WHO STARTS
            int currentPlayer = coinTossWithBot(player1_name, difficulty);

            break;
        }
        else if (strcmp("medium", difficulty) == 0)
        {
            special_print("You will be playing against Tom the bot.\n");
            special_print("\nLet's see who's the real SPELL MASTER...\nMay the best player win...\n");

            // 1. READING THE SPELLS FROM THE FILE SPELLS.TXT
            char spells[MAX_SPELLS][MAX_SPELL_LENGTH];
            int numberOfSpells = readSpells(spells);

            // 3. DISPLAYING THE SPELLS
            displaySpells(spells, numberOfSpells);

            // 4. TOSS A COIN TO SEE WHO STARTS
            int currentPlayer = coinTossWithBot(player1_name, difficulty);
            int chosenWords [MAX_SPELL_LENGTH] = {0};
            char lastChar = 'a';
            while (1){
                char currentSpell [MAX_SPELL_LENGTH];
                // player's turn
                if (currentPlayer ==0){
                    special_print("\nYour turn! Enter a spell: ");
                    scanf("%s", currentSpell);
                // check if spell is valid 
                    while (!isSpellValid(currentSpell, spells, numberOfSpells) || chosenWords [getSpellIndex(currentSpell, spells, numberOfSpells)] ==1){
                        special_print("Invalid spell. Enter a valid spell: " );
                            scanf("%s", currentSpell);
                        
                    }
                    // mark chosen word as used 
                    chosenWords [getSpellIndex(currentSpell, spells, numberOfSpells)] =1;
                    // update lastChar for next turn (increases chances of winning)
                    lastChar = currentSpell [strlen(currentSpell) -1];}
                else {
                    int botSpellIndex = mediumBot(lastChar, spells, numberOfSpells, chosenWords, winningWords, *count);
                    while (chosenWords[botSpellIndex] ==1){
                        botSpellIndex = mediumBot(lastChar, spells, numberOfSpells, chosenWords, winningWords, *count);
                    }
                    // mark chosen word again 
                    chosenWords[botSpellIndex] = 1;

                    // display bot spell
                    printf("\nTom the bot chooses: %s\n", spells [botSpellIndex]);
                    strcpy(currentSpell, spells[botSpellIndex]);
                    currentPlayer = 1 - currentPlayer;}
                }
                
            }
            

            break;
        }
        else if (strcmp("hard", difficulty) == 0)
        {
            special_print("You will be playing against Bob the bot.\n");
            special_print("\nLet's see who's the real SPELL MASTER...\nMay the best player win...\n");

            // 1. READING THE SPELLS FROM THE FILE SPELLS.TXT
            char spells[MAX_SPELLS][MAX_SPELL_LENGTH];
            int numberOfSpells = readSpells(spells);

            // 3. DISPLAYING THE SPELLS
            displaySpells(spells, numberOfSpells);

            // 4. TOSS A COIN TO SEE WHO STARTS
            int currentPlayer = coinTossWithBot(player1_name, difficulty);

            //
            char missingLetters[26];
            struct Trie *head = getNewTrieNode();
            storeWords(head, spells, numberOfSpells);
            int missingCount = 0;
            findMissingAlphabets(head, missingLetters, &missingCount);
            char winningWords[MAX_SPELLS][MAX_WORD_LENGTH];
            int count = 0;

            findWinningWords(head, "", missingLetters, winningWords, &count);
            printf("Winning Words:\n");
            for (int i = 0; i < count; ++i)
            {
                printf("%s\n", winningWords[i]);
            }

            break;
        }
        else
        {
            special_print("Invalid difficulty level. Please choose 'easy', 'medium', or 'hard': ");
            scanf("%s", difficulty);
        }
    }

    return 0;
}

// 1. READS A FILE CALLED SPELLS.TXT
int readSpells(char spells[][MAX_SPELL_LENGTH])
{
    FILE *fptr = fopen("spells.txt", "r"); // A pointer to our file that we open and read (r=read mode)

    if (fptr == NULL)
    {
        return 0;
    }

    char firstLine[4];         // Reading first line as a string => Number of Spells: 78, will be stored in firstLine
    fgets(firstLine, 4, fptr); // 4=> max number of characters to read from this line

    int numberOfSpells = atoi(firstLine); // Converting 78 into an integer using atoi

    for (int i = 0; i < numberOfSpells; i++)
    {
        fscanf(fptr, "%s", spells[i]);
    }

    fclose(fptr);
    return numberOfSpells;
}

void storeWords(struct Trie *head, char spells[][MAX_SPELL_LENGTH], int numberOfSpells)
{
    FILE *fptr = fopen("spells.txt", "r");
    if (fptr == NULL)
    {
        perror("Error opening the file");
        return; // Exit the function on error
    }

    char firstLine[100]; // Assuming the first line is not longer than 100 characters

    // Read the first line and extract the number of spells
    if (fgets(firstLine, sizeof(firstLine), fptr) != NULL)
    {
        sscanf(firstLine, "Number of Spells: %d", &numberOfSpells);
    }
    else
    {
        perror("Error reading the first line");
        fclose(fptr);
        return;
    }

    for (int i = 0; i < numberOfSpells; i++)
    {
        fscanf(fptr, "%s", spells[i]);
        insert(head, spells[i]);
    }

    fclose(fptr);
}
// 3. DISPLAYS THE SPELLS AS A TABLE (5 WORDS PER LINE)
void displaySpells(char spells[][MAX_SPELL_LENGTH], int numberOfSpells)
{
    special_print("\nHere is the list of Spells... Choose wisely:\n");
    for (int i = 0; i < numberOfSpells; i++)
    {
        printf("%-20s", spells[i]);                      // Using width to implement aligned columns
        if ((i + 1) % 5 == 0 || i == numberOfSpells - 1) // Because 5 words per line or last word
        {
            printf("\n");
        }
    }
}

// 6. CHECKS IF A SPELL IS VALID (IF IT EXISTS IN THE FILE)
int isSpellValid(char spell[], char spells[][MAX_SPELL_LENGTH], int numberOfSpells)
{
    for (int i = 0; i < numberOfSpells; i++)
    {
        if (strcmp(spell, spells[i]) == 0)
        {
            return 1; // Spell is valid
        }
    }
    return 0; // Spell is not valid
}

// 6. CHECKS IF A SPELL STARTING WITH THE LAST CHAR IS STILL AVAILABLE
int countOccurencies(char spells[][MAX_SPELL_LENGTH], char lastChar, int numberOfSpells)
{
    int count = 0;

    for (int i = 0; i < numberOfSpells; i++)
    {
        char *currentSpell = spells[i];
        if (currentSpell[0] == lastChar)
        {
            count++;
        }
    }

    return count;
}

// PRINT THE CHARACTERS ONE BY ONE
void special_print(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        putchar(str[i]);
        fflush(stdout);
        // usleep(50000); // CONTROLS THE SPEED
        i++;
    }
}

// PRINT THE CHARACTERS ONE BY ONE (slowly)
void loading_print(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        putchar(str[i]);
        fflush(stdout);
        // usleep(400000); // CONTROLS THE SPEED
        i++;
    }
}

// 4 TOSSING A COIN AND SAYING WHO WILL START
int coinTossWithBot(const char *player_name, const char *difficulty)
{
    char player1_coin[6];

    int currentPlayer = 0; // To store who will start.

    special_print("\nLet's see who will start the battle...\n");

    printf("%s, pick 'heads' or 'tails': ", player_name);
    scanf("%s", player1_coin);
    while (1)
    {
        if (strcmp(player1_coin, "heads") == 0)
        {
            special_print("The bot chooses tails\n");
            break;
        }
        else if (strcmp(player1_coin, "tails") == 0)
        {
            special_print("The bot chooses heads\n");
            break;
        }
        else
        {
            special_print("Invalid. Pick between 'heads' or 'tails': ");
            scanf("%s", player1_coin);
        }
    }

    loading_print("...");

    // Randomly choose the side of the coin (heads=0, tails=1)
    srand(time(NULL));
    int coinToss = rand() % 2;

    if ((coinToss == 0 && strcmp(player1_coin, "heads") == 0) || (coinToss == 1 && strcmp(player1_coin, "tails") == 0))
    {
        printf("\nYou are going to start.\n\n", player_name);
    }
    else
    {
        special_print("\nThe bot is going to start.\n\n");
        currentPlayer = 1;
    }

    return currentPlayer;
}

int easyBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells)
{
}

int mediumBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, int chosenWords[], char winningWords[MAX_SPELLS][MAX_WORD_LENGTH], int *count)
{
   
    int validSpells[MAX_SPELLS];
    int validCount = 0;
    
    for (int i = 0; i < numberOfSpells; i++)
    {
        if (spells[i][0] == lastChar && chosenWords[i] == 0)
        {
            validSpells[validCount++] = i;
        }
    }

    // try choosing a winning word based on the last char
    for (int i = 0; i < *count; i++)
    {
        if (winningWords[i][0] == lastChar && chosenWords[i] ==0)
        {
            // mark as chosen so not used later
            chosenWords[i] = 1;
            return i;
        }
    }

    // if no winning word is available, choose a valid spell
    for (int i = 0; i < validCount; i++)
    {
        chosenWords[validSpells[i]] = 1;
        return validSpells[i];
    }
    return -1; // no valid move found 
}


// int hardBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, int currentplayer, struct Trie *head)
// {
//     int move = 0;
//     char missingLetters[26];
//     struct Trie *head = getNewTrieNode();
//     storeWords(head, spells, numberOfSpells);
//     int missingCount = 0;
//     findMissingAlphabets(head, missingLetters, &missingCount);
//     char *winning_Words[];
//     findWordWithMissingCharacter();
//     if (currentplayer == 1)
//     {
//         if (winning_Words != NULL)
//         {
//             const char *WORD[] = winning_Words[0];
//             for (int i = 0; i < sizeof(spells); i++)
//             {
//                 if (strcmp(spells[i], WORD) == 0)
//                     move = i;
//             }
//         }
//         else
//         {
//         }
//         return move;
//     }
//     else
//     {
//     }
// }
