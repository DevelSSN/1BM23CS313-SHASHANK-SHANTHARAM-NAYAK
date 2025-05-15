#include <stdio.h>

#define MAX_PROCESSES 10
#define SIMULATION_TIME 30  // Total simulation time in time units

typedef struct {
    int id;
    int period;
    int exec_time;
    int next_release;
    int remaining_time;
    int active;  // Indicates if the process is ready to run
} process;

int main() {
    process processes[MAX_PROCESSES];
    int n;

    printf("Number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i;
        printf("Process %d period: ", i);
        scanf("%d", &processes[i].period);
        printf("Process %d execution time: ", i);
        scanf("%d", &processes[i].exec_time);
        processes[i].next_release = 0;
        processes[i].remaining_time = 0;
        processes[i].active = 0;
    }

    // Sort by period (Rate Monotonic Priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].period > processes[j].period) {
                process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    printf("\n--- Rate Monotonic Scheduling Simulation ---\n\n");

    // Simulation loop
    for (int time = 0; time < SIMULATION_TIME; time++) {

        // Check for new releases
        for (int i = 0; i < n; i++) {
            if (time == processes[i].next_release) {
                if (processes[i].remaining_time > 0) {
                    printf("Time %d: Process %d MISSED DEADLINE\n", time, processes[i].id);
                }

                processes[i].next_release += processes[i].period;
                processes[i].remaining_time = processes[i].exec_time;
                processes[i].active = 1;
            }
        }

        // Run highest-priority active process
        int ran = 0;
        for (int i = 0; i < n; i++) {
            if (processes[i].active && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time == processes[i].exec_time)
                    printf("Time %d: Process %d START\n", time, processes[i].id);

                processes[i].remaining_time--;

                if (processes[i].remaining_time == 0) {
                    processes[i].active = 0;
                    printf("Time %d: Process %d END\n", time, processes[i].id);
                }
                ran = 1;
                break;  // Preempt lower-priority processes
            }
        }

        if (!ran) {
            printf("Time %d: IDLE\n", time);
        }
    }

    return 0;
}
