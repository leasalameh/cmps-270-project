/*our github repo: cmps-270-project (username: leasalameh)

Method: getNewTrieNode
 Signature: struct Trie *getNewTrieNode()
 Requires: None
 Effects:
   - Allocates memory for a new Trie node and initializes its fields.
   - Returns a pointer to the newly created Trie node.
   - The isLeaf field is set to 0 (indicating the node is not a leaf).
   - The character array is initialized with NULL pointers for each character in the alphabet.
        (Assuming ALPHABET_SIZE is the size of the character array)

Method: insert
 Signature: void insert(struct Trie *head, char *str)
 Requires:
   - a pointer to the head of a Trie data structure.
   - a string containing the word to be inserted into the Trie.
 Effects:
   - Inserts the given word into the Trie represented by the provided head.
   - If the characters of the word are not present in the Trie, creates new Trie nodes as needed.
   - Marks the last node corresponding to the last character of the word as a leaf node.
   - Uses the getNewTrieNode() function to allocate memory for new Trie nodes.
   - Prints an error message to stderr and exits with EXIT_FAILURE if memory allocation fails.

Method: search
 Signature: int search(struct Trie *head, char *str)
 Requires:
   - head is a pointer to the head of a Trie data structure.
   - str is a null-terminated string representing the word to be searched in the Trie.
 Effects:
   - Returns 0 if the Trie is empty or the word is not found.
   - Returns 1 if the word is found in the Trie.
   - Traverses the Trie to find the given word, returning 1 only if the entire word is present.
   - If the Trie is empty or the path in the Trie corresponding to the word is incomplete, returns 0.
 Note:
   - The Trie data structure is not modified by this function.
   - The caller is responsible for ensuring that the Trie is properly initialized before calling this method.

Method: hasChildren
 Signature: int hasChildren(struct Trie *curr)
 Requires:
   - curr is a pointer to a Trie node.
 Effects:
   - Returns 1 if the given Trie node has at least one child (non-NULL pointer).
   - Returns 0 if the Trie node has no children (all character pointers are NULL).
 Note:
   - The method checks if there are any child nodes for the given Trie node.
   - It is particularly useful in determining if a Trie node is a leaf node.
   - The caller is responsible for ensuring that the Trie node is valid before calling this method.

Method: deletion
 Signature: int deletion(struct Trie **curr, char *str)
 Requires:
   - curr is a pointer to a pointer to a Trie node.
   - str is a null-terminated string representing the word to be deleted from the Trie.
 Effects:
   - Returns 1 if the word is successfully deleted from the Trie.
   - Returns 0 if the Trie is empty or the word is not found.
   - Recursively traverses the Trie to delete the specified word.
   - Unmarks leaf nodes without deleting them to maintain the Trie structure.
   - Deletes non-leaf nodes that have no children.
   - Frees memory for deleted nodes.

Method: findMissingAlphabets
 Signature: void findMissingAlphabets(struct Trie *root, char missingAlphabets[], int *missingCount)
 Requires:
   - root is a pointer to the root of a Trie data structure.
   - missingAlphabets is an array to store missing alphabets (characters not present in the Trie).
   - missingCount is a pointer to an integer that stores the count of missing alphabets.
 Effects:
   - Finds and populates the missingAlphabets array with characters (a to z) not present in the Trie.
   - Updates the missingCount variable with the count of missing alphabets.

Method: findWinningWords
 Signature: void findWinningWords(struct Trie *node, const char *suffix, const char *missingLetters, char winningWords[MAX_SPELLS][MAX_SPELL_LENGTH], int *count)
 Requires:
   - node is a pointer to a Trie node.
   - suffix is a null-terminated string representing the current word formed during the traversal.
   - missingLetters is a null-terminated string containing the letters that need to be present in the word.
   - winningWords is a 2D array to store winning words.
   - count is a pointer to an integer that stores the count of winning words.
 Effects:
   - Traverses the Trie to find words that meet the criteria for winning.
   - Appends winning words to the winningWords array.
   - Updates the count variable with the number of winning words found.

Method: findWordsStartingWith
 Signature: void findWordsStartingWith(struct Trie *node, const char *prefix, char startingChar, char words[MAX_SPELLS][MAX_SPELL_LENGTH], int *count)
 Requires:
   - node is a pointer to a Trie node.
   - prefix is a null-terminated string representing the current word formed during the traversal.
   - startingChar is the character that the words must start with.
   - words is a 2D array to store words starting with the specified character.
   - count is a pointer to an integer that stores the count of words found.
 Effects:
   - Traverses the Trie to find words that start with the specified character.
   - Appends the found words to the words array.
   - Updates the count variable with the number of words found.

Method: readSpells
 Signature: int readSpells(char spells[][MAX_SPELL_LENGTH])
 Requires:
   - spells is a 2D array to store spell names, with each row having a maximum length of MAX_SPELL_LENGTH.
   - "spells.txt" is a text file containing spell names, and the first line indicates the number of spells.
 Effects:
   - Reads spell names from "spells.txt" and stores them in the spells array.
   - Returns the number of spells read from the file.
   - If the file cannot be opened, returns 0.

Method: storeWords
 Signature: void storeWords(struct Trie *head, char spells[][MAX_SPELL_LENGTH], int numberOfSpells)
 Requires:
   - head; a pointer to the head of a Trie data structure.
   - spells is a 2D array containing spell names, with each row having a maximum length of MAX_SPELL_LENGTH.
   - "spells.txt" text file
   - numberOfSpells; the number of spells to read and store from the file.
 Effects:
   - Reads spell names from "spells.txt" and inserts them into the Trie data structure.
   - Uses the insert method to add each spell to the Trie.
   - Prints an error message and returns if the file cannot be opened or if there is an error reading the first line.

Method: displaySpells
 Signature: void displaySpells(char spells[][MAX_SPELL_LENGTH], int numberOfSpells)
 Requires:
   - 2D array containing spell names, with each row having a maximum length of MAX_SPELL_LENGTH.
   - the number of spells to display.
 Effects:
   - Prints the list of spells to the console in aligned columns, with 5 spells per line.
   - Uses the special_print function for a formatted display.

Method: isSpellValid
 Signature: int isSpellValid(char spell[], char spells[][MAX_SPELL_LENGTH], int numberOfSpells)
 Requires:
   - a string representing the spell to be validated.
   - a 2D array containing valid spell names, with each row having a maximum length of MAX_SPELL_LENGTH.
   - the number of valid spells.
 Effects:
   - Returns 1 if the provided spell is found in the list of valid spells; otherwise, returns 0.

Method: CountOccurencies
 Signature: int countOccurencies(char spells[][MAX_SPELL_LENGTH], char lastChar, int numberOfSpells)
 Requires:
   - a 2D array containing spell names, with each row having a maximum length of MAX_SPELL_LENGTH.
   - character to be matched with the first character of each spell.
   - total number of spells in the array.
 Effects:
   - Returns the count of spells in the array that start with the specified lastChar.

Method: countOccurencesInTrie
 Signature: int countOccurrencesInTrie(struct Trie *node, char startChar)
 Requires:
   - a pointer to a Trie node.
   - character to be matched with the first character of each word in the Trie.
 Effects:
   - Returns the count of words in the Trie that start with the specified character.
   - If startChar is '\0', counts all words in the Trie.

Method: countWordsStartingWithEachLetter
 Signature: void countWordsStartingWithEachLetter(struct Trie *node, int *letterCounts)
 Requires:
   - a pointer to a Trie node.
   - an array of integers to store the count of words starting with each letter of the alphabet.
 Effects:
   - Populates the letterCounts array with the count of words starting with each letter of the alphabet.
   - Uses the findWordsStartingWith method to find words starting with each letter.

Method:special_print
 Signature: void special_print(const char *str)
 Requires:
   - a string needs to be printed.
 Effects:
   - Prints each character of the string with a delay, giving a special printing effect.
   - Uses putchar to print each character individually.
   - Uses fflush(stdout) to ensure immediate display of each character.
   - Uses usleep(60000) to control the speed of printing.

Method: loading_print
 Signature: void loading_print(const char *str)
 Requires:
   - a string needs to be printed.
 Effects:
   - Prints each character of the string with a loading effect, introducing a delay between each character.
   - Uses putchar to print each character individually.
   - Uses fflush(stdout) to ensure immediate display of each character.
   - Uses usleep(600000) to control the speed of printing, simulating a loading effect.

Method: cointTossWithBot
 Signature: int coinTossWithBot(const char *player_name, const char *difficulty)
 Requires:
   - a pointer to a string representing the player's name.
   - is a pointer to a string representing the difficulty level.
 Effects:
   - Does a coin toss to determine the starting player between the human player and the bot.
   - Prompts the player to choose 'heads' or 'tails'.
   - Generates a random coin toss result.
   - Prints the bot's choice based on the coin toss.
   - Returns 0 if the human player starts, and 1 if the bot starts.

Method: easyBot
 Signature: int easyBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, int startingPlayer, struct Trie *head, int sum)

Requires:
  - a character that the generated word should start with.
  - a 2D array containing spell names, with each row having a maximum length of MAX_SPELL_LENGTH.
  - the total number of spells in the array.
  - an integer representing the player who starts (0 for human, 1 for bot).
  - a pointer to the head of a Trie data structure.
  - the total count of words in the trie.

Effects:
  - If the starting player is the bot, returns a random move index. generates a word starting with lastChar and returns its index.
  - If the starting player is not the bot, take last character and find words starting with this character and compare it

Method: mediumBot
 Signature: int mediumBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, int startingPlayer, struct Trie *head, int sum)

Requires:
  - a character that the generated word should start with.
  - a 2D array containing spell names, with each row having a maximum length of MAX_SPELL_LENGTH.
  - the total number of spells in the array.
  - startingPlayer is an integer representing the player who starts (0 for human, 1 for bot).
  - a pointer to the head of a Trie data structure.
  - sum is the total number of words in the trie

Effects:
  - If the starting player is the bot, generates a word to potentially win the game and returns its index.
  - If the starting player is the bot, but there are no winning words, implement to the easyBot strategy.
  - If the starting player is not the bot, check if last character of the input matches one of the first character of a winning word,
 - If the starting player is not the bot and there is no winning words, implement the easy bot.

Method: hardBot
Signature: hardBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, int startingPlayer, struct Trie *head, int sum)

Requires:
  -the lastChar parameter must be a valid character.
  -the spells array must contain valid strings.
  -the numberOfSpells parameter must be a valid positive integer.
  -the startingPlayer parameter must be either 0 or 1.
  -the head parameter must point to a valid Trie structure.

Effects:
  -Modifies the move variable to store the index of the chosen spell in the spells array.
  -Determine the optimal move for the bot based on the current game state, the opponent's last move (lastChar), and the available spells.
  -Depending on the game situation, the bot may prioritize certain types of words or letters, and the final move reflects the outcome of these strategic considerations.
*/

/* TEST CASES:
EASY BOT: our easy bot plays like a normal player, enters a valid spell that is not repeated.
    test cases:
    if bot starts: (we need startingplayer = 1 && difficulty = easy)
    expected output: the first word of the file (accio)

    if bot does not start: (startingplayer = 0)
        -test if bot repeats a word
            we need to keep giving the bot words that end with a certain character.
            if bot looses without repeating a word (runs out of spells), it works correctly.
        -test if bot uses the correct starting letter
            in the main, if bot uses wrong character, invalid spell is printed. to test we
            give the bot any word and we see if it last char matches bot move.
        - test if bot does not use the correct starting letter:
            it should be detected in the main


MEDIUM BOT: our medium bot plays like the easy bot, but with a twist. It has an array of Winning Words
    that it should be using (if it exists) in 2 cases: 1- if he starts the game, 2- if the last char of the
    previous spell cast matches the first char of one of the Winning Words (if he does not satisfy these
    conditions, medium bot will act like the easy bot).
    test cases:
    medium Test-Case:
    in the mediumBot, the only difference with the easyBot is the winning word array; the bot has to enter a valid spell and a non repetitive one, but there is 2 cases:
    1. the bot starts so he enters immediatly a winning word and wins.
    2. if the player starts and the last character is equal to the first character of a winning word, the bot wins.
    Test-cases:
    1. The bot starts:
    -enter a winning word --> bot wins
    -if there are no winning words -->enters a valid spell
    -if there are no winninf words --> enters a non valid spell

    2. the player starts:
    -if last and first character of winning word matches, bot ennters a winning word --> bot wins
    -if it doesn't, the bot enters a valid spell
    -if it doesn't, the bot enters a repeated word --> player wins
    -if it doesn't, the bot enters a word that does not match -->player wins


HARD BOT: our hard bot has the winning move array of the medium bot, but it has 5 cases:
    case 1: bot starts and there is a winning move array:
        expected output, winning word. test case: (starting player = 1, difficulty = hard,
        count of winning words>0): bot wins
    case 2: bot starts and there is no winning move array:
        - count number of words per starting letters if count = 2 AND one of the words starts and ends with the same letter, use it.
        - choose a Startingletter that has an odd number of words and ending letter that has even number of words.
        - choose a Startingletter that has an odd number of words and ending letter that has odd number of words.
        - choose a Startingletter that has an even number of words and ending letter that has even number of words.
        - choose a Startingletter that has an even number of words and ending letter that has odd number of words.
        - choose a random spell
    case 3:
        - if there is winning word and player starts and winning word first letter matches last char of bot options
        --> choose a word that starts with valid character and ends with a winning word letter
    case 4:
        - if there is a winning word and player starts but winning word first letter does not match:
            choose a word that will result in having a winning word (force the move of the player)
    case 5:
        - if player starts and no winning word,

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ALPHABET_SIZE 26     // Define the character size
#define MAX_SPELLS 100       // Maximum number of spells
#define MAX_SPELL_LENGTH 100 // Maximum length of a spell

// Data structure to store a Trie node
struct Trie
{
    struct Trie *character[ALPHABET_SIZE];
    int isLeaf; // 1 when the node is a leaf node
};

// Function that creates a new Trie node with default values
struct Trie *getNewTrieNode()
{
    struct Trie *node = (struct Trie *)malloc(sizeof(struct Trie));
    node->isLeaf = 0;
    if (node)
    {
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            node->character[i] = NULL;
        }
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

// Count occurrences of words starting with each letter in the Trie
void countWordsStartingWithEachLetter(struct Trie *node, int *letterCounts)
{
    int count = 0;
    int previous = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        char words[MAX_SPELLS][MAX_SPELL_LENGTH];
        char c = i + 'a';
        findWordsStartingWith(node, "", c, words, &count);
        if (count > 0)
        {
            letterCounts[i] = count - previous;
            previous += letterCounts[i];
        }
    }
}

// Prints characters one by one to simulate a special effect
void special_print(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        putchar(str[i]);
        fflush(stdout);
        usleep(60000); // CONTROLS THE SPEED
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

int easyBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, int startingPlayer, struct Trie *head, int sum)
{
    int move = 0;
    if (startingPlayer == 1 && sum == numberOfSpells)
    {
        return rand() % numberOfSpells;
    }
    else
    {
        char words_starting_with_lastChar[MAX_SPELLS][MAX_SPELL_LENGTH];
        int countOf_startingWords = 0;
        findWordsStartingWith(head, "", lastChar, words_starting_with_lastChar, &countOf_startingWords);

        for (int i = 0; i < countOf_startingWords; i++)
        {
            for (int j = 0; j < numberOfSpells; j++)
            {
                if (strcmp(words_starting_with_lastChar[i], spells[j]) == 0)
                {
                    move = j;
                    break;
                }
            }
        }
        return move;
    }
    return 0;
}

int mediumBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, int startingPlayer, struct Trie *head, int sum)
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

    if (startingPlayer == 1 && count > 0 && sum == numberOfSpells)
    {
        const char *WORD = winningWords[0];
        for (int i = 0; i < numberOfSpells; i++)
        {
            // Check if the current spell is equal to WORD
            if (strcmp(spells[i], WORD) == 0)
            {
                // If a match is found, set the move variable to the current index and exit the loop
                move = i;
                break;
            }
        }
        return move;
    }

    else if (startingPlayer == 1 && count == 0 && sum == numberOfSpells)
    {
        return easyBot(lastChar, spells, numberOfSpells, startingPlayer, head, sum);
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
                        move = j;
                        break;
                    }
                }
            }
            return move;
        }
        else
        {
            return easyBot(lastChar, spells, numberOfSpells, startingPlayer, head, sum);
        }
    }
}

int hardBot(char lastChar, char spells[][MAX_SPELL_LENGTH], int numberOfSpells, int startingPlayer, struct Trie *head, int sum)
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

    if (startingPlayer == 1 && count > 0 && sum == numberOfSpells)
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

    else if (startingPlayer == 1 && count == 0 && sum == numberOfSpells)
    {
        int letterCounts[ALPHABET_SIZE] = {0};

        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            letterCounts[i] = 0;
        }

        countWordsStartingWithEachLetter(head, letterCounts);

        char twoWords[MAX_SPELLS][MAX_SPELL_LENGTH];
        char StartingChar, endingChar;
        int MatchCount = 0;
        char MoveOfBot[MAX_SPELL_LENGTH];
        for (int i = 0; i < ALPHABET_SIZE; i++)
        {
            int wordcount = 0;
            if (letterCounts[i] == 2)
            {
                char ch = i + 'a';
                findWordsStartingWith(head, "", ch, twoWords, &wordcount);

                for (int i = 0; i < wordcount; i++)
                {
                    const char *word = twoWords[i];
                    StartingChar = word[0];
                    endingChar = word[strlen(word) - 1];
                    if (StartingChar == endingChar)
                    {
                        strcpy(MoveOfBot, twoWords[i]);
                        MatchCount++;
                    }
                }
            }
        }
        if (MatchCount == 1)
        {
            for (int i = 0; i < numberOfSpells; i++)
            {
                if (strcmp(spells[i], MoveOfBot) == 0)
                {
                    move = i;
                    break;
                }
            }
            return move;
        }

        // choose word with odd count but it should end with word with even count
        // Choose a word with specific starting and ending letter counts
        int oddStartEvenEnd = -1, oddStartOddEnd = -1, evenStartOddEnd = -1, evenStartEvenEnd = -1;

        for (int i = 0; i < numberOfSpells; i++)
        {
            const char *word = spells[i];
            int startCount = countOccurrencesInTrie(head, word[0]);
            int endCount = countOccurrencesInTrie(head, word[strlen(word) - 1]);

            if (startCount % 2 == 1 && endCount % 2 == 0)
            {
                oddStartEvenEnd = i;
                break;
            }
            else if (startCount % 2 == 1 && endCount % 2 == 1)
            {
                oddStartOddEnd = i;
            }
            else if (startCount % 2 == 0 && endCount % 2 == 0)
            {
                evenStartEvenEnd = i;
            }
            else if (startCount % 2 == 0 && endCount % 2 == 1)
            {
                evenStartOddEnd = i;
            }
        }

        // Prioritize the selection based on the conditions
        if (oddStartEvenEnd != -1)
        {
            move = oddStartEvenEnd;
        }
        else if (oddStartOddEnd != -1)
        {
            move = oddStartOddEnd;
        }
        else if (evenStartEvenEnd != -1)
        {
            move = evenStartEvenEnd;
        }
        else if (evenStartOddEnd != -1)
        {
            move = evenStartOddEnd;
        }
        else
        {
            // No word found with the specified conditions, choose any valid word
            move = rand() % numberOfSpells;
        }

        return move;
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
            char startingLetter = lastChar;
            char words_starting_with_lastChar[MAX_SPELLS][MAX_SPELL_LENGTH];
            int countOf_startingWords = 0;
            findWordsStartingWith(head, "", lastChar, words_starting_with_lastChar, &countOf_startingWords);

            // Choose a word with specific starting and ending letter counts
            int StartEvenEnd = -1, StartOddEnd = -1;

            for (int i = 0; i < countOf_startingWords; i++)
            {
                const char *word = words_starting_with_lastChar[i];
                int endCount = countOccurrencesInTrie(head, word[strlen(word) - 1]);

                if (endCount % 2 == 0)
                {
                    StartEvenEnd = i;
                    break;
                }
                else if (endCount % 2 == 1)
                {
                    StartOddEnd = i;
                }
            }

            // Prioritize the selection based on the conditions
            if (StartEvenEnd != -1)
            {
                move = StartEvenEnd;
            }
            else if (StartOddEnd != -1)
            {
                move = StartOddEnd;
            }
            else
            {
                // No word found with the specified conditions, choose any valid word
                move = rand() % numberOfSpells;
            }

            return move;
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
            char moves[MAX_SPELLS][MAX_SPELL_LENGTH];
            int moveCount = 0;

            while (!gameOver)
            {

                int letterCounts[ALPHABET_SIZE] = {0};

                for (int i = 0; i < ALPHABET_SIZE; i++)
                {
                    letterCounts[i] = 0;
                }

                countWordsStartingWithEachLetter(head, letterCounts);
                int sum;

                for (int i = 0; i < ALPHABET_SIZE; i++)
                {
                    sum += letterCounts[i];
                }

                if (currentPlayer == 0)
                {
                    printf("%s chooses: ", player1_name);
                    scanf("%s", currentSpell);
                }
                else if (currentPlayer == 1)
                {
                    if (strcmp("easy", difficulty) == 0)
                    {
                        strcpy(currentSpell, spells[easyBot(lastChar, spells, numberOfSpells, startingPlayer, head, sum)]);
                    }
                    else if (strcmp("medium", difficulty) == 0)
                    {
                        strcpy(currentSpell, spells[mediumBot(lastChar, spells, numberOfSpells, startingPlayer, head, sum)]);
                    }
                    else if (strcmp("hard", difficulty) == 0)
                    {
                        strcpy(currentSpell, spells[hardBot(lastChar, spells, numberOfSpells, startingPlayer, head, sum)]);
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