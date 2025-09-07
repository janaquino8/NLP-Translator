#include "options.c"

/*
    ManageDataMenu 
    
    displays and runs the manage data menu
    @param N/A
    @return N/A

    Pre-condition: N/A
*/
void 
ManageDataMenu()
{
    struct translatePair aEntries[ENTMAX][PAIRMAX]; // 2d array representing the entries and its translation pairs
    int aEntryCounts[ENTMAX] = {0}, // Number of translation pairs per entry
        nNoEntries = 0,             // Number of existing entries
        nManageMenuInput,           // Numerical input of the user on the menu
        isSuccessfulCall;           // 1 if the corresponding function is successfully ran; 0 otherwise

    // Loop to operate the manage data menu 
    do 
    {
        // Initialization
        isSuccessfulCall = 0;

        // Display screen
        printf("\n");
        printLine(LINELEN);
        displayManageDataMenu();

        // Loop to call a feature; exits if a corresponding function is successfully ran
        do 
        {
            nManageMenuInput = getIntSentiInput(0, 9, "Enter: ");
            printLine(SLINELEN);
    
            /* 
                Running the corresponding function
                Checking Pre-conditions:
                    Add Entry and Import checks if ENTMAX has been met
                    The others check if at least one entry exists
            */
            switch (nManageMenuInput)
            {
                case 1:
                    if (nNoEntries < ENTMAX)
                    {
                        AddEntry(aEntries, aEntryCounts, &nNoEntries);
                        isSuccessfulCall = 1;
                    }
                    else
                        printf("You've already reached the maximum number of entries possible.\n");
                    break;
                case 2:
                    if (nNoEntries > 0)
                    {
                        AddTranslation(aEntries, aEntryCounts, &nNoEntries);
                        isSuccessfulCall = 1;
                    }
                    else
                        printf("There is no existing entry. Add one first!\n");
                    break;
                case 3:
                    if (nNoEntries > 0)
                    {
                        DeleteEntry(aEntries, aEntryCounts, &nNoEntries);
                        isSuccessfulCall = 1;
                    }
                    else
                        printf("There is no existing entry. Add one first!\n");
                    break;
                case 4:
                    if (nNoEntries > 0)
                    {
                        DeleteTranslation(aEntries, aEntryCounts, &nNoEntries);
                        isSuccessfulCall = 1;
                    }
                    else
                        printf("There is no existing entry. Add one first!\n");
                    break;
                case 5:
                    if (nNoEntries > 0)
                    {
                        DisplayAllEntries(aEntries, aEntryCounts, nNoEntries);
                        isSuccessfulCall = 1;
                    }
                    else
                        printf("There is no existing entry. Add one first!\n");
                    break;
                case 6:
                    if (nNoEntries > 0)
                    {
                        SearchWord(aEntries, aEntryCounts, nNoEntries);
                        isSuccessfulCall = 1;
                    }
                    else
                        printf("There is no existing entry. Add one first!\n");
                    break;
                case 7:
                    if (nNoEntries > 0)
                    {
                        SearchTranslation(aEntries, aEntryCounts, nNoEntries);
                        isSuccessfulCall = 1;
                    }
                    else
                        printf("There is no existing entry. Add one first!\n");
                    break;
                case 8:
                    if (nNoEntries > 0)
                    {
                        Export(aEntries, aEntryCounts, nNoEntries);
                        isSuccessfulCall = 1;
                    }
                    else
                        printf("There is no existing entry. Add one first!\n");
                    break;
                case 9:
                    if (nNoEntries < ENTMAX)
                    {
                        Import(aEntries, aEntryCounts, &nNoEntries);
                        isSuccessfulCall = 1;
                    }
                    else
                        printf("You've already reached the maximum number of entries possible.\n");
                    break;
            }
        } while (!isSuccessfulCall && nManageMenuInput != 0);
    } while (nManageMenuInput != 0); 
}

/*
    TranslateMenu 
    
    displays and runs the translate menu
    @param N/A
    @return N/A

    Pre-condition: N/A
*/
void 
TranslateMenu()
{
    struct translatePair aEntries[ENTMAX][PAIRMAX]; // 2d array representing the entries and its translation pairs
    int aEntryCounts[ENTMAX] = {0}, // Number of translation pairs per entry
        nNoEntries = 0,             // Number of existing entries
        nTransMenuInput;            // Numerical input of the user on the menu
    FILE *fp;   // File pointer for the imported file
    MediumString filename; // File name of the txt file to be imported
    
    //  Getting the filename
    printf("\nEnter the filename to import data from.\n");
    getTxtFileNameInput(filename);
    
    if ((fp = fopen(filename, "rt")) != NULL)
    {
        // Importing the data from the text file
        readImportedData(fp, aEntries, aEntryCounts, &nNoEntries);
        fclose(fp);

        // The actual translate menu runs if at least one translate pair is read
        if (nNoEntries > 0)
        {
            printf("\nData from %s successfully imported", filename);
    
            // Loop to call a feature
            do 
            {
                // Display screen
                printf("\n");
                printLine(LINELEN);
                displayTranslateMenu();
            
                nTransMenuInput = getIntSentiInput(0, 2, "Enter: ");
            
                // Calls a corresponding feature
                switch (nTransMenuInput)
                {
                    case 1:
                        TranslateTextInput(aEntries, aEntryCounts, nNoEntries);
                        break;
                    case 2:
                        TranslateTextFile(aEntries, aEntryCounts, nNoEntries);
                        break;
                }
            
            } while (nTransMenuInput != 0); 
        }
        else
        {
            printf("\nData import failed.\n");
            getIntSentiInput(0, 0, "Enter 0 to revert: ");

        }
    }
    else
    {
        printf("\nData import failed.\n");
        getIntSentiInput(0, 0, "Enter 0 to continue: ");
    }
}

/*
    main function

    @param N/A
    @return 0 if successfully ran
    
    Pre-condition: N/A
*/
int 
main()
{
    int nMenuInput;    // Numerical input of the user on the menu

    // Loop to operate the main menu
    do 
    {
        // Display screen
        printf("\n");
        displayMainMenu();

        nMenuInput = getIntSentiInput(0, 2, "Enter: ");

        switch (nMenuInput)
        {
            case 1:
                ManageDataMenu();
                break;
            case 2:
                TranslateMenu();
                break;
        }
    } while (nMenuInput != 0); 
    
    // Message before program termination
    printf("\n");
    printLine(LINELEN);
    printf("Thank you! ~ Salamat! ~ Terima kasih! ~ Gracias! ~ Merci ! ~ Grazie! ~ Obrigado!\n\n");

    return 0;
}