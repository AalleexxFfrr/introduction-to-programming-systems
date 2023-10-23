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

#define MAX_ADDRESS_LENGTH 100
#define INVALID_ARGUMENTS_MESSAGE "Invalid number of arguments. Please provide one, or don't provide any."
#define INPUT_ERROR_MESSAGE "Error reading input data." 
#define NOT_FOUND_MESSAGE "Not found"
#define FOUND_MESSAGE "Found: "
#define ENABLE_MESSAGE "Enable: "

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
    if (argc > 2) {
        fprintf(stderr, "%s\n", INVALID_ARGUMENTS_MESSAGE);
        return 1;
    }

    /* If user's input includes only executable file and database, we take address as empty string
       User doesn't provide address, so we display all possible start letters of adresses
       So user can know where to start to search 
    */
    const char *PREFIX = (argc >= 2) ? argv[1] : "";
    const int PREFIXLENGTH = strlen(PREFIX);

    char line[MAX_ADDRESS_LENGTH]; // A buffer to store each line
    char allowedLetters[MAX_ADDRESS_LENGTH];
    char foundedCity[MAX_ADDRESS_LENGTH]; // A buffer to store copy of line, if countPrefix == 1 (only one address in database)
    int countPrefix = 0; // Count mathes between a PREFIX and a line

    // Stream processing
    while (fgets(line, sizeof(line), stdin) != NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "%s\n", INPUT_ERROR_MESSAGE);
            return 1;
        }

        int length = strlen(line);
        if (length > 0) {
            if (strncasecmp(PREFIX,line, PREFIXLENGTH) == 0) {
                if (countPrefix < 2) {
                    strcpy(foundedCity, line);
                }
                addCharToStringIfNotPresent(allowedLetters, toupper(line[PREFIXLENGTH]));
                countPrefix++;
            }       
        }
    }

    alphabetizeString(allowedLetters);

    if (countPrefix == 0) {
        printf("%s\n", NOT_FOUND_MESSAGE);
    } else if (countPrefix == 1) {
        printf("%s", FOUND_MESSAGE);
        for (int i = 0; foundedCity[i] != '\0'; i++) {
            printf("%c", toupper(foundedCity[i]));
        }
        printf("\n");
    } else {
        printf("%s%s\n", ENABLE_MESSAGE, allowedLetters);
    }

    return 0;
}
