/**
 * @file keyfilter.c
 * @brief Theme: Text Processing
 * @author Aleksandr Dmitriev (240259/xdmitr01)
 * @date October 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

/**
 * @brief Help function to create a string to store allowed letters on the keyboard.
 *        It also checks if the string doesn't already contain the letter to avoid letter repetitiveness.
 *
 * @param str The destination string.
 * @param newChar The character to be added to the string if not already present.
 */
void addCharToStringIfNotPresent(char *str, char newChar) {
    int isCharInString = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == newChar) {
            isCharInString = 1;
            break;
        }
    }

    if (!isCharInString) {
        int length = strlen(str);
        str[length] = newChar;
        str[length+1] = '\0';
    }
}

/**
 * @brief Sort a string in alphabetical order using the bubble sort algorithm.
 * 
 * This function is used to sort the characters within the provided string.
 *
 * @param str The string to be alphabetized.
 */
void alphabetizeString(char *str) {
    int length = strlen(str);

    for (int i = 0; i < length - 1; i++) {
        for (int j = 0; j < length - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

/**
 * @brief The main function.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 * @return An integer representing the exit status.
 */
int main(int argc, char *argv[]) {
    /* If user's input includes only executable file and database, we take address as empty string
       User doesn't provide address, so we display all possible start letters of adresses
       So user can know where to start to search 
    */
    const char *PREFIX = (argc >= 2) ? argv[1] : "";
    const int PREFIXLENGTH = strlen(PREFIX);

    char line[100]; // A buffer to store each line

    char allowedLetters[100];
    char foundedCity[100]; // A buffer to store copy of line, if countPrefix == 1 (only one address in database)
    int countPrefix = 0; // Count mathes between a PREFIX and a line

    // Stream processing
    while (fgets(line, sizeof(line), stdin) != NULL) {

        int length = strlen(line);

        if (length > 0) {
            if (strncasecmp(PREFIX,line, PREFIXLENGTH) == 0) {
                strcpy(foundedCity, line);
                addCharToStringIfNotPresent(allowedLetters, toupper(line[PREFIXLENGTH]));
                countPrefix++;
            }       
        }
    }

    alphabetizeString(allowedLetters);

    if (countPrefix == 0)
        printf("Not found\n");

    if (countPrefix == 1) {
        printf("Found: ");
        for (int i = 0; foundedCity[i] != '\0'; i++) {
            printf("%c", toupper(foundedCity[i]));
            }
        printf("\n");   
    }

    if (countPrefix >= 2)
        printf("Enable: %s\n", allowedLetters);

     return 0;
}
       