#ifndef PAGE_REPLACEMENT_H
#define PAGE_REPLACEMENT_H

#include <stdio.h>

// Macro for taking user input
#define GET_INPUT(frames, pages, refString) \
    printf("Enter number of frames: "); \
    scanf("%d", &frames); \
    printf("Enter number of pages: "); \
    scanf("%d", &pages); \
    printf("Enter reference string: "); \
    for (int i = 0; i < pages; i++) { \
        scanf("%d", &refString[i]); \
    }

// Macro for initializing frames
#define INIT_FRAMES(frames, frame, counter) \
    for (int i = 0; i < frames; i++) { \
        frame[i] = -1; \
        if (counter != NULL) counter[i] = 0; \
    }

// Macro for displaying frame contents
#define DISPLAY_FRAMES(page, frames, frame) \
    printf("%d: ", page); \
    for (int i = 0; i < frames; i++) { \
        printf("%d ", frame[i]); \
    } \
    printf("\n");

// Macro for printing total page faults
#define PRINT_PAGE_FAULTS(pageFaults) \
    printf("Total Page Faults: %d\n", pageFaults);

#endif
