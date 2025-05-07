#include <stdio.h>
#include <stdbool.h>

int main() {
    int P, R;

    printf("Enter number of processes: ");
    scanf("%d", &P);
    printf("Enter number of resource types: ");
    scanf("%d", &R);

    int Allocation[P][R], Max[P][R], Need[P][R], Available[R];
    bool Finish[P];
    int Work[R], SafeSequence[P];

    // Input Allocation matrix
    printf("Enter Allocation matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &Allocation[i][j]);

    // Input Max matrix
    printf("Enter Max matrix (%d x %d):\n", P, R);
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            scanf("%d", &Max[i][j]);

    // Input Available vector
    printf("Enter Available resources (%d):\n", R);
    for (int i = 0; i < R; i++)
        scanf("%d", &Available[i]);

    // Calculate Need matrix = Max - Allocation
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    // Initialize
    for (int i = 0; i < R; i++)
        Work[i] = Available[i];
    for (int i = 0; i < P; i++)
        Finish[i] = false;

    int count = 0;

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!Finish[i]) {
                bool canRun = true;
                for (int j = 0; j < R; j++) {
                    if (Need[i][j] > Work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (int j = 0; j < R; j++)
                        Work[j] += Allocation[i][j];
                    SafeSequence[count++] = i;
                    Finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is NOT in a safe state.\n");
            return 1;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", SafeSequence[i]);
    printf("\n");

    return 0;
}
