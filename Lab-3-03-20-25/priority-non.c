#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct process process;
struct process{
	int pid;
	int pri;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
};

void priority(process* processes, int n) {
    bool isCompleted[n];// Track completion of processes
    int completed = 0;
    int completedTime = 0;
    for (int i = 0; i < n; i++) {
        isCompleted[i] = false;
    }

    while (completed < n) {
        int minRemainingbt = 9999;
	int minPri = 9999;
        int idx = -1;
        bool processFound = false;

        // Find the process with the minimum remaining burst time
        for (int i = 0; i < n; i++) {
            if (processes[i].at <= completedTime && !isCompleted[i] && processes[i].pri < minPri) {
                minPri = processes[i].pri;
                idx = i;
                processFound = true;
            }
        }

        if (processFound) {
		completedTime += processes[idx].bt;
		isCompleted[idx] = true;
		processes[idx].ct = completedTime;
		completed++;
            }
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
		scanf("%d%d%d%d",&processes[i].pid,&processes[i].pri,&processes[i].at,&processes[i].bt);
	}
	priority(processes, n);
	double avgTAT=0, avgWT=0;
	printf("pid | at | bt | pri | ct | tat | wt\n");
	for (int i = 0; i < n; i++) {
		printf("%3d | %2d | %2d | %3d | %2d | %3d | %2d\n", processes[i].pid, processes[i].at,processes[i].bt, processes[i].pri, processes[i].ct, processes[i].tat, processes[i].wt);
		avgTAT += processes[i].tat;
		avgWT += processes[i].wt;
	}
	printf("ATAT:%f,AWT:%f\n",avgTAT/n,avgWT/n);


}
