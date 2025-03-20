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
};

void sjf(process* processes, int n) {
    int currentTime = 0;


	process temp;
	for(int i=0;i<n;i++)
	{
		for(int j=i;j<n;j++)
		{
			if((processes[j].at < processes[i].at)||(processes[j].at == processes[i].at && processes[j].bt < processes[i].bt))
			{
				temp = processes[i];
				processes[i] = processes[j];
				processes[j] = temp;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		currentTime += processes[i].bt;
		processes[i].ct = currentTime;
			
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

 
	double avgTAT=0, avgWT=0;
	printf("pid | at | bt | ct | tat | wt\n");
	for (int i = 0; i < n; i++) {
		printf("%3d | %2d | %2d | %2d | %3d | %2d\n", processes[i].pid, processes[i].at,processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
		avgTAT += processes[i].tat;
		avgWT += processes[i].wt;
	}
	printf("ATAT:%f,AWT:%f\n",avgTAT/n,avgWT/n);
}
