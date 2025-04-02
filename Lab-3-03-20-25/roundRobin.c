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

int tq = 4;

void robin(process* processes, int n)
{
	int ct = 0, completed = 0;
	bool isCompleted[n];
	for(int i=0;i<n;i++){
		processes[i].btl = processes[i].bt;
		isCompleted[i] = false;
	}


	while(completed<n)
	{
		for(int i=0;i<n;i++)
		{
			if(!isCompleted[i] && processes[i].btl-tq>0)
			{
				processes[i].btl -= tq;
				ct += tq;
			}
			else if(!isCompleted[i])
			{
				ct += processes[i].btl;
				processes[i].btl = 0;
				processes[i].ct = ct;
				completed++;
				isCompleted[i]=true;
			}
		}
	}

	for(int i=0;i<n;i++)
	{
		processes[i].tat = processes[i].ct - processes[i].at;
		processes[i].wt = processes[i].tat - processes[i].bt;
	}
}

void main()
{
	int n;
	printf("Enter n:");
	scanf("%d",&n);

	process processes[n];
	for(int i=0;i<n;i++)
	{
		printf("Enter the data:");
		scanf("%d%d%d",&processes[i].pid, &processes[i].at, &processes[i].bt);
	}

	robin(processes, n);

	double avgTAT=0, avgWT=0;
	printf("pid | at | bt | ct | tat | wt\n");
	for (int i = 0; i < n; i++) {
		printf("%3d | %2d | %2d | %2d | %3d | %2d\n", processes[i].pid, processes[i].at,processes[i].bt, processes[i].ct, processes[i].tat, processes[i].wt);
		avgTAT += processes[i].tat;
		avgWT += processes[i].wt;
	}
	printf("ATAT:%f,AWT:%f\n",avgTAT/n,avgWT/n);
}

