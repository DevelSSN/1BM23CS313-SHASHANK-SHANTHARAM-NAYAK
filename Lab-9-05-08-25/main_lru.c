#include "page_replacement.h"

int main() {
    int frames, pages, pageFaults = 0;
    int referenceString[100], frame[100]; // Frame contents
    int lastUsed[100];                    // Tracks last used time of each frame slot

    GET_INPUT(frames, pages, referenceString);

    // Initialize frames and usage history
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;
        lastUsed[i] = -1;
    }

    for (int time = 0; time < pages; time++) {
        int currentPage = referenceString[time];
        int found = 0;

        // Check if current page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == currentPage) {
                found = 1;
                lastUsed[j] = time;  // Update usage time
                break;
            }
        }

        // Page fault
        if (!found) {
            int index = -1;

            // Find an empty frame
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    index = j;
                    break;
                }
            }

            // No empty frame; replace LRU
            if (index == -1) {
                int minTime = time;
                for (int j = 0; j < frames; j++) {
                    if (lastUsed[j] < minTime) {
                        minTime = lastUsed[j];
                        index = j;
                    }
                }
            }

            frame[index] = currentPage;
            lastUsed[index] = time;
            pageFaults++;
        }

        DISPLAY_FRAMES(currentPage, frames, frame);
    }

    PRINT_PAGE_FAULTS(pageFaults);
    return 0;
}
