/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
                                                            Jan Leoric Badiola Aquino
*********************************************************************************************************/

#ifndef NLPT
#define NLPT

#include <stdio.h>
#include <string.h>

#define ENTMAX 150 // Maximum number of entries
#define PAIRMAX 10 // Maximum number of translation pairs per entry

// Maximum string lengths
#define SHORT_STRMAX 20 // For ShortString
#define MED_STRMAX   30 // For MediumString
#define LONG_STRMAX 150 // For LongString

// Line sizes (for display)
#define LINELEN  90 
#define SLINELEN 30
#define TLINELEN 49

typedef char ShortString[SHORT_STRMAX + 1]; // For languages and translations
typedef char MediumString[MED_STRMAX + 1];  // For txt file names
typedef char LongString[LONG_STRMAX + 1];   // For text inputs for translation

// Data structure for a translation pair
struct translatePair  
{
    ShortString strLang;  // Language
    ShortString strTrans; // Translation
};

// helper.c
void printLine(int n);
void displayMainMenu();
void displayManageDataMenu();
void displayTranslateMenu();
int getIntSentiInput(int nMin, int nMax, char sInstruct[]);
int getIntNoInput(int nIsRedo, char sInstruct[]);
char getDisplaySentiInput();
void getShortStrInput(char sInput[], char sInstruct[]);
void getTxtFileNameInput(char sInput[]);
void getLongStrInput(char sInput[], char sInstruct[]);
void CleanString(char nString[], int nIfCapitalized);
struct translatePair getTranslatePair();
void displayEntry(struct translatePair entry[], int nEntryCount, int nEntryNo);
void displayEntries(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries, int aEntryNoList[]);
void copyEntry(struct translatePair dest[], struct translatePair origin[], int nNoPairs);
int pairComparison(struct translatePair pair1, struct translatePair pair2);
void search(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries, struct translatePair target, 
    int nFirstEntry, int nFirstPair, int *nEntryNo, int *nPairNo, int nMatch);
void sortEntries(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries);
void sortEntryPairs(struct translatePair entry[], int entryCount);
void shiftEntries(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries, int nStartingIndex);
void shiftPairs(struct translatePair aEntry[], int nEntryCount, int nStartingIndex);
void clearEntry(struct translatePair aEntry[], int nEntryCount);
void readImportedData(FILE *fp, struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int *nNoEntries);
void tokenize(char text[], char words[][LONG_STRMAX + 1], int *wordCount);
int shortStrWordCount(char string[]);
void shiftWords(char aWords[][LONG_STRMAX + 1], int nWordCount, int nStartingIndex, int nShift);
int checkCapitalization(char word[]);
void executeTranslate(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries, char aWords[][LONG_STRMAX + 1],
    int isWordCountPresent[], int *wordCount, char langFrom[], char langTo[]);

// options.c
void AddEntry(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int *nNoEntries);
void AddTranslation(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int *nNoEntries);
void DisplayAllEntries(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries);
void SearchWord(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries);
void SearchTranslation(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries);
void DeleteEntry(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int *nNoEntries);
void DeleteTranslation(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int *nNoEntries);
void Export(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries);
void Import(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int *nNoEntries);
void TranslateTextInput(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries);
void TranslateTextFile(struct translatePair aEntries[][PAIRMAX], int aEntryCounts[], int nNoEntries);

// main.c
void ManageDataMenu();
void TranslateMenu();

#endif