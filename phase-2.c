#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ALPHABET_SIZE 26     // Define the character size
#define MAX_SPELLS 100       // Maximum number of spells
#define MAX_MOVES 100        // Maximum number of moves to check for repetition later
#define MAX_SPELL_LENGTH 100 // Maximum length of a spell

// Data structure to store a Trie node
struct Trie
{
    int isLeaf; // 1 when the node is a leaf node
    struct Trie *character[ALPHABET_SIZE];
};

// Function that creates a new Trie node with default values
struct Trie *getNewTrieNode()
{
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->isLeaf = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
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

// Iterative function to search a string in a Trie. Returns 1 if the string is found in the Trie; and 0 otherwise.
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
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (curr->character[i])
        {
            return 1; // child found
        }
    }

    return 0;
}

int deletion(struct Trie **curr, char *str)
{
    // Base case: If the Trie is empty
    if (*curr == NULL)
    {
        printf("DEBUG: Trie is empty\n");
        return 0;
    }

    // If the end of the string is not reached
    if (*str)
    {
        int childIndex = *str - 'a';

        // Recur for the node corresponding to the next character in the string
        if ((*curr)->character[childIndex] != NULL &&
            deletion(&((*curr)->character[childIndex]), str + 1))
        {
            // After the recursive call, delete the current node if it is non-leaf
            if (!hasChildren(*curr) && !(*curr)->isLeaf)
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
        }
    }

    // If the end of the string is reached
    if (*str == '\0')
    {
        // If the current node is a leaf node
        if ((*curr)->isLeaf)
        {
            // Unmark it as a leaf node (do not delete)
            (*curr)->isLeaf = 0;

            // If the current node has no children, delete it
            if (!hasChildren(*curr))
            {
                free(*curr);
                (*curr) = NULL;
                return 1;
            }
        }
    }

    return 0;
}

// Finds missing alphabets in the Trie and stores them in an array
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

// Finds winning words in the Trie based on missing letters
void findWinningWords(struct Trie *node, const char *suffix, const char *missingLetters, char winningWords[MAX_SPELLS][MAX_SPELL_LENGTH], int *count)
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
            char newSuffix[MAX_SPELL_LENGTH];
            strcpy(newSuffix, suffix);
            strncat(newSuffix, (char[]){(char)(i + 'a')}, 1);
            findWinningWords(node->character[i], newSuffix, missingLetters, winningWords, count);
        }
    }
}

void findWordsStartingWith(struct Trie *node, const char *prefix, char startingChar, char words[MAX_SPELLS][MAX_SPELL_LENGTH], int *count)
{
    if (node == NULL)
    {
        return;
    }

    if (node->isLeaf && prefix[0] == startingChar)
    {
        strcpy(words[*count], prefix);
        (*count)++;
    }

    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (node->character[i])
        {
            char newPrefix[MAX_SPELL_LENGTH];
            strcpy(newPrefix, prefix);
            strncat(newPrefix, (char[]){(char)(i + 'a')}, 1);
            findWordsStartingWith(node->character[i], newPrefix, startingChar, words, count);
        }
    }
}

// Reads spells from file "spells.txt", returns the number of spells, and populates the spells array
int readSpells(char spells[][MAX_SPELL_LENGTH])
{
    FILE *fptr = fopen("spells.txt", "r"); // A pointer to our file that we open and read (r=read mode)

    if (fptr == NULL)
    {
        return 0;
    }

    char firstLine[100];         // Reading first line as a string => Number of Spells: 78, will be stored in firstLine
    fgets(firstLine, 100, fptr); // 4=> max number of characters to read from this line

    int numberOfSpells = atoi(firstLine); // Converting 78 into an integer using atoi

    for (int i = 0; i < numberOfSpells; i++)
    {
        fscanf(fptr, "%s", spells[i]);
    }

    fclose(fptr);
    return numberOfSpells;
}

// Stores words from the file in the Trie data structure
// Reads spells from "spells.txt" and inserts them into the Trie
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

// Displays spells in a formatted table (5 words per line)
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

// Checks if a spell is valid (exists in the list of spells). Returns 1 if the spell is valid, 0 otherwise
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

// Counts occurences of spells in the list starting with a given character
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

// Recursive function to count occurrences of words starting with a specific character in the Trie
int countOccurrencesInTrie(struct Trie *node, char startChar)
{
    if (node == NULL)
        return 0;

    int count = 0;

    if (node->isLeaf && startChar == '\0')
        count++; // Count the leaf node itself

    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (node->character[i])
        {
            char nextChar = i + 'a';
            if (startChar == '\0' || startChar == nextChar)
            {
                // Recursively count occurrences in the child node
                count += countOccurrencesInTrie(node->character[i], '\0');
            }
        }
    }

    return count;
}

// Prints characters one by one to simulate a special effect
void special_print(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        putchar(str[i]);
        fflush(stdout);
        //usleep(60000); // CONTROLS THE SPEED
        i++;
    }
}

// Prints characters one by one slowly to simulate loading
void loading_print(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        putchar(str[i]);
        fflush(stdout);
        usleep(600000); // CONTROLS THE SPEED
        i++;
    }
}

// Tosses a coin and returns the player (0=player or 1=bot) who starts
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
        special_print("\nYou are going to start.\n\n");
    }
    else
    {
        special_print("\nBob the bot is going to start.\n\n");
        currentPlayer = 1;
    }

    return currentPlayer;
}

int easyBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells)
{
    return 0;
}

int mediumBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells)
{
    return 0;
}

int hardBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, int startingPlayer, struct Trie *head)
{
    // move = index of the spell chosen by the bot (spells[hardbot()] in the main)
    int move = 0;
    char missingLetters[26];
    // find,  if there are, letters of the alphabet that are not used to start a word.
    int missingCount = 0;
    findMissingAlphabets(head, missingLetters, &missingCount);
    // array of winning words, if there are (they end with the missing letters)
    char winningWords[MAX_SPELLS][MAX_SPELL_LENGTH];
    int count = 0;
    findWinningWords(head, "", missingLetters, winningWords, &count);
    // match or no match (lastChar and 1stchar of winning word)0:false,1 true;
    int match = 0;

    if (startingPlayer == 1 && count > 0)
    {
        const char *WORD = winningWords[0];
        for (int i = 0; i < numberOfSpells; i++)
        {
            if (strcmp(spells[i], WORD) == 0)
            {
                move = i;
                break;
            }
        }
        return move;
    }
    else if (startingPlayer == 1 && count == 0)
    {
    }
    else
    {
        if (count > 0)
        {
            for (int i = 0; i < count; i++)
            {
                const char *possibility = winningWords[i];
                for (int j = 0; j < numberOfSpells; j++)
                {
                    if (possibility[0] == lastChar && strcmp(spells[j], possibility) == 0)
                    {
                        match = 1;
                        move = j;
                        break;
                    }
                }
            }
            if (match == 0)
            {
                char winningLetters[26];

                for (int i = 0; i < count; i++)
                {
                    const char *WIN = winningWords[i];
                    winningLetters[i] = WIN[0];
                }
                char words_ending_with_winning_letters[MAX_SPELLS][MAX_SPELL_LENGTH];
                int countOf_winningLetterWords = 0;
                findWinningWords(head, "", winningLetters, words_ending_with_winning_letters, &countOf_winningLetterWords);

                char words_starting_with_lastChar[MAX_SPELLS][MAX_SPELL_LENGTH];
                int countOf_startingWords = 0;
                findWordsStartingWith(head, "", lastChar, words_starting_with_lastChar, &countOf_startingWords);

                char force_player_move[MAX_SPELLS][MAX_SPELL_LENGTH];
                int countOfForcePlayerMove = 0;

                // Compare lastChar with the last character of words starting with lastChar
                // Compare lastChar with the last character of words starting with lastChar
                for (int i = 0; i < countOf_winningLetterWords; i++)
                {
                    const char *endingWord = words_ending_with_winning_letters[i];

                    for (int j = 0; j < countOf_startingWords; j++)
                    {
                        const char *startingWord = words_starting_with_lastChar[j];
                        char startingWordLastChar = startingWord[strlen(startingWord) - 1];

                        if (endingWord[0] == startingWordLastChar)
                        {
                            strcpy(force_player_move[countOfForcePlayerMove], endingWord);
                            countOfForcePlayerMove++;
                            break; // Break out of the inner loop once a match is found
                        }
                    }
                }
                // Compare lastChar with the last character of words starting with lastChar
                char maxPercentageChar = '\0';
                double maxPercentage = 0.0;

                for (int i = 0; i < countOfForcePlayerMove; i++)
                {
                    const char *LastCharOfBot = force_player_move[i];
                    char firstChar = LastCharOfBot[0];

                    int totalStartingWithFirstCharInWinningWords = countOccurencies(winningWords, firstChar, count);

                    // Count words in the Trie starting with the first character
                    int totalStartingWithFirstCharInTrie = countOccurrencesInTrie(head, firstChar) - totalStartingWithFirstCharInWinningWords;

                    // Count words in the array force_player_move starting with the first character
                    int totalInForcePlayerMove = countOccurencies(force_player_move, firstChar, countOfForcePlayerMove);

                    // Calculate the ratio
                    double ratio = (double)totalInForcePlayerMove / totalStartingWithFirstCharInTrie;

                    // Update maxPercentageChar if the current ratio is greater
                    if (ratio > maxPercentage)
                    {
                        maxPercentage = ratio;
                        maxPercentageChar = firstChar;
                    }
                }
                // Initialize the string to store the final bot move
                char finalBotMove[MAX_SPELL_LENGTH];

                // Loop over the words starting with lastChar array
                for (int i = 0; i < countOf_startingWords; i++)
                {
                    const char *startingWord = words_starting_with_lastChar[i];
                    char lastCharStartingWord = startingWord[strlen(startingWord) - 1];

                    // Compare the last character with maxPercentageChar
                    if (lastCharStartingWord == maxPercentageChar)
                    {
                        // Store the word in the final bot move
                        strcpy(finalBotMove, startingWord);
                        break; // Assuming you want to break after finding the first match
                    }
                }
                for (int i = 0; i < numberOfSpells; i++)
                {
                    if (strcmp(spells[i], finalBotMove) == 0)
                    {
                        move = i;
                        break;
                    }
                }
            }
            return move;
        }
        else
        {
        }
    }
    return 0;
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
        if (strcmp("easy", difficulty) == 0 || strcmp("medium", difficulty) == 0 || strcmp("hard", difficulty) == 0)
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
            int startingPlayer = currentPlayer;

            // play the game (player vs bot)
            int gameOver = 0;
            int winner = -1; // 0 for player 1, 1 for player 2
            char currentSpell[50];
            char lastChar = '\0'; // Initialize the last character to an arbitrary value

            // create a trie
            struct Trie *head = getNewTrieNode();

            // store the words of the file in the trie
            storeWords(head, spells, numberOfSpells);

            // Initialize moves array to store player moves
            char moves[MAX_MOVES][MAX_SPELL_LENGTH];
            int moveCount = 0;

            while (!gameOver)
            {
                if (currentPlayer == 0)
                {
                    printf("%s chooses: ", player1_name);
                    scanf("%s", currentSpell);
                }
                else if (currentPlayer == 1)
                {
                    if (strcmp("easy", difficulty) == 0)
                    {
                        strcpy(currentSpell, spells[easyBot(lastChar, spells, numberOfSpells)]);
                    }
                    else if (strcmp("medium", difficulty) == 0)
                    {
                        strcpy(currentSpell, spells[mediumBot(lastChar, spells, numberOfSpells)]);
                    }
                    else if (strcmp("hard", difficulty) == 0)
                    {
                        strcpy(currentSpell, spells[hardBot(lastChar, spells, numberOfSpells, startingPlayer, head)]);
                    }
                    printf("Bob chooses: %s\n", currentSpell);
                }
                if (!isSpellValid(currentSpell, spells, numberOfSpells)) // Checking if spell is valid
                {
                    if (currentPlayer == 0)
                    {
                        special_print("\nInvalid spell...  You cast a spell not in the list... Bob wins.\n");
                    }
                    else
                    {
                        special_print("\nInvalid spell... Bob cast a spell not in the list... YOU WIN!!\n");
                    }
                    winner = 1 - currentPlayer; // Switch winner
                    gameOver = 1;
                }
                else if (moveCount > 0 && currentSpell[0] != lastChar) // Opponent chooses a spell in which the first character doesn't match the last character of the previous spell
                {
                    if (currentPlayer == 0)
                    {
                        special_print("\nInvalid spell...  The first character of your spell does not match the last character of Bob's last spell... Bob wins.\n");
                    }
                    else
                    {
                        special_print("\nInvalid spell... The first character of Bob's spell does not match the last character of your spell... YOU WIN!!\n");
                    }
                    winner = 1 - currentPlayer; // Switch winner
                    gameOver = 1;
                }
                else
                {
                    // Check if the current player repeated a spell
                    for (int i = 0; i < moveCount; i++)
                    {
                        if (strcmp(currentSpell, moves[i]) == 0)
                        {
                            if (currentPlayer == 0)
                            {
                                special_print("\nInvalid spell...  You repeated a previously cast spell... Bob wins.\n");
                            }
                            else
                            {
                                special_print("\nInvalid spell... Bob repeated a previously cast spell... YOU WIN!!\n");
                            }
                            winner = 1 - currentPlayer; // Switch winner
                            gameOver = 1;
                            break;
                        }
                    }

                    // Store the current player's move
                    strcpy(moves[moveCount], currentSpell);
                    moveCount++;

                    // Update the last character
                    lastChar = currentSpell[strlen(currentSpell) - 1];

                    // Check if the opponent has no valid spells left BEFORE SWITCHING PLAYERS
                    int words_USED_startingWithLastChar = countOccurencies(moves, lastChar, moveCount);          // Count how many spells start with the last character in the MOVES (already casted spells)
                    int words_inTOTAL_startingWithLastChar = countOccurencies(spells, lastChar, numberOfSpells); // Count how many spells start with the last character in the file (total number of spells)
                    if (words_USED_startingWithLastChar == words_inTOTAL_startingWithLastChar)                   // If the number is = then opponent wins, no switching players (there are no available words left that start with last char)
                    {
                        if (currentPlayer == 0)
                        {
                            special_print("\nBob has no valid spells left. YOU WIN!!\n");
                        }
                        else
                        {
                            special_print("\nYou have no valid spells left. Bob wins.\n");
                        }
                        winner = 1 - currentPlayer; // Switch winner
                        gameOver = 1;
                    }
                    else
                    {
                        currentPlayer = 1 - currentPlayer;
                    }
                }
                if (head != NULL)
                {
                    int deleted = deletion(&head, currentSpell);
                }
            }
            // 7. ENDING THE GAME (NO TIES) AND ANNOUNCING THE WINNER
            if (winner == 1)
            {
                printf("\nGAME OVER...\nCONGRATULATIONS! You are the SPELL MASTER!\n");
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