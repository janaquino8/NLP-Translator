# NLP Translator
A simple translator made using C 

## About
This is a simple natural language processing (NLP) translator written using C. For the **manage data** section, this translator allows the user to add entries pertaining to the translation of a single word to other languages, delete entries, view entries, search entries based on word or translation, export the entries to a text file, and import a text file following the prescribed format (see ```Sample_Import.txt``` for details). For the **translate** section, the user may enter the text to be translated via input (maximum of 150 characters) or file (maximum of 150 characters per sentence). Translations will not include any punctuation marks that are not part of the words in the text (see ```Sample_TextFile.txt``` for an example on how translations via text file are exported).

This is done as a Machine Project (MP), part of the course requirements for CCPROG2 in DLSU.

## Installation Guide

### Cloning the repository
```sh
git clone https://github.com/janaquino8/NLP-Translator
```

### Compiling the project
```sh
gcc -Wall -std=c99 NLPT_main.c
```

### Running the project
```sh
./a
```

## Files
- ```NLPT_main.c``` - main file
- ```NLPT_options.c``` - file for the main menu, manage data, and translation options
- ```NLPT_helper.c``` - file for helper functions
- ```NLPT_header.h``` - header file
- ```Sample_Import.txt``` - sample text file for translation entries to be imported
- ```Sample_TextFile.txt``` - sample text file for an exported translated text

---

_The author of this project would like to thank his CCPROG2 professor, Ms. Nats, for guidance in this project._
_Made by Jan Leoric B. Aquino_
