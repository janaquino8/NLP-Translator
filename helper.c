#include "header.h"

/*
    printLine 
    
    prints an asterisk line depending on the length given
    @param n length of the line
    @return N/A

    Pre-condition: n is greater than 0
*/
void
printLine(int n)
{
    int i;
    
    printf("\n");

    // Prints a line that is n asterisks long
    for (i = 0; i < n; i++)
        printf("*");
    
    printf("\n");
}

/*
    displayMainMenu 
    
    displays the display screen of the main menu
    @param N/A
    @return N/A

    Pre-condition: N/A
*/
void
displayMainMenu()
{
    printLine(LINELEN);

    printf("Welcome to the\n");

    // Printing the NLP Translator logo
    printf(" _____  ___   ___         _______  ___________\n");
    printf("(\\\"   \\|\"  \\ |\"  |       |   __ \"\\(\"     _   \")\n");
    printf("|.\\\\   \\    |||  |       (. |__) :))__/  \\\\__/\n");
    printf("|: \\.   \\\\  ||:  |       |:  ____/    \\\\_ /\n");
    printf("|.  \\    \\. | \\  |___    (|  /        |.  |\n");
    printf("|    \\    \\ |( \\_|:  \\  /|__/ \\       \\:  |\n");
    printf(" \\___|\\____\\) \\_______)(_______)       \\__|\n\n");

    printf("Natural Language Processing Translator!\n\n");

    printf("Your one-stop app for all your personalized translating needs, from storing to file processing!\n\n");

    printf("Type any of the following [enclosed in brackets] to continue:\n");
    printf("[1] Manage Data\n");
    printf("[2] Translate\n");
    printf("[0] Exit\n");

    printLine(SLINELEN);
}

/*
    displayManageDataMenu 
    
    displays the display screen of the manage data menu
    @param N/A
    @return N/A

    Pre-condition: N/A
*/
void
displayManageDataMenu()
{
    printf(" __  __                                __  __\n");
    printf("|  \\/  | __ _ _ __   __ _  __ _  ___  |  \\/  | ___ _ __  _   _\n");
    printf("| |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ | |\\/| |/ _ \\ '_ \\| | | |\n");
    printf("| |  | | (_| | | | | (_| | (_| |  __/ | |  | |  __/ | | | |_| |\n");
    printf("|_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___| |_|  |_|\\___|_| |_|\\__,_|\n");
    printf("                          |___/\n\n");

    printf("OPTIONS:\n");
    printf("[1] Add Entry\n");
    printf("[2] Add Translations\n");
    printf("[3] Delete Entry\n");
    printf("[4] Delete Translation\n");
    printf("[5] Display All Entries\n");
    printf("[6] Search Word\n");
    printf("[7] Search Translation\n");
    printf("[8] Export\n");
    printf("[9] Import\n");
    printf("[0] Exit\n");

    printLine(SLINELEN);
}

/*
    displayTranslateMenu 
    
    displays the display screen of the translate menu
    @param N/A
    @return N/A

    Pre-condition: N/A
*/
void
displayTranslateMenu()
{
    printf(" _____                    _       _\n");
    printf("|_   _| __ __ _ _ __  ___| | __ _| |_ ___\n");
    printf("  | || '__/ _` | '_ \\/ __| |/ _` | __/ _ \\\n");
    printf("  | || | | (_| | | | \\__ \\ | (_| | ||  __/\n");
    printf("  |_||_|  \\__,_|_| |_|___/_|\\__,_|\\__\\___|\n\n");
    printf("OPTIONS:\n");
    printf("[1] Translate Text Input\n");
    printf("[2] Translate Text File\n");
    printf("[0] Exit\n");

    printLine(SLINELEN);
}

//#############################################################################################################
//#############################################################################################################

/*
    getIntSentiInput 
    
    gets the sentinel input of the user given a specific range of allowed aValues
    @param min lower boundary allowed for the input
    @param max upper boundary allowed for the input
    @param sInstruct string containing instructions to guide the user
    @return integer input of the user

    Pre-condition: nMin <= nMax; both are only one digit
*/
int 
getIntSentiInput(int nMin, int nMax, char sInstruct[])
{
    char holder, // Holds the char input of the user
         ch; // Holds the last char entered by the user
    int  nInput, // The numerical equivalent of the user input
         nCharCount; // The number of characters that the user entered

    // Loop to repeat until the input is within the boundaries
    do 
    {
        nCharCount = 0; // Initialization of nCharCount

        printf("%s", sInstruct);
        
        // Reads user input as long as the user doesn't input a new line
        do 
        {
            holder = getchar();
            if (holder != '\n')
            {
                ch = holder; // Stores the non-newline user input to ch 
                nCharCount++;
            } 
        } while (holder != '\n');
    
        nInput = ch - '0';

        // Invalid input
        if (nInput < nMin || nInput > nMax || nCharCount != 1)
            printf("Wrong input. Try again. ");
    } while (nInput < nMin || nInput > nMax || nCharCount != 1); // Checks to see if user entered an int within the range, and of only one digit

    return nInput;
}

/*
    getIntNoInput 
    
    gets the user's input of an entry or pair number
    @param nIsRedo 1 if the user may input another number after entering an invalid number; 0 otherwise
    @param sInstruct string containing instructions to guide the user
    @return a positive integer corresponding to the index of an entry or pair number (entry/pair no - 1)
    
    Pre-assumption: Input is only three digits long
*/
int
getIntNoInput(int nIsRedo, char sInstruct[])
{
    int i,
        j,
        aValues[3], // Stores the value of each entered digit
        nCharCount, // The number of digits entered
        nIsValid = 0, // Bool value denoting if the entered value is valid
        nFinalValue = 0; // The actual input of the user as an integer
    char ch; // Stores a character in the input

    // Reads the input of the user while the user's input is invalid and nIsRedo is 1
    do
    {
        nCharCount = 0; // Initialization of nCharCount

        printf("%s", sInstruct);

        // Reads until the newline
        do
        {
            scanf("%c", &ch);

            // Stores the first 3 entered digits to aValues
            if (nCharCount < 3 && ch != '\n')
                aValues[nCharCount] = ch - '0';
            
            nCharCount++;
        } while (ch != '\n');

        nCharCount--;

        // Checks to see if user entered an int within the range, and a maximum of 3 digits
        if (nCharCount >= 1 && nCharCount <= 3)
        {
            i = 0;
            
            // Ensures that the user entered digits
            while (i < nCharCount && aValues[i] >= 0 && aValues[i] <= 9)
                i++;
            
            // Runs if the input is indeed a numerical value
            if (i == nCharCount)
            {   
                // Gets the actual entry/pair number entered by the user
                for (j = 0; j < nCharCount; j++)
                {
                    nFinalValue *= 10;
                    nFinalValue += aValues[j];
                }
                nIsValid = 1;
            }
        }
    } while (!nIsValid && nIsRedo);

    return nFinalValue - 1; // Returns the index equivalent of the entry/pair number
}

/*
    getDisplaySentiInput 
    
    gets the user's char input for when using display options
    @param N/A
    @return the char input of the user (either N, P, or X)

    Pre-assumption: N/A
*/
char
getDisplaySentiInput()
{
    int nCharCount; // The number of characters that the user entered
    char ch, // Holds the last char entered by the user
         holder; // Holds the char input of the user

    // Loops until the input is within the boundaries and restrictions
    do
    {
        nCharCount = 0; // Initialization of nCharCount

        // Gets the input of the user
        printf("Enter option: ");

        do
        {
            scanf("%c", &holder);

            if (holder != '\n')
            {
                ch  = holder;
                nCharCount++;
            }
        } while (holder != '\n');
    } while ((ch != 'N' && ch != 'P' && ch != 'X') || nCharCount != 1);

    return ch; // Return the valid character input of the user
}

/*
    getShortStrInput 
    
    gets the string (Language/Translation) input of a user
    @param sInput string to store the input
    @param sInstruct string containing instructions to guide the user
    @return N/A

    Pre-condition: N/A
*/
void
getShortStrInput(char sInput[], char sInstruct[])
{
    char holder; // Holds the char input of the user
    int  nCharCount; // The number of characters that the user entered

    // Loop to repeat until the input is within the boundaries
    do 
    {
        nCharCount = 0;

        // Gets the user input
        printf("%s", sInstruct);
        
        do 
        {
            holder = getchar();

            // Copies holder to input if the character is valid
            if ((holder >= 'A' && holder <= 'Z') || (holder >= 'a' && holder <= 'z') ||
                (holder >= '0' && holder <= '9') || holder == '\'' || holder == '-' ||
                 holder == ' ') 
            {
                nCharCount++;
                if (nCharCount <= SHORT_STRMAX)
                    sInput[nCharCount - 1] = holder;
            } 
        } while (holder != '\n');

        if (nCharCount < 1 || nCharCount > SHORT_STRMAX)
            printf("Wrong input. Try again. ");
    } while (nCharCount < 1 || nCharCount > SHORT_STRMAX); 

    sInput[nCharCount] = '\0';
}

/*
    getTxtFileNameInput 
    
    gets the text filename input of a user
    @param sInput string to store the input
    @return the address of input

    Pre-condition: strlen(sInput) is less than or equal to the given size limit allocated for filenames minus the file extension
*/
void
getTxtFileNameInput(char sInput[])
{
    char holder; // Holds the char input of the user
    int  nCharCount, // The number of characters that the user entered
         nIsValid; // Bool value denoting if user input is valid

    // Loop to repeat until the input is within the boundaries
    do 
    {
        nCharCount = 0;
        nIsValid = 1;
        printf("Enter txt filename (only 'A-Z', 'a-z', '0-9', '_', '-', '()', and spaces are allowed); no need to enter '.txt': ");
        
        // Gets the user input
        do 
        {
            holder = getchar();

            if (holder != '\n' && nIsValid)
            {
                // Copies holder to input if the character is valid; else, the input is valid
                if ((holder >= 'A' && holder <= 'Z') || (holder >= 'a' && holder <= 'z') ||
                    (holder >= '0' && holder <= '9') || holder == '_' || holder == '-' ||
                    holder == '(' || holder == ')')
                {
                    nCharCount++;
                    if (nCharCount <= MED_STRMAX)
                        sInput[nCharCount - 1] = holder;
                }
                else
                    nIsValid = 0;
            } 
        } while (holder != '\n');

        // Not a valid input if nCharCount is outside boundaries
        if (nCharCount < 1 || nCharCount > MED_STRMAX - 4)
            nIsValid = 0;

        if (!nIsValid)
            printf("Wrong input. Try again. ");
    } while (!nIsValid); 

    sInput[nCharCount] = '\0';

    strcat(sInput, ".txt"); // adds '.txt' to input
}

/*
    getLongStrInput 
    
    gets the string (text) input of a user
    @param input string to store the input
    @param sInstruct string containing instructions to guide the user
    @return N/A

    Pre-condition: strlen(input) is less than or equal to the given size limit allocated for that string
*/
void
getLongStrInput(char sInput[], char sInstruct[])
{
    char holder;
    int  nCharCount;

    // Loop to repeat until the input is within the boundaries
    do 
    {
        nCharCount = 0;

        printf("%s", sInstruct);
        
        // Gets the user input of a text until the newline
        do 
        {
            holder = getchar();
            if (holder != '\n') 
            {
                nCharCount++;
                if (nCharCount <= LONG_STRMAX)
                    sInput[nCharCount - 1] = holder;
            } 
        } while (holder != '\n');

        if (nCharCount < 1 || nCharCount > LONG_STRMAX)
            printf("Invalid input. Try again. ");
    } while (nCharCount < 1 || nCharCount > LONG_STRMAX); 

    sInput[nCharCount] = '\0';
}

/*
    CleanString 
    
    lowercases the strings, then capitalizes the first character if desired
    @param nString string to be 'cleaned'
    @param nIfCapitalized 1 if first character should be capitalized; 0 otherwise
    @return N/A

    Pre-condition: strlen(nString) <= 20
*/
void
CleanString(char nString[], int nIfCapitalized)
{
    int i = 0;

    // Capitalizes the first character if it is a lowecase letter
    if (nIfCapitalized)
    {
        if (nString[i] >= 'a' && nString[i] <= 'z')
            nString[i] -= 'a' - 'A';
        i++;
    }

    // Lowercases the remaining letters
    while (nString[i] != '\0')
    {
        if (nString[i] >= 'A' && nString[i] <= 'Z')
        nString[i] += 'a' - 'A';
        i++;
    }
}

/*
    getTranslatePair 
    
    gets the translatePair input of the user
    @param N/A
    @return the input of the user

    Pre-condition: N/A
*/
struct translatePair
getTranslatePair()
{
    struct translatePair input; // Stores the language and translation input of the user

    printf("Enter a translation pair!\n\n");

    // Gets the input for the language and translation
    getShortStrInput(input.strLang, "Language: ");
    CleanString(input.strLang, 1);
    getShortStrInput(input.strTrans, "Translation: ");
    CleanString(input.strTrans, 0);

    return input;
}

//#############################################################################################################
//#############################################################################################################

/*
    displayEntry 
    
    displays the translation pairs stored in an entry
    @param entry the entry to be displayed
    @param nEntryCount the current count of the entry
    @param nEntryNo the entry number (disregarding array indexing)
    @return N/A

    Pre-condition: The entry contains at least one translation pair;
                   the entry is sorted 
*/
void
displayEntry(struct translatePair entry[], 
             int nEntryCount,
             int nEntryNo)
{
    int i;

    // Displays the entry (entry number, then the translation pairs with numbering on the right)
    printf("Entry %d", nEntryNo);
    printLine(TLINELEN);
    printf("* %-22s* %-22s*", "Language", "Translation");
    printLine(TLINELEN);

    for (i = 0; i < nEntryCount; i++)
        printf("* %-22s* %-22s%d\n", entry[i].strLang, entry[i].strTrans, i + 1);

    printLine(TLINELEN);

    printf("\n");
}

/*
    displayEntries 
    
    displays all existing entries, page-style
    @param aEntries array of the list of entries that exist
    @param aEntryCounts array of the number of translation pairs stored in each entry
    @param nNoEntries the number of existing entries 
    @param aEntryNoList array containing the entry no. of each entry in aEntries
    @return N/A

    Pre-condition: There is at least one entry that exists
*/
void
displayEntries(struct translatePair aEntries[][PAIRMAX],
               int aEntryCounts[],
               int nNoEntries,
               int aEntryNoList[])
{
    int index = 0;
    char option; // 'P', 'X', or 'N'

    // Displays entries one-by-one, able to be toggled using the valid inputs for option; runs while option != 'X'
    do
    {
        // Displaying an entry, including its entry count
        // Ternary operator checks if there's a specified entry number for the entry
        displayEntry(aEntries[index], aEntryCounts[index], aEntryNoList[0] > 0 ? aEntryNoList[index] : index + 1);
        printf("Entry count: %d\n\n", aEntryCounts[index]);
        printLine(SLINELEN);

        printf("< P  X  N >\n\n");
        printf("P - Previous\n");
        printf("X - Exit\n");
        printf("N - Next\n\n");

        // Gets user input for option
        do 
        {
            option = getDisplaySentiInput();

            // Error handling
            if (index == 0 && option == 'P')
                printf("You are already viewing the first entry.\n");
            else if (index == nNoEntries - 1 && option == 'N')
                printf("You are already viewing the last entry.\n");
        } while ((option != 'X' && option != 'P' && option != 'N') ||
                 ((index == 0 && option == 'P') || (index == nNoEntries - 1 && option == 'N')));
        
        if (option == 'P')
            index--;
        else if (option == 'N')
            index++;

    } while (option != 'X');
}

//#############################################################################################################
//#############################################################################################################

/*
    copyEntry 
    
    copies an existing entry to another entry
    @param dest array representing the destination entry
    @param origin array representing the origin entry
    @param nNoPairs the number of pairs in origin
    @return N/A
    
    Pre-condition: dest isn't initialized;
                   origin has at least one existing translation pair and is sorted
*/
void
copyEntry(struct translatePair dest[], 
          struct translatePair origin[],
          int nNoPairs)
{
    int i;

    // Copies translate pairs in origin to dest
    for (i = 0; i < PAIRMAX; i++)
    {
        if (i < nNoPairs)
            dest[i] = origin[i];
        else
        {
            strcpy(dest[i].strLang, "");
            strcpy(dest[i].strTrans, ""); 
        }    
    }
}

//#############################################################################################################
//#############################################################################################################

/*
    pairComparison compares two translate pairs and returns a value depending on their similarities
    @param pair1 the first pair
    @param pair2 the second pair
    @return 1 if only the languages match, 2 if only the translations match, 3 if both and 0 if neither
    Pre-condition: strLang of each pair holds a non-garbage value
*/
int
pairComparison(struct translatePair pair1,
               struct translatePair pair2)
{
    int i = 0; // Tracks the similarities of the pairs

    // If the languages match
    if (strcmp(pair1.strLang, pair2.strLang) == 0)
        i += 1;
    
    // If the translation words match
    if (strcmp(pair1.strTrans, pair2.strTrans) == 0)
        i += 2;
    
    return i;
}

/*
    search 
    
    searches the entries for the first instance of a target 
        (whether language, translation, or both), starting from a given entry and pair 
    @param aEntries array of the list of entries that exist
    @param aEntryCounts array of the number of translation pairs stored in each entry
    @param nNoEntries address containing the number of existing entries 
    @param target what search will be looking for
    @param nFirstEntry the first entry to be searched
    @param nFirstPair the first pair (within nFirstEntry) to be searched
    @param nEntryNo address where the index of the first instance of the target entry will be stored
    @param nPairNo address where the index of the first instance of the target pair will be stored
    @param nMatch will tell if the language, the translation, or both will be searched
                   (1 if only the languages, 2 if only the translations, 3 if both)
    @return N/A

    Pre-condition: at least one entry exists
*/
void
search(struct translatePair aEntries[][PAIRMAX],
       int aEntryCounts[],
       int nNoEntries,
       struct translatePair target, 
       int nFirstEntry,
       int nFirstPair,
       int *nEntryNo,
       int *nPairNo,
       int nMatch)
{
    int i = nFirstEntry,
        j = nFirstPair,
        isFound = 0; // Denotes if the target has been found and similarity rate to target
    
    // These variables will hold the indices to the first instance of target
    *nEntryNo = -1;
    *nPairNo = -1;

    // Loops until found or until all entries have been checked
    while (!isFound && i < nNoEntries)
    {
        // Loops until found or all translation pairs in the entry have been checked
        while (!isFound && j < aEntryCounts[i])
        {
            isFound = pairComparison(target, aEntries[i][j]); // Checks the similarity rate to target

            // If the desired match is met (matches with nMatch)
            if (isFound == 3 || isFound == nMatch)
            {
                *nEntryNo = i;
                *nPairNo = j;
            }
            else 
            {
                isFound = 0; // Resets isFound
                j++;
            }
        }

        // Moves to the next entry
        if (!isFound)
        {
            i++;
            j = 0;
        }
    }
}

//#############################################################################################################
//#############################################################################################################

/*
    sortEntries 
    
    sorts the entries according to English translation
    @param aEntries array of the list of entries that exist
    @param aEntryCounts array of the number of translation pairs stored in each entry
    @param nNoEntries address containing the number of existing entries 
    @return N/A

    Pre-condition: Each entry has had its pairs intra-sorted prior;
                   there is at least one existing entry
*/
void
sortEntries(struct translatePair aEntries[][PAIRMAX],
            int aEntryCounts[],
            int nNoEntries)
{
    int i = 0,
        j,
        a, // Entry to be compared with min
        b, // Pair to be compared with min
        intTemp,
        iMin = 0, // Entry min variable
        jMin = 0; // Pair min variable
    struct translatePair target, // Contains the target language to be found
                         TPtemp;

    
    strcpy(target.strLang, "English"); // Set to English since in sorting entries, the entries with English pairs are placed first
    
    // Selection sort; prioritizing entries that match with target.strLang
    while (i < nNoEntries - 1 && iMin != -1 && jMin != -1)
    {
        iMin = i;
        jMin = 0;

        // Searches for the first instance of the target to serve as min
        search(aEntries, aEntryCounts, nNoEntries, target,
               iMin, jMin, &iMin, &jMin, 1);
        
        // Runs if an English pair is found
        if (iMin > -1 && jMin > -1)
        {
            a = iMin;
            b = jMin;

            while (a != -1 && b != -1)
            {
                // Finds another entry to be compared to
                search (aEntries, aEntryCounts, nNoEntries, target,
                        a, b + 1, &a, &b, 1);

                if (a > -1 && b > -1)
                    if (strcmp(aEntries[a][b].strTrans, aEntries[iMin][jMin].strTrans) < 0)
                    {
                        iMin = a;
                        jMin = b;
                        b++;
                    }
            }

            // Executes swaps if iMin is not the lowest entry index possible to save on memory processing
            if (iMin != i)
            {
                // Entry count swap
                intTemp = aEntryCounts[i];
                aEntryCounts[i] = aEntryCounts[iMin];
                aEntryCounts[iMin] = intTemp;
                
                // Entry translation pairs swap
                for (j = 0; j < PAIRMAX; j++)
                {
                    TPtemp = aEntries[i][j];
                    aEntries[i][j] = aEntries[iMin][j];
                    aEntries[iMin][j] = TPtemp;
                }
            }

            i++;
        }
    }
}


/*
    sortEntryPairs 
    
    sorts the translation pairs in a single entry according to language
    @param entry the entry to be sorted
    @param entryCount the current count of the entry
    @return N/A 

    Pre-condition: The entry contains at least one translation pair
*/
void
sortEntryPairs(struct translatePair entry[], 
               int entryCount)
{
    int i, 
        j, 
        min;
    struct translatePair temp;
    
    // Selection sort based on language, then translation word if necessary
    for (i = 0; i < entryCount - 1; i++)
    {
        min = i;

        // Checks if language; if same language, then checks translation word
        for (j = i + 1; j < entryCount; j++)
            if (strcmp(entry[j].strLang, entry[min].strLang) < 0 ||
                (strcmp(entry[j].strLang, entry[min].strLang) == 0 &&
                strcmp(entry[j].strTrans, entry[min].strTrans) < 0))
              min = j;
        
        if (min != i)
        {
            temp = entry[i];
            entry[i] = entry[min];
            entry[min] = temp;
        }
    }
}

//#############################################################################################################
//#############################################################################################################

/*
    shiftEntries 
    
    shifts the entries and their counts by one index lower
    @param aEntries array of the list of entries that exist
    @param aEntryCounts array of the number of translation pairs stored in each entry
    @param nNoEntries the number of existing entries 
    @param nStartingIndex index where the shifting starts
    @return N/A

    Pre-condition: There are at least two existing entries;
                   nStartingIndex is a value from 0 to nNoEntries 1
*/
void
shiftEntries(struct translatePair aEntries[][PAIRMAX],
             int aEntryCounts[],
             int nNoEntries,
             int nStartingIndex)
{
    int i;

    // Shifts both entries and entry counts
    for (i = nStartingIndex; i < nNoEntries - 1; i++)
    {
        copyEntry(aEntries[i], aEntries[i + 1], aEntryCounts[i + 1]);
        aEntryCounts[i] = aEntryCounts[i + 1];
    }
}

/*
    shiftPairs 
    
    shifts the translation pairs of an entry by one index lower
    @param aEntry array of the list of translation pairs in an entry
    @param nEntryCount array of the number of translation pairs stored in the entry
    @param nStartingIndex index where the shifting starts
    @return N/A
    Pre-condition: There are at least two entries that exist;
                   nStartingIndex is a value from 0 to nEntryCount 1
*/
void
shiftPairs(struct translatePair aEntry[],
           int nEntryCount,
           int nStartingIndex)
{
    int i;

    // Shifts pairs
    for (i = nStartingIndex; i < nEntryCount - 1; i++)
        aEntry[i] = aEntry[i + 1];
}

/*
    clearEntry 
    
    clears all translation pairs in an entry
    @param aEntry array of the list of translation pairs in an entry
    @param nEntryCount array of the number of translation pairs stored in the entry
    @return N/A

    Pre-condition: The entry is intended to be "deleted"
*/
void
clearEntry(struct translatePair aEntry[],
           int nEntryCount)
{
    int i;

    // Clears every language and translation pair
    for (i = 0; i < nEntryCount; i++)
    {
        strcpy(aEntry[i].strLang, "");
        strcpy(aEntry[i].strTrans, ""); 
    }
}

//#############################################################################################################
//#############################################################################################################

/*
    readImportedData 
    
    reads data from a text file and stores it as translation pairs in aEntries
    @param fp file pointer of the txt file being read
    @param aEntries array of the list of entries that exist
    @param aEntryCounts array of the number of translation pairs stored in each entry
    @param *nNoEntries address of the number of existing entries
    @return N/A

    Pre-condition: fp points to a txt file;
                   in textfiles, each translation pair in an entry is separated by one newline, 
                       while entries are separated by two;
                   each element in aEntryCounts is initialized to 0 prior
*/
void
readImportedData(FILE *fp,
                 struct translatePair aEntries[][PAIRMAX],
                 int aEntryCounts[],
                 int *nNoEntries)
{
    int nLenCount = 0, // Tracks the length of a string
        nToggleRead = 1, // Toggles between language (1) and translation word (2)
        nNewlineReads = 0; // Tracks the number of consecutive newlines read
    char ch; // Stores the char read in the file

    *nNoEntries = 0; 

    // Reads the txt file until EOF
    while (fscanf(fp, "%c", &ch) != EOF && *nNoEntries < ENTMAX)
    {
        // Newline tracker
        if (ch == '\n')
            nNewlineReads++;
        else
        {
            if (ch == ':')
            {
                aEntries[*nNoEntries][aEntryCounts[*nNoEntries]].strLang[nLenCount] = '\0';

                nToggleRead = 2; // Toggles to translation word reading after reading ':'
                nLenCount = 0;

                // Skips to the first character after ':'
                fscanf(fp, "%c%c", &ch, &ch);
            }
            else
                nNewlineReads = 0; // Resets nNewlineReads if a regular charcter was entered
        }
        
        if (nNewlineReads == 2) // Stops reading an entry
        {
            sortEntryPairs(aEntries[*nNoEntries], aEntryCounts[*nNoEntries]);
            (*nNoEntries)++;
        }
        else if (nNewlineReads == 1) // Stops reading a translation pair
        {
            aEntries[*nNoEntries][aEntryCounts[*nNoEntries]].strTrans[nLenCount] = '\0';

            CleanString(aEntries[*nNoEntries][aEntryCounts[*nNoEntries]].strLang, 1);
            CleanString(aEntries[*nNoEntries][aEntryCounts[*nNoEntries]].strTrans, 0);

            aEntryCounts[*nNoEntries]++;
            nLenCount = 0;
            nToggleRead = 1; // Toggles back to language reading
        }
        else // Reads character input
        {
            switch (nToggleRead)
            {
                case 1: // Language reading
                    if (nLenCount < SHORT_STRMAX)
                        aEntries[*nNoEntries][aEntryCounts[*nNoEntries]].strLang[nLenCount] = ch;
                    break;
                case 2: // Translation word reading
                    if (nLenCount < SHORT_STRMAX)
                        aEntries[*nNoEntries][aEntryCounts[*nNoEntries]].strTrans[nLenCount] = ch;
                    break;
            }
            nLenCount++;
        }
    }

    sortEntries(aEntries, aEntryCounts, *nNoEntries);
}

//#############################################################################################################
//#############################################################################################################

/*
    tokenize 
    
    separates a given text into individual words while removing punctuation marks
    @param text the text to be tokenized
    @param words the array to store the tokenized words
    @param wordCount address of the number of words found from tokenizing 
    @return N/A

    Pre-condition: text is a LongString that contains at least one character;
                   words isn't initialized prior
*/
void
tokenize(char text[],
         char words[][LONG_STRMAX + 1],
         int *wordCount)
{
    int j = 0,
        k = 0;
    char ch; // Stores the character read from text

    (*wordCount) = 0;

    // Runs until NULL character
    while ((ch = text[k]) != '\0')
    {
        if (j < LONG_STRMAX)
        {
            // Copies ch to the word if a valid character is read
            if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
                (ch >= '0' && ch <= '9') || ch == '\'' || ch == '-')
            {
                words[*wordCount][j] = ch;
                j++;
            }

            // Finalizes the current word and moves to reading the next one
            else if (strlen(words[*wordCount]) > 0)
            {
                words[*wordCount][j] = '\0';
                (*wordCount)++;
                j = 0;
            }
        }
        else
        {
            words[*wordCount][j] = '\0';
            (*wordCount)++;
            j = 0;
        }
        k++;
    }

    if (strlen(words[*wordCount]) > 0)
    {
        words[*wordCount][j] = '\0';
        (*wordCount)++;
    }
}

/*
    shortStrWordCount 
    
    counts the number of words present in a given ShortString
    @param string the string to be evaluated
    @return the number of words in string
    
    Pre-condition: string is a ShortString that contains at least one character
*/
int
shortStrWordCount(char string[])
{
    int i = 0,
        ctr = 0; // Counter for the number of words read
    char ch; // Stores the characters read from the text

    while ((ch = string[i]) != '\0')
    {
        // Consider a new word spotted if a space is spotted
        if (ch == ' ')
        {
            ctr++;
            i++;
            // Skips to the next non-space character
            while (string[i] == ' ')
                i++;
        }
        else
            i++;
    }

    // Reads the last word cut by the EOF
    if (ch != ' ')
        ctr++;
    
    return ctr;
}

/*
    shiftWords 
    
    shifts words in the given array 
    @param aWords array of the list of words
    @param nWordCount array of the number of words stored in aWords
    @param nStartingIndex index where the shifting starts
    @param nShift how many indices each entry will go down by
    @return N/A
    Pre-condition: There are at least two words that exist;
                   nStartingIndex is a value from 0 to nWordCount 1
                   nShift is between 1 and nWordCount nStartingIndex 1
*/
void
shiftWords(char aWords[][LONG_STRMAX + 1],
           int nWordCount,
           int nStartingIndex,
           int nShift)
{
    int i;

    // Shifts words
    for (i = nStartingIndex; i < nWordCount - nShift; i++)
        strcpy(aWords[i], aWords[i + nShift]);
}

/*
    checkCapitalization 
    
    checks the capitalization of the word/phrase
    @param word word or phrase to be checked
    @return 1 if FULLY CAPITALIZED, 2 if Sentence case, and 0 otherwise
    
    Pre-condition: strlen(word) <= 20
*/
int
checkCapitalization(char word[])
{
    char checker[SHORT_STRMAX]; // Used as a test case for different casings
 
    strcpy(checker, word); // Copies word to checker

    // If fully capitalized
    if (strcmp(word, strupr(checker)) == 0)
        return 1;
    else
    {
        // If sentence cased
        CleanString(checker, 1);
        if (strcmp(word, checker) == 0)
            return 2;
        else // Other cases
            return 0;
    } 
}

/*
    executeTranslate

    executes the translation of a text
    @param aEntries array of the list of entries that exist
    @param aEntryCounts array of the number of translation pairs stored in each entry
    @param nNoEntries address containing the number of existing entries 
    @param target what search will be looking for
    @param isWordCountPresent array of boolean values denoting if there exists words with the corresponding word length
    @param wordCount pointer to the word count of the text
    @param langFrom the string of the language of the text
    @param langTo the string of the language to translate the text to
    @return N/A
*/
void
executeTranslate(struct translatePair aEntries[][PAIRMAX], 
                 int aEntryCounts[],
                 int nNoEntries,
                 char aWords[][LONG_STRMAX + 1],
                 int isWordCountPresent[],
                 int *wordCount,
                 char langFrom[],
                 char langTo[])
{
    int i = 0,
        j,
        k,
        matchI, // Entry number containing target
        matchJ,  // Pair number containing target
        nIsValid, // Bool value denoting if the translation word formed is valid
        isTranslated, // Bool value denoting if the word has been translated
        nCapitalization; // Value denoting the capitalization of the word
    struct translatePair target; // The target translation pair (language input of user and translation word from text)

    strcpy(target.strLang, langFrom);

    // Loops for every tokenized word in the text
    while (i < *wordCount)
    {
        // Runs if word is a ShortString
        if (strlen(aWords[i]) <= SHORT_STRMAX)
        {
            j = SHORT_STRMAX / 2 - 1;
            isTranslated = 0;

            // Runs while the word isn't yet translated or all possible word counts haven't been tried
            while (!isTranslated && j >= 0)
            {
                // If there is at least a target.strLang pair that possesses the current word count
                if (isWordCountPresent[j])
                {
                    nIsValid = 1;

                    // Proceeds if there are enough words to assess the current word count
                    if (*wordCount - i >= j + 1)
                    {
                        strcpy(target.strTrans, "");

                        // Creates a new translation word following the word count
                        for (k = 0; k < j + 1 && nIsValid; k++)
                        {
                            nIsValid = strlen(target.strTrans) + strlen(aWords[i + k]) <= 20;

                            if (nIsValid)
                            {
                                strcat(target.strTrans, aWords[i + k]);
                                if (k < j)
                                    strcat(target.strTrans, " ");
                            }
                        }
                    }
                    else
                        nIsValid = 0;
                    
                    if (nIsValid)
                    {
                        matchI = 0;
                        matchJ = 0;

                        nCapitalization = checkCapitalization(target.strTrans);
                        CleanString(target.strTrans, 0);

                        // Finds any instance of target among the entries
                        while (!isTranslated && matchI > -1 && matchJ > -1)
                        {
                            search (aEntries, aEntryCounts, nNoEntries, target,
                                    matchI, matchJ, &matchI, &matchJ, 3);
                    
                            // Proceeds to check if there are any langTo pairs in the same entry
                            if (matchI > -1 && matchJ > -1)
                            {
                                k = 0;
                                
                                while (!isTranslated && k < aEntryCounts[matchI])
                                    if (strcmp(aEntries[matchI][k].strLang, langTo) == 0)
                                        isTranslated = 1;
                                    else
                                        k++;
                                
                                // Copies the (entire) found translation word to words
                                if (isTranslated)
                                {
                                    strcpy(aWords[i], aEntries[matchI][k].strTrans);

                                    // Capitalizes accordingly
                                    switch (nCapitalization)
                                    {
                                        case 1:
                                            strupr(aWords[i]);
                                            break;
                                        case 2:
                                            CleanString(aWords[i], 1);
                                            break;
                                    }

                                    // Shifts words according to the word count of the translation
                                    if (j > 0)
                                    {
                                        shiftWords(aWords, *wordCount, i + 1, j);
                                        *wordCount -= j;
                                    }
                                }
                                else 
                                    matchJ++;
                            }
                        }
                    }
                }
                
                if (!isTranslated)
                    j--;
            }
        }

        i++;
    }
}