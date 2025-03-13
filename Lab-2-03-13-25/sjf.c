#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct process process;
struct process{
	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
	int btl;
};

void sjf(process* processes, int n) {
    int currentTime = 0, completed = 0;
    bool isCompleted[n];  // Track completion of processes
    for (int i = 0; i < n; i++) {
        isCompleted[i] = false;
        processes[i].btl = processes[i].bt; // Initialize remaining bt
    }

    while (completed < n) {
        int minRemainingbt = 9999;
        int idx = -1;
        bool processFound = false;

        // Find the process with the minimum remaining burst time
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= currentTime && !isCompleted[i] && processes[i].btl < minRemainingbt) {
                minRemainingbt = processes[i].btl;
                idx = i;
                processFound = true;
            }
        }

        if (processFound) {
            // Execute the process for one time unit
            processes[idx].btl--;

            // If process is completed, record completion time
            if (processes[idx].btl == 0) {
                processes[idx].ct = currentTime + 1;
                isCompleted[idx] = true;
                completed++;
            }
        }

        currentTime++;
    }
	for (int i = 0; i < n; i++) {
        processes[i].tat = processes[i].ct - processes[i].at;  // TAT = CT - AT
        processes[i].wt = processes[i].tat - processes[i].bt;  // WT = Tat - BT
    }
}

void main()
{
	int n;
	printf("Enter n:");
	scanf("%d",&n);
	process* processes = (process*)malloc(n*sizeof(process));
	for(int i=0;i<n;i++)
	{
		printf("Enter data:");
		scanf("%d%d%d",&processes[i].pid,&processes[i].at,&processes[i].bt);
	}

	sjf(processes, n);

	printf("pid | at | bt | ct | tat | wt\n");
    for (int i = 0; i < n; i++) {
        printf("%3d | %2d | %2d | %2d | %3d | %2d\n", processes[i].pid, processes[i].at,
               processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
    }
}
