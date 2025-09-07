#include "helper.c"

/*
    AddEntry creates a new entry/entries
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param nNoEntries - address containing the number of existing entries 
    @return N/A
    Pre-condition: The number of existing entries is less than ENTMAX
*/
void
AddEntry(struct translatePair aEntries[][PAIRMAX],
         int aEntryCounts[],
         int *nNoEntries)
{
    int i, 
        j,
        nIsFound,  // entry number if the input has been found in the entry; -1 otherwise
        nIsStore,  // 1 if the input has been stored to a new array; 0 otherwise
        nSentinel; // 1 as long as the function continues to run
    struct translatePair input; // Stores the input of the user

    printf("      __   __      ___      ___  __\n");
    printf(" /\\  |  \\ |  \\    |__  |\\ |  |  |__) \\ /\n");
    printf("/~~\\ |__/ |__/    |___ | \\|  |  |  \\  |\n\n");

    // Loops while nSentinel is 1 and nNoEntries is less than ENTMAX
    do
    {
        nIsFound = -1;

        input = getTranslatePair(); // Gets the user input of the translate pair

        // Displays existing entries with the input, if any
        printf("\nEntries with %s - %s:\n", input.strLang, input.strTrans);

        // Loop to find instances of the input in the existing entries
        for (i = 0; i < *nNoEntries; i++)
        {   
            j = 0;

            while (nIsFound != i && j < aEntryCounts[i])
            {
                // Runs if the input matches aEntries[i][j]
                if (pairComparison(input, aEntries[i][j]) == 3)
                {
                    displayEntry(aEntries[i], aEntryCounts[i], i + 1);
                    nIsFound = i; // Denotes that the translation pair is found in entry i
                }
                else
                    j++;
            }
        }
    
        // If the input is not found in any of the existing entries
        if (nIsFound == -1)
            printf("No entry contains the entered translation pair.\n\n");
    
        printf("Would you like to add %s - %s to a new entry?\n", input.strLang, input.strTrans);
        nIsStore = getIntSentiInput(0, 1, "Enter (1 if yes; 0 if no): ");    
    
        /*
            if 1, add new entry
            if 0, go back to manage data menu
            then ask if to add new entry, but keep in mind max limit
        */
        if (nIsStore)
        {
            aEntries[*nNoEntries][0] = input;
            aEntryCounts[*nNoEntries]++;
            (*nNoEntries)++;
            SortEntries(aEntries, aEntryCounts, *nNoEntries); // Allows for auto sorting

            printf("\nEntry added successfully.\n\n");

            if (*nNoEntries < ENTMAX)
            {
                printf("Would you like to add another entry?\n");
                nSentinel = getIntSentiInput(0, 1, "Enter (1 if yes; 0 if no): ");
                printf("\n");
            }
        }
        else
            nSentinel = 0;
    } while (nSentinel && *nNoEntries < ENTMAX);
}   

/*
    AddTranslation creates a new translation pair for an existing entry
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param nNoEntries - address containing the number of existing entries 
    @return N/A
    Pre-condition: There is at least one existing entry
*/
void
AddTranslation(struct translatePair aEntries[][PAIRMAX],
               int aEntryCounts[],
               int *nNoEntries)
{
    int i, 
        j,
        nIsFound = -1,  // entry number if the input has been found in the entry; -1 otherwise
        nSentinel,      // 1 as long as the function continues to run
        nEntryStore,    // Entry number to store the entered translation pairs
        nNoFoundEntries = 0, // Number of entries that contain the first input of the user
        aFoundEntries[ENTMAX] = {0}; // Bool values  denoting the entries that contain the first input of the user
                                     // (1 if yes; 0 if no)
    struct translatePair input; // Stores the input of the user

    printf("      __   __     ___  __             __            ___    __\n");
    printf(" /\\  |  \\ |  \\     |  |__)  /\\  |\\ | /__` |     /\\   |  | /  \\ |\\ |\n");
    printf("/~~\\ |__/ |__/     |  |  \\ /~~\\ | \\| .__/ |___ /~~\\  |  | \\__/ | \\|\n\n");

    input = getTranslatePair();
    printf("\nEntries with %s - %s:\n", input.strLang, input.strTrans);

    // Loop to determine the entries that contain the first input of the user
    for (i = 0; i < *nNoEntries; i++)
    {   
        j = 0;

        while (nIsFound != i && j < aEntryCounts[i])
        {
            // Runs if the input matches aEntries[i][j]
            if (pairComparison(input, aEntries[i][j]) == 3)
            {
                displayEntry(aEntries[i], aEntryCounts[i], i + 1);
                nNoFoundEntries++;
                aFoundEntries[i]++; // Denotes that entry i contains the translation pair (value is 1) 
                nIsFound = i; // Denotes that the translation pair is found in entry i

                if (aEntryCounts[i] >= PAIRMAX)
                    printf("NOTE: This entry is full.\n\n");
            }
            else
                j++;
        }
    }

    // If the input isn't found
    if (nNoFoundEntries == 0)
    {
        printf("No available entry with the translation pair exists. Add an entry to add this translation pair!\n");
        printf("Would you like to add an entry now?\n");
        nSentinel = getIntSentiInput(0, 1, "Enter (1 if yes; 0 if no): ");
        if (nSentinel)
            AddEntry(aEntries, aEntryCounts, nNoEntries);
    }
    else
    {
        // If only one entry contains the input, that will be the assigned entry to take in new inputs
        if (nNoFoundEntries == 1)
            nEntryStore = nIsFound;
        else
        {
            // Selection of entry to take in new inputs
            do
            {
                nEntryStore = getIntNoInput(1, "Enter a valid entry no. to add a translation: ");
                // Checks if the entered entry number does contain the translation pair input 
                if (!aFoundEntries[nEntryStore] || aEntryCounts[nEntryStore] >= PAIRMAX)
                    printf("Invalid. ");
            } while (!aFoundEntries[nEntryStore] || aEntryCounts[nEntryStore] >= PAIRMAX);
        }
        
        // Loops while nSentinel is 1 and the entry count of the entry is less than PAIRMAX
        while (nSentinel && aEntryCounts[nEntryStore] < PAIRMAX)
        {
            // Gets user inputs of translate pairs and duly stores them
            input = getTranslatePair();
            aEntries[nEntryStore][aEntryCounts[nEntryStore]] = input;
            aEntryCounts[nEntryStore]++;

            printf("\n%s - %s added successfully to entry %d\n\n", 
                    input.strLang, input.strTrans, nEntryStore + 1);
            
            // Asks the user if another translate pair is to be added (if entry count is less than PAIRMAX)
            if (aEntryCounts[nEntryStore] < PAIRMAX)
            {
                printf("Would you like to add another pair to this entry?\n");
                nSentinel = getIntSentiInput(0, 1, "Enter (1 if yes; 0 if no): ");
                printf("\n");
            }
        } 

        // Sorts the entry (intra), then the entries (inter)
        SortEntryPairs(aEntries[nEntryStore], aEntryCounts[nEntryStore]);
        SortEntries(aEntries, aEntryCounts, *nNoEntries);
    }
}

/*
    DisplayAllEntries display all existing entries (entries that have at least one translation pair)
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param nNoEntries - the number of existing entries 
    @return N/A
    Pre-condition: There is at least one existing entry
*/
void
DisplayAllEntries(struct translatePair aEntries[][PAIRMAX],
                  int aEntryCounts[],
                  int nNoEntries)
{
    // Placeholder for displayEntries (aEntryNoList parameter, as this instance displays every entry and its corresponding entry number)
    int holder[1] = {0};

    printf(" __     __   __                                      ___      ___  __     ___  __\n");
    printf("|  \\ | /__` |__) |     /\\  \\ /     /\\  |    |       |__  |\\ |  |  |__) | |__  /__`\n");
    printf("|__/ | .__/ |    |___ /~~\\  |     /~~\\ |___ |___    |___ | \\|  |  |  \\ | |___ .__/\n\n");
    
    displayEntries(aEntries, aEntryCounts, nNoEntries, holder);
}

/*
    SearchWord displays, if any, the entries that include the instance of an input translation
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param nNoEntries - the number of existing entries 
    @return N/A
    Pre-condition: There is at least one existing entry
*/
void
SearchWord(struct translatePair aEntries[][PAIRMAX],
           int aEntryCounts[],
           int nNoEntries)
{
    struct translatePair aFoundEntries[ENTMAX][PAIRMAX]; // Stores the entries containing the entered word
    int i,
        j,
        nIsFound = -1,  // entry number if the input has been found in the entry; -1 otherwise
        nNoFoundEntries = 0, // Number of entries that contain the input of the user
        aEntryNoList[ENTMAX], // Stores the entry numbers of the entries that contain the word
        aFoundEntryCounts[ENTMAX]; // Stores the entry counts of the entries that contain the word
    ShortString input; // Stores the user input of a word

    printf(" __   ___       __   __                __   __   __\n");
    printf("/__` |__   /\\  |__) /  ` |__|    |  | /  \\ |__) |  \\\n");
    printf(".__/ |___ /~~\\ |  \\ \\__, |  |    |/\\| \\__/ |  \\ |__/\n\n");

    // Gets the user input of a translation word
    getShortStrInput(input, "Enter a word: ");
    CleanString(input, 0);

    // Determines the entries that contain the input translation word
    for (i = 0; i < nNoEntries; i++)
    {
        j = 0;

        while (nIsFound != i && j < aEntryCounts[i])
        {
            // Copies the entry to aFoundEntries if the word is found
            if (strcmp(aEntries[i][j].strTrans, input) == 0)
            {
                copyEntry(aFoundEntries[nNoFoundEntries], aEntries[i], aEntryCounts[i]);
                aFoundEntryCounts[nNoFoundEntries] = aEntryCounts[i];
                aEntryNoList[nNoFoundEntries] = i + 1; 
                nNoFoundEntries++;
                nIsFound = i; // Denotes that the input word was found in entry i
            }
            else
                j++;
        }
    }

    // Displays the found entries if there exist
    if (nNoFoundEntries > 0)
        displayEntries(aFoundEntries, aFoundEntryCounts, nNoFoundEntries, aEntryNoList);
    else
        getIntSentiInput(0, 0, "No entry found. Enter 0 to revert: ");
}

/*
    SearchTranslation displays, if any, the entries that include the instance of an input translation pair
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param nNoEntries - the number of existing entries 
    @return N/A
    Pre-condition: There is at least one existing entry
*/
void
SearchTranslation(struct translatePair aEntries[][PAIRMAX],
                  int aEntryCounts[],
                  int nNoEntries)
{
    struct translatePair aFoundEntries[ENTMAX][PAIRMAX], // Stores the entries containing the entered translation pair
                         input; // Stores the user input of a translation pair
    int i,
        j,
        nIsFound = -1,  // entry number if the input has been found in the entry; -1 otherwise
        nNoFoundEntries = 0, // Number of entries that contain the input of the user
        aEntryNoList[ENTMAX], // Stores the entry numbers of the entries that contain the word
        aFoundEntryCounts[ENTMAX]; // Stores the entry counts of the entries that contain the word

    printf(" __   ___       __   __          ___  __             __            ___    __\n");
    printf("/__` |__   /\\ |__) /  ` |__|     |  |__)  /\\  |\\ | /__` |     /\\   |  | /  \\ |\\ |\n");
    printf(".__/ |___ /~~\\ |  \\ \\__, |  |     |  |  \\ /~~\\ | \\| .__/ |___ /~~\\  |  | \\__/ | \\|\n\n");

    // Gets the user input of a translation pair
    input = getTranslatePair();

    // Determines the entries that contain the input translation pair
    for (i = 0; i < nNoEntries; i++)
    {
        j = 0;

        while (nIsFound != i && j < aEntryCounts[i])
        {
            // Copies the entry to aFoundEntries if the translation pair is found
            if (pairComparison(input, aEntries[i][j]) == 3)
            {
                copyEntry(aFoundEntries[nNoFoundEntries], aEntries[i], aEntryCounts[i]);
                aFoundEntryCounts[nNoFoundEntries] = aEntryCounts[i];
                aEntryNoList[nNoFoundEntries] = i + 1;
                nNoFoundEntries++;
                nIsFound = i; // Denotes that the input translation pair was found in entry i
            }
            else
                j++;
        }
    }

    // Displays the found entries if there exist
    if (nNoFoundEntries > 0)
        displayEntries(aFoundEntries, aFoundEntryCounts, nNoFoundEntries, aEntryNoList);
    else
        getIntSentiInput(0, 0, "No entry found. Enter 0 to revert: ");
}

/*
    DeleteEntry deletes an existing entry, then shifts succeeding entries if necessary
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param *nNoEntries - address of the number of existing entries 
    @return N/A
    Pre-condition: There is at least one existing entry
                   The entries have been sorted prior
*/
void
DeleteEntry(struct translatePair aEntries[][PAIRMAX],
            int aEntryCounts[],
            int *nNoEntries)
{
    int nSentinel, // 1 as long as the function continues to run
        nEntryNoInput, // The entry number input of the user
        holder[1] = {0}; // Placeholder for displayEntries 
                         // (aEntryNoList parameter, as this instance displays every entry and its corresponding entry number)

    printf(" __   ___       ___ ___  ___     ___      ___  __\n");
    printf("|  \\ |__  |    |__   |  |__     |__  |\\ |  |  |__) \\ /\n");
    printf("|__/ |___ |___ |___  |  |___    |___ | \\|  |  |  \\  |\n\n");

    // Loops while nSentinel is 1 and there are still existing entries  
    do
    {
        // Displays all entries before proceeding to deletion
        printf("View the existing entries, then enter X to continue.\n\n");

        displayEntries(aEntries, aEntryCounts, *nNoEntries, holder);
        
        // Lets the user decide which entry to delete if more than one exists
        if (*nNoEntries > 1)
        {
            // Gets the user input of an entry number
            printf("\n");
            nEntryNoInput = getIntNoInput(0, "Enter a valid entry no. to delete: ");
    
            // Runs if a valid entry number is entered
            if (nEntryNoInput > -1 && nEntryNoInput < *nNoEntries)
            {
                // Shifts entries if the entered entry number is not the last entry
                if (nEntryNoInput < *nNoEntries - 1)
                    shiftEntries(aEntries, aEntryCounts, *nNoEntries, nEntryNoInput);
    
                // Clears the last "non-empty" entry in the 2d array to ensure no issues in sorting
                clearEntry(aEntries[*nNoEntries - 1], aEntryCounts[*nNoEntries - 1]);
                aEntryCounts[*nNoEntries - 1] = 0;
                (*nNoEntries)--;
    
                printf("\nEntry deleted successfully.\n");
    
                if (*nNoEntries > 0)
                {
                    printf("Would you like to delete another entry?\n");
                    nSentinel = getIntSentiInput(0, 1, "Enter (1 if yes; 0 if no): ");
                }
            }
            else
                nSentinel = getIntSentiInput(0, 0, "Invalid input. Enter 0 to revert: ");
        }
        else // If only one entry exists
        {
            printf("Only one entry exists. Would you like to delete it?\n");
            nSentinel = getIntSentiInput(0, 1, "Enter (1 if yes; 0 if no): ");

            if (nSentinel)
            {
                clearEntry(aEntries[0], aEntryCounts[0]);
                aEntryCounts[0] = 0;
                (*nNoEntries)--;
                printf("\nEntry deleted successfully.\n");
            }
        }
    } while (nSentinel != 0 && *nNoEntries > 0);
}

/*
    DeleteTranslation deletes a translation pair/s from a single entry, then adjusts accordingly
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param *nNoEntries - address of the number of existing entries 
    @return N/A
    Pre-condition: There is at least one existing entry
                   The entries have been sorted prior
                   Each entry has been sorted prior
*/
void
DeleteTranslation(struct translatePair aEntries[][PAIRMAX],
                  int aEntryCounts[],
                  int *nNoEntries)
{
    int nSentinel, // 1 as long as the function continues to run
        nEntryNoInput, // The entry number input of the user
        nPairNoInput, // The pair number input of the user
        isEntryExists = 1, // Bool value denoting if the entry exists
        holder[1] = {0}; // Placeholder for displayEntries 
                         // (aEntryNoList parameter, as this instance displays every entry and its corresponding entry number)
    
    printf(" __   ___       ___ ___  ___    ___  __             __            ___    __\n");
    printf("|  \\ |__  |    |__   |  |__      |  |__)  /\\  |\\ | /__` |     /\\   |  | /  \\ |\\ |\n");
    printf("|__/ |___ |___ |___  |  |___     |  |  \\ /~~\\ | \\| .__/ |___ /~~\\  |  | \\__/ | \\|\n\n");

    // Displays all entries before proceeding to deletion
    printf("View the existing entries, then enter X to continue.\n\n");

    displayEntries(aEntries, aEntryCounts, *nNoEntries, holder);

    printf("\n");
    
    // Lets the user decide which entry to base deletion on if more than one entry exists
    if (*nNoEntries > 1)
    {
        nEntryNoInput = getIntNoInput(0, "Enter a valid entry no: ");
        // Sets nSentinel to 0 if the entered entry number is invalid
        if (nEntryNoInput < 0 || nEntryNoInput >= *nNoEntries)
            nSentinel = getIntSentiInput(0, 0, "Invalid input. Enter 0 to revert: ");
    }
    else
        nEntryNoInput = 0;
    
    // Loops while nSentinel is 1 and the entry still exists (i.e., it contains at least one translation pair)
    while (nSentinel && isEntryExists)
    {
        displayEntry(aEntries[nEntryNoInput], aEntryCounts[nEntryNoInput], nEntryNoInput + 1);

        // Lets the user decide which translation pair to delete if more than one exists
        if (aEntryCounts[nEntryNoInput] > 1)
        {
            nPairNoInput = getIntNoInput(0, "Enter a valid pair no. to delete: ");
            printf("\n");

            // Runs if a valid pair number is entered
            if (nPairNoInput > -1 && nPairNoInput < aEntryCounts[nEntryNoInput])
            {
                // Shifts pairs if the entered pair number is not the last entry
                if (nPairNoInput < aEntryCounts[nEntryNoInput] - 1)
                    shiftPairs(aEntries[nEntryNoInput], aEntryCounts[nEntryNoInput], nPairNoInput);

                // Clears the last "non-empty" pair in the entry to ensure no issues in sorting
                strcpy(aEntries[nEntryNoInput][aEntryCounts[nEntryNoInput]].strLang, "");
                strcpy(aEntries[nEntryNoInput][aEntryCounts[nEntryNoInput]].strTrans, "");
                aEntryCounts[nEntryNoInput]--;

                printf("Translation pair deleted successfully.\n");
            }
            else
                printf("Invalid input.\n");
        }
        else // If only one translation pair exists in the entry
        {
            printf("Only one translation pair exists. Deleting thir pair will also delete the entry.\n");
            printf("Would you like to delete it?\n");

            nSentinel = getIntSentiInput(0, 1, "Enter (1 if yes; 0 if no): ");

            if (nSentinel)
            {
                if (nEntryNoInput < *nNoEntries - 1)
                    shiftEntries(aEntries, aEntryCounts, *nNoEntries, nEntryNoInput);

                clearEntry(aEntries[*nNoEntries - 1], aEntryCounts[*nNoEntries - 1]);
                aEntryCounts[*nNoEntries - 1] = 0;
                (*nNoEntries)--;
                isEntryExists = 0;

                printf("\nEntry deleted successfully.\n");
            }
        }
        
        // Asks the user if another translation pair in the entry is to be deleted
        if (nSentinel && isEntryExists)
        {
            printf("Would you like to delete another translation pair?\n");
            nSentinel = getIntSentiInput(0, 1, "Enter (1 if yes; 0 if no): ");
        }
    }

    // Sorts the entries in case if the previous entry's leading translation pair was deleted
    SortEntries(aEntries, aEntryCounts, *nNoEntries);
}

/*
    Export exports all stored information (entries) to a textfile
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param nNoEntries - the number of existing entries 
    @return N/A
    Pre-condition: There is at least one existing entry
                   The entries have been sorted prior
                   Each entry has been sorted prior
*/
void
Export(struct translatePair aEntries[][PAIRMAX],
       int aEntryCounts[],
       int nNoEntries)
{    
    int i,
        j;
    FILE *fp; // File pointer
    MediumString filename; // File name of the txt file to export data to
    
    printf(" ___      __   __   __  ___\n");
    printf("|__  \\_/ |__) /  \\ |__)  |\n");
    printf("|___ / \\ |    \\__/ |  \\  |\n\n");

    // Asks the user for the file name
    printf("Enter the filename to export data to.\n");

    getTxtFileNameInput(filename);

    fp = fopen(filename, "wt");

    // Writes data stored in aEntries to the file
    if (fp != NULL)
    {
        for (i = 0; i < nNoEntries; i++)
        {
            for (j = 0; j < aEntryCounts[i]; j++)
                fprintf(fp, "%s: %s\n", aEntries[i][j].strLang, aEntries[i][j].strTrans);
            fprintf(fp, "\n");
        }
        
        fclose(fp);
    
        printf("Data successfully exported to %s\n", filename);
    }
    else
    {
        printf("Data export failed.\n");
        getIntSentiInput(0, 0, "Enter 0 to continue: ");
    }
}

/*
    Import imports all information from a textfile into the program
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param nNoEntries - address of the number of existing entries 
    @return N/A
    Pre-condition: The number of existing entries is less than ENTMAX
                   There is at least one entry in the textfile
*/
void
Import(struct translatePair aEntries[][PAIRMAX],
       int aEntryCounts[],
       int *nNoEntries)
{
    struct translatePair aImportEntries[ENTMAX][PAIRMAX]; // Stores the imported entries
    int i = 0,
        nIsAdd = 0, // Bool value denoting if the imported entry is to be added
        nSentinel, // 1 as long as the function continues to run 
        aImportEntryCounts[ENTMAX] = {0}, // Stores the entry counts of each imported entry
        nImportNoEntries = 0; // Stores the number of entries imported
    FILE *fp; // File pointer
    MediumString filename; // File name of the txt file to import data from

    printf("         __   __   __  ___\n");
    printf("|  |\\/| |__) /  \\ |__)  |\n");
    printf("|  |  | |    \\__/ |  \\  |\n\n");

    // Asks the user for the file name
    printf("Enter the filename to import data from.\n");
    getTxtFileNameInput(filename);

    if ((fp = fopen(filename, "rt")) != NULL)
    {
        // Imports data directly to the program if there is no existing entry
        if (*nNoEntries == 0)
        {
            ReadImportedData(fp, aEntries, aEntryCounts, &nImportNoEntries);
            *nNoEntries = nImportNoEntries;
            fclose(fp);
            printf("\nData import from %s successful.\n", filename);
        }
        else // If at least one entry exists
        {
            // Stores data to aImportEntries first
            ReadImportedData(fp, aImportEntries, aImportEntryCounts, &nImportNoEntries);
            fclose(fp);

            // Lets the user decide one-by-one if an entry is to be imported
            printf("\nYou will now read through each imported entry and decide whether or not to save it.\n");

            // Runs while nNoEntries is less than ENTMAX and there are still imported entries left to be read
            while (*nNoEntries < ENTMAX && i < nImportNoEntries)
            {
                displayEntry(aImportEntries[i], aImportEntryCounts[i], i + 1);
                nSentinel = getIntSentiInput(0, 1, "Save entry? (1 if yes; 0 if no): ");
                if (nSentinel)
                {
                    // Copies the imported entry to the program
                    copyEntry(aEntries[*nNoEntries], aImportEntries[i], aImportEntryCounts[i]);
                    aEntryCounts[*nNoEntries] = aImportEntryCounts[i];
                    (*nNoEntries)++;
                    nIsAdd++;
                    
                    printf("Entry saved.\n\n");
                }
                i++;
            }
            // Sorts all existing entries if at least one imported entry was added to the program
            if (nIsAdd)
                SortEntries(aEntries, aEntryCounts, *nNoEntries);
        }
    }
    else
    {
        printf("Data import failed.\n");
        getIntSentiInput(0, 0, "Enter 0 to continue: ");
    }
}

//#############################################################################################################
//#############################################################################################################

/*
    TranslateTextInput translates an entered source text from a specific language to another
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param nNoEntries - the number of existing entries 
    @return N/A
    Pre-condition: There is at least one existing entry  
*/
void
TranslateTextInput(struct translatePair aEntries[][PAIRMAX],
                   int aEntryCounts[],
                   int nNoEntries)
{
    int i,
        j,
        nWordCount, // The number of words tokenized from input
        nSentinel = 1, // 1 as long as the function continues to run
        aIsWordCountPresent[SHORT_STRMAX / 2] = {0}; // Bool values denoting if a certain translatio pair word count exists
                                                     // (1 if yes; 0 if no)
    ShortString langFrom, // The language of the source text
                langTo; // The language to translate the source text to
    LongString input, // Stores the text input of the user
               aWords[LONG_STRMAX / 2] = {'\0'}; // Stores the words tokenized from input

    printf("___  ___     ___            __       ___\n");
    printf(" |  |__  \\_/  |     | |\\ | |__) |  |  |\n");
    printf(" |  |___ / \\  |     | | \\| |    \\__/  |\n\n");

    // Gets the user input for langFrom and langTo
    getShortStrInput(langFrom, "What is the language of the text?: ");
    CleanString(langFrom, 1);   
    // Ensures that langFrom and langTo are not the same
    do
    {
        getShortStrInput(langTo, "What language would you like to translate the text to?: ");
        CleanString(langTo, 1);
    } while (strcmp(langFrom, langTo) == 0);

    // Checks multiple word instances for translation pairs with langFrom
    // (i.e., how many 2-word translation pairs, how many 3-word translation pairs, etc.)
    for (i = 0; i < nNoEntries; i++)
        for (j = 0; j < aEntryCounts[i]; j++)
            if (strcmp(aEntries[i][j].strLang, langFrom) == 0)
                aIsWordCountPresent[ShortStrWordCount(aEntries[i][j].strTrans) - 1] = 1;
        
    // Loops while nSentinel is 1
    while (nSentinel)
    {
        nWordCount = 0;
        
        // Gets the text input of the user
        printf("\n");
        getLongStrInput(input, "Enter text: ");
        
        Tokenize(input, aWords, &nWordCount); // Separates the input to words and stores them in aWords
    
        // Executes the actual translation and stores the result in aWords
        executeTranslate(aEntries, aEntryCounts, nNoEntries,
                         aWords, aIsWordCountPresent, &nWordCount,
                         langFrom, langTo);

        // Displays the translated text (per words, without symbols that are part of words)
        printf("\nTranslated text:\n\n");

        for (i = 0; i < nWordCount; i++)
            printf("%s ", aWords[i]);

        // Asks the user if another translation from langFrom to langTo is to be made
        printf("\n\nTranslate another text from %s to %s?\n", langFrom, langTo);
        nSentinel = getIntSentiInput(0, 1, "Enter (1 if yes; 0 if no): ");
    }
}

/*
    TranslateTextInput translates an imported source text (from a txt file) from a specific language to another,
        then saves it in another txt file
    @param aEntries - array of the list of entries that exist
    @param aEntryCounts - array of the number of translation pairs stored in each entry
    @param nNoEntries - the number of existing entries 
    @return N/A
    Pre-condition: There is at least one existing entry  
                   The origin file contains at least one character
*/
void
TranslateTextFile(struct translatePair aEntries[][PAIRMAX],
                  int aEntryCounts[],
                  int nNoEntries)
{
    int i,
        j,
        nWordCount = 0, // The number of words tokenized from input
        aIsWordCountPresent[SHORT_STRMAX / 2] = {0}; // Bool values denoting if a certain translation pair word count exists
                                                     // (1 if yes; 0 if no)
    char ch; // Holds a character read from origFile
    ShortString langFrom, // The language of the source text
                langTo; // The language to translate the source text to
    LongString input, // Stores the text input of the user
               aWords[LONG_STRMAX / 2] = {'\0'}; // Stores the words tokenized from the input
    MediumString origFile, // File containing the source text
                 destFile; // File to save the translated text to
    FILE *fp1, // File pointer of origFile
         *fp2; // File pointer of destFile

    printf("___  ___     ___     ___         ___\n");
    printf(" |  |__  \\_/  |     |__  | |    |__\n");
    printf(" |  |___ / \\  |     |    | |___ |___\n\n");

    // Gets the user input for langFrom and langTo
    getShortStrInput(langFrom, "What is the language of the text?: ");
    CleanString(langFrom, 1);   
    
    // Gets the user input of origFile
    printf("\nEnter the filename to import the source text from.\n");
    getTxtFileNameInput(origFile);
    
    // Ensures that langFrom and langTo are not the same
    do
    {
        getShortStrInput(langTo, "\nWhat language would you like to translate the text to?: ");
        CleanString(langTo, 1);
    } while (strcmp(langFrom, langTo) == 0);


    // Gets the user input of destFile
    printf("\nEnter the filename to save the translated text.\n");
    getTxtFileNameInput(destFile);

    // Adds _COPY to the file name for destFile if the origFile and destFile are the same
    // With adjustments depending on strlen(destFile)
    if (strcmp(origFile, destFile) == 0)
    {
        if (strlen(destFile) <= 25)
            destFile[strlen(destFile) - 4] = '\0';        
        else
            destFile[20] = '\0';
        

        strcat(destFile, "_COPY.txt");
    }

    printf("\n");

    if ((fp1 = fopen(origFile, "rt")) != NULL)
    {
        // Checks multiple word instances for translation pairs with langFrom
        // (i.e., how many 2-word translation pairs, how many 3-word translation pairs, etc.)
        for (i = 0; i < nNoEntries; i++)
            for (j = 0; j < aEntryCounts[i]; j++)
                if (strcmp(aEntries[i][j].strLang, langFrom) == 0)
                    aIsWordCountPresent[ShortStrWordCount(aEntries[i][j].strTrans) - 1] = 1;

        fp2 = fopen(destFile, "wt");
            
        i = 0;

        // Simultaneously prints the translated text on the console and on destFile
        // Newline per sentence
        printf("Translated text:\n\n");

        // Runs while EOF has not been reached
        while (fscanf(fp1, "%c", &ch) == 1)
        {
            // Adds ch to input if LONG_STRMAX has not been reached 
            // or the sentence hasnt been terminated (by '.', '?', or '!')
            if (ch != '.' && ch != '?' && ch != '!' && i < LONG_STRMAX)
            {
                input[i] = ch;
                i++;
            }
            else if (i > 0) // If the sentence is duly terminated
            {
                input[i] = '\0';

                // Resets aWords to prevent complications with Tokenize
                for (j = 0; j < nWordCount; j++)
                    strcpy(aWords[j], "");

                nWordCount = 0;
                
                Tokenize(input, aWords, &nWordCount); // Separates the input to words and stores them in aWords
            
                // Executes the actual translation and stores the result in aWords
                executeTranslate(aEntries, aEntryCounts, nNoEntries,
                    aWords, aIsWordCountPresent, &nWordCount,
                    langFrom, langTo);
        
                // Prints the sentence
                for (j = 0; j < nWordCount; j++)
                {
                    printf("%s ", aWords[j]);
                    fprintf(fp2, "%s ", aWords[j]);
                }

                printf("\n");
                fprintf(fp2, "\n");
                
                i = 0;
            }
            
        }

        // Runs the same process for translation if the last sentence doesn't end with '.', '?', or '!'
        if (i > 0)
        {
            input[i] = '\0';

            nWordCount = 0;
            
            Tokenize(input, aWords, &nWordCount);
        
            executeTranslate(aEntries, aEntryCounts, nNoEntries,
                             aWords, aIsWordCountPresent, &nWordCount,
                             langFrom, langTo);
    
            for (j = 0; j < nWordCount; j++)
            {
                printf("%s ", aWords[j]);
                fprintf(fp2, "%s ", aWords[j]);
            }
        }

        fclose(fp1);
        fclose(fp2);

        printf("\nText from %s successfully translated and saved to %s\n\n", origFile, destFile);
    }
    else
    {
        printf("Translation failed.\n");
        getIntSentiInput(0, 0, "Enter 0 to revert: ");
    }
}