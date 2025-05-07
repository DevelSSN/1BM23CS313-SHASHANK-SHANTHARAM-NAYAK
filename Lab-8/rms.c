#include <stdio.h>

#define max_processes 10
#define SIMULATION_TIME 30  // Simulated time units (e.g., ms)

typedef struct {
    int id;
    int period;
    int exec_time;
    int next_release;
    int remaining_time;
} process;

int main() {
    process processes[max_processes];
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
    }

    // Sort processes by period (Rate Monotonic: smaller period = higher priority)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].period > processes[j].period) {
                process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Simulated time loop
    for (int time = 0; time < SIMULATION_TIME; time++) {
        for (int i = 0; i < n; i++) {
            // Release new job if period met
            if (time == processes[i].next_release) {
                processes[i].next_release += processes[i].period;
                processes[i].remaining_time = processes[i].exec_time;
                printf("Time %d: Process %d START\n", time, processes[i].id);
            }

            // Run highest-priority ready task
            if (processes[i].remaining_time > 0) {
                processes[i].remaining_time--;
                if (processes[i].remaining_time == 0) {
                    printf("Time %d: Process %d END\n", time, processes[i].id);
                }
                break;  // Preempt lower-priority processes
            }
        }
    }

    return 0;
}

