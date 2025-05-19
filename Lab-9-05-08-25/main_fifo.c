#include "page_replacement.h"

int main() {
	int frames, pages, pageFaults = 0, current = 0;
	int referenceString[100], frame[100]; // Max size to prevent runtime issues

	GET_INPUT(frames, pages, referenceString);

	// Initialize frames
	for (int i = 0; i < frames; i++) {
		frame[i] = -1;
	}

	for (int i = 0; i < pages; i++) {
		int found = 0;
		for (int j = 0; j < frames; j++) {
			if (frame[j] == referenceString[i]) {
				found = 1;
				break;
			}
		}
		if (!found) {
			frame[current] = referenceString[i];
			current = (current + 1) % frames;
			pageFaults++;
		}
		DISPLAY_FRAMES(referenceString[i], frames, frame);
	}

	PRINT_PAGE_FAULTS(pageFaults);
	return 0;
}
