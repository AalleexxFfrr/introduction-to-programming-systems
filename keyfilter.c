// gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    const char *PREFIX = (argc >= 2) ? argv[1] : "";

    char line[100]; // A buffer to store each line
    char addresses[42][100];

    // User's input includes only executable file and database
    // User doesn't provide address, so we display all start letters of adresses
    // So user can know where to start to search
    if (argc < 2) {
        printf("Enable: ");
        while (fgets(line, sizeof(line), stdin) != NULL) {
            if (strlen(line) > 0) {
                printf("%c", line[0]);
            }
        }
        printf("\n");
    }

    // User's input includes address or part of it
    if (argc >= 2) {
        int i = 0;
        while (i < 42 && fgets(line, sizeof(line), stdin) != NULL) {
            if (strlen(line) > 0) {
                strcpy(addresses[i], line); // Copy the line to adresses array
                i++;
            }
        }

        int countPrefix = 0;
        for (int j = 0; j < i; j++) {

            if (strncasecmp(PREFIX,addresses[j], strlen(PREFIX)) == 0)
                countPrefix++;
        }

        if (countPrefix == 0)
            printf("Not found\n");

        if (countPrefix == 1) {
            for (int j = 0; j < i; j++) {

                if (strncasecmp(PREFIX,addresses[j], strlen(PREFIX)) == 0) 
                    printf("Found: %s\n", addresses[j]);
            }
        }

        if (countPrefix > 1) {
            printf("Enable: ");

            for (int j = 0; j < i; j++) {
               
                if (strncasecmp(PREFIX,addresses[j], strlen(PREFIX)) == 0) 
                    printf("%c", addresses[j][strlen(PREFIX)]);
            }

            printf("\n");
        }
    }
       
    return 0;

}
