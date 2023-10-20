// gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


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


int main(int argc, char *argv[]) {
    const char *PREFIX = (argc >= 2) ? argv[1] : "";
    const int PREFIXLENGTH = strlen(PREFIX);

    char line[100]; // A buffer to store each line

    // User's input includes only executable file and database
    // User doesn't provide address, so we display all start letters of adresses
    // So user can know where to start to search
    if (argc < 2) {
        char allowedLetters[100];
        while (fgets(line, sizeof(line), stdin) != NULL) {
            int length = strlen(line);
            if (length > 0) {
                addCharToStringIfNotPresent(allowedLetters, line[0]);
            }
        }
        alphabetizeString(allowedLetters);
        printf("Enable: %s\n", allowedLetters);
    }

    // User's input includes address or part of it
    if (argc >= 2) {
        char allowedLetters[100];
        char foundedCity[100];
        int countPrefix = 0;
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
    }
       
    return 0;

}
