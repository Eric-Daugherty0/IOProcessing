
#include <stdio.h>
#include <string.h>
// Include the header file
#include "Daugherty-IOProcessing.h"

int main(void)
{
    char words[MAX_WORDS][SIZE];
    char choice[20];
    int count = 0;
    int running = 1;

    // Load the words saved from the last time
    if (loadWords(words, &count))
    {
        printf("Saved words loaded successfully.\n");
    }
    else
    {
        printf("No saved words found. Starting a new list.\n");
    }
    // Main program loop
    while (running)
    {
        menu();

        if (!getInput(choice, sizeof(choice)))
        {
            running = 0;
            continue;
        }

        if (strlen(choice) != 1)
        {
            printf("Invalid choice. Please try again.\n");
            continue;
        }
        // Process the user's choice
        switch (choice[0])
        {
            case 'A':
            case 'a':
                enterWords(words, &count);
                break;

            case 'B':
            case 'b':
                makeTextFile(words, count);
                break;

            case 'C':
            case 'c':
                printWords(words, count);
                break;

            case 'D':
            case 'd':
                running = 0;
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    // Save the words before ending
    if (saveWords(words, count))
    {
        printf("Words saved to binary file.\n");
    }
    else
    {
        printf("Error saving words to binary file.\n");
    }

    printf("The program has ended.\n");

    return 0;
}

// Show the menu
void menu(void)
{
    printf("\n======= WORD MENU =======\n");
    printf("| A. Add more words     |\n");
    printf("| B. Create a text file |\n");
    printf("| C. Display all words  |\n");
    printf("| D. Exit               |\n");
    printf("=========================\n");
    printf("Enter your choice: ");
}

// Get input from the user
int getInput(char input[], int size)
{
    int ch;

    if (fgets(input, size, stdin) == NULL)
    {
        return 0;
    }

    if (strchr(input, '\n') == NULL)
    {
        // Remove extra characters if the input is too long
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            
        }
    }
    else
    {
        input[strcspn(input, "\n")] = '\0';
    }

    return 1;
}

// Let the user add words
void enterWords(char words[][SIZE], int *count)
{
    char word[SIZE];
    char answer[20];

    while (*count < MAX_WORDS)
    {
        printf("Enter a word: ");

        if (!getInput(word, sizeof(word)))
        {
            return;
        }

        if (word[0] == '\0')
        {
            printf("Please enter a word.\n");
            continue;
        }

        strcpy(words[*count], word);
        (*count)++;

        printf("Word added. Total words: %d\n", *count);

        if (*count == MAX_WORDS)
        {
            printf("The word list is full.\n");
            break;
        }

        printf("Add another word? (Y/N): ");

        if (!getInput(answer, sizeof(answer)))
        {
            return;
        }

        if (answer[0] != 'Y' && answer[0] != 'y')
        {
            break;
        }
    }
}

// Display all the words
void printWords(char words[][SIZE], int count)
{
    if (count == 0)
    {
        printf("There are no words to display.\n");
        return;
    }

    printf("\n===== ALL WORDS =====\n");

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s\n", i + 1, words[i]);
    }

    printf("Total words: %d\n", count);
}

// Write all the words to a text file
void makeTextFile(char words[][SIZE], int count)
{
    FILE *file = fopen("words.txt", "w");

    if (file == NULL)
    {
        printf("Could not create the text file.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        if (fprintf(file, "%s\n", words[i]) < 0)
        {
            printf("Error writing to the text file.\n");
            fclose(file);
            return;
        }
    }

    if (fclose(file) != 0)
    {
        printf("Error closing the text file.\n");
        return;
    }

    printf("Words saved to words.txt successfully.\n");
}

// Load the saved words from the binary file
int loadWords(char words[][SIZE], int *count)
{
    FILE *file = fopen("words.dat", "rb");
    int savedCount;

    *count = 0;

    if (file == NULL)
    {
        return 0;
    }

    if (fread(&savedCount, sizeof(int), 1, file) != 1 ||
        savedCount < 0 || savedCount > MAX_WORDS)
    {
        printf("The saved file could not be read.\n");
        fclose(file);
        return 0;
    }

    for (int i = 0; i < savedCount; i++)
    {
        if (fread(words[i], SIZE, 1, file) != 1)
        {
            printf("Error reading the saved words.\n");
            fclose(file);
            return 0;
        }

        // Make sure each word ends correctly
        words[i][SIZE - 1] = '\0';
    }

    fclose(file);
    *count = savedCount;

    return 1;
}

// Save the words to the binary file
int saveWords(char words[][SIZE], int count)
{
    FILE *file = fopen("words.dat", "wb");

    if (file == NULL)
    {
        return 0;
    }

    // Save how many words there are
    if (fwrite(&count, sizeof(int), 1, file) != 1)
    {
        fclose(file);
        return 0;
    }

    // Save each word
    for (int i = 0; i < count; i++)
    {
        if (fwrite(words[i], SIZE, 1, file) != 1)
        {
            fclose(file);
            return 0;
        }
    }

    if (fclose(file) != 0)
    {
        return 0;
    }

    return 1;
}