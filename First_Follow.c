#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Maximum number of non-terminals and terminals
#define MAX_NON_TERMINALS 10
#define MAX_TERMINALS 10
#define MAX_PRODUCTIONS 10

// Structure to store a production rule
struct ProductionRule {
    char nonTerminal;
    char production[100];
};

// Structure to store the first and follow sets
struct Sets {
    char nonTerminal;
    char production[100]; // Added to store production
    char firstSet[MAX_TERMINALS];
    char followSet[MAX_TERMINALS];
};

// Function to calculate the first set for a non-terminal
void calculateFirstSet(struct Sets sets[], int numSets, char nonTerminal) {
    for (int i = 0; i < numSets; i++) {
        if (sets[i].nonTerminal == nonTerminal) {
            // Initialize the first set with the empty string
            strcpy(sets[i].firstSet, "$");

            // Iterate through production rules
            for (int j = 0; j < numSets; j++) 
            {
                if (sets[j].nonTerminal == nonTerminal) {
                    char firstChar = sets[j].production[0];

                    // If the first character is a terminal, add it to the first set
                    if (islower(firstChar)) 
                    {
                        strcat(sets[i].firstSet, &firstChar);

                    } else if (isupper(firstChar)) 
                    {
                        // If the first character is a non-terminal, recursively calculate its first set
                        calculateFirstSet(sets, numSets, firstChar);

                        // Add the first set of the non-terminal to the current first set
                        strcat(sets[i].firstSet, sets[j].firstSet);
                    }
                }
            }
        }
    }
}

// Function to calculate the follow set for a non-terminal
void calculateFollowSet(struct Sets sets[], int numSets, char nonTerminal) {
    for (int i = 0; i < numSets; i++) {
        if (sets[i].nonTerminal == nonTerminal) {
            // Initialize the follow set with the empty string
            strcpy(sets[i].followSet, "$");

            // Iterate through production rules
            for (int j = 0; j < numSets; j++) {
                char production[100];
                strcpy(production, sets[j].production);

                // Find the occurrence of the non-terminal in the production
                char *pos = strchr(production, nonTerminal);

                while (pos != NULL) {
                    char nextChar = pos[1];

                    // If the non-terminal is at the end of the production or
                    // followed by a terminal, add it to the follow set
                    if (nextChar == '\0' || islower(nextChar)) {
                        strcat(sets[i].followSet, sets[j].followSet);
                    }

                    // If the non-terminal is followed by a non-terminal, add
                    // the first set of that non-terminal to the follow set
                    if (isupper(nextChar)) {
                        for (int k = 0; k < numSets; k++) {
                            if (sets[k].nonTerminal == nextChar) {
                                strcat(sets[i].followSet, sets[k].firstSet);
                                if (strchr(sets[k].firstSet, '$') == NULL) {
                                    // If the first set of the following non-terminal
                                    // does not contain the empty string, stop here
                                    break;
                                }
                            }
                        }
                    }

                    // Move to the next occurrence of the non-terminal in the production
                    pos = strchr(pos + 1, nonTerminal);
                }
            }
        }
    }
}

int main() {
    int numProductions;
    struct Sets sets[MAX_NON_TERMINALS];

    printf("Enter the number of production rules: ");
    scanf("%d", &numProductions);

    // Input production rules and non-terminals
    for (int i = 0; i < numProductions; i++) {
        printf("Enter production rule %d (non-terminal followed by production): ", i + 1);
        scanf(" %c %s", &sets[i].nonTerminal, sets[i].production);
    }

    // Calculate first sets for all non-terminals
    for (int i = 0; i < numProductions; i++) {
        calculateFirstSet(sets, numProductions, sets[i].nonTerminal);
    }

    // Calculate follow sets for all non-terminals
    for (int i = 0; i < numProductions; i++) {
        calculateFollowSet(sets, numProductions, sets[i].nonTerminal);
    }

    // Print the calculated first and follow sets
    printf("\nNon-terminal\tProduction\tFirst Set\tFollow Set\n");
    for (int i = 0; i < numProductions; i++) {
        printf("%c\t\t%s\t\t%s\t\t%s\n", sets[i].nonTerminal, sets[i].production, sets[i].firstSet, sets[i].followSet);
    }

    return 0;
}
