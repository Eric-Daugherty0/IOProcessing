#ifndef DAUGHERTY_IOPROCESSING_H
#define DAUGHERTY_IOPROCESSING_H

#define MAX_WORDS 1000
#define SIZE 100
// Function prototypes
void menu(void);
int getInput(char input[], int size);
void enterWords(char words[][SIZE], int *count);
void printWords(char words[][SIZE], int count);
void makeTextFile(char words[][SIZE], int count);
int loadWords(char words[][SIZE], int *count);
int saveWords(char words[][SIZE], int count);

#endif
