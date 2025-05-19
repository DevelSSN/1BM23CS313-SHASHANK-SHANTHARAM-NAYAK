#include "page_replacement.h"  // Ensure this header provides: GET_INPUT, DISPLAY_FRAMES, PRINT_PAGE_FAULTS

int main() {
    int frames, pages, pageFaults = 0;
    int referenceString[100], frame[100];

    GET_INPUT(frames, pages, referenceString);

    // Initialize all frames to -1 (indicating empty)
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
    }

    // Traverse through each page in the reference string
    for (int i = 0; i < pages; i++) {
        int currentPage = referenceString[i];
        int found = 0;

        // Check if the page is already in one of the frames (page hit)
        for (int j = 0; j < frames; j++) {
            if (frame[j] == currentPage) {
                found = 1;
                break;
            }
        }

        // If not found (page fault)
        if (!found) {
            int replaceIndex = -1;

            // First, check for any empty frame
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            // If no empty frame, find the page used farthest in future
            if (replaceIndex == -1) {
                int farthest = -1;

                for (int j = 0; j < frames; j++) {
                    int nextUse = pages;  // Default: not used again

                    // Look ahead in the reference string
                    for (int k = i + 1; k < pages; k++) {
                        if (frame[j] == referenceString[k]) {
                            nextUse = k;
                            break;
                        }
                    }

                    // Select the frame with the farthest use
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }
            }

            // Replace the selected frame with the current page
            frame[replaceIndex] = currentPage;
            pageFaults++;
        }

        // Display current frame contents after this page reference
        DISPLAY_FRAMES(currentPage, frames, frame);
    }

    // Output total page faults
    PRINT_PAGE_FAULTS(pageFaults);
    return 0;
}
