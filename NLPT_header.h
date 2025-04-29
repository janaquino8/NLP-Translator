/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
                                                            Jan Leoric Badiola Aquino, DLSU ID# 12411221
*********************************************************************************************************/

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