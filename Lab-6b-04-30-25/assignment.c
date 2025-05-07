#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void naiveStringMatch(char* text, char* pattern) {
    int n = strlen(text);       // Length of the text
    int m = strlen(pattern);    // Length of the pattern

    // Traverse through every position in the text where the pattern could fit
    for (int i = 0; i <= n - m; i++) {
        int j;
        
        // Check if the pattern matches starting at text[i]
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                break;  // Mismatch found, break the inner loop
            }
        }

        // If the entire pattern matches, print the position
        if (j == m) {
            printf("Pattern found at index %d\n", i);
        }
    }
}

int main() {
    char *text, *pattern;
    int text_size, pattern_size;

    // Dynamically allocate memory for text and pattern
    printf("Enter the size of the text: ");
    scanf("%d", &text_size);
    
    // Allocate memory for the text
    text = (char*)malloc((text_size + 1) * sizeof(char));  // +1 for null terminator
    if (text == NULL) {
        printf("Memory allocation for text failed!\n");
        return 1;
    }

    // Take input for the text
    printf("Enter the text: ");
    getchar();  // Consume the newline left by previous scanf
    fgets(text, text_size + 1, stdin);  // Read text including spaces

    // Dynamically allocate memory for the pattern
    printf("Enter the size of the pattern: ");
    scanf("%d", &pattern_size);

    pattern = (char*)malloc((pattern_size + 1) * sizeof(char));  // +1 for null terminator
    if (pattern == NULL) {
        printf("Memory allocation for pattern failed!\n");
        free(text);
        return 1;
    }

    // Take input for the pattern
    printf("Enter the pattern: ");
    getchar();  // Consume the newline left by previous scanf
    fgets(pattern, pattern_size + 1, stdin);  // Read pattern including spaces

    // Call the Naive String Matching function
    naiveStringMatch(text, pattern);

    // Free the dynamically allocated memory
    free(text);
    free(pattern);

    return 0;
}
