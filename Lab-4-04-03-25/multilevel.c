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

void sort(process* p, int n)
{
	process temp;
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(p[j].at<p[i].at)
			{
				temp = p[j];
				p[j] = p[i];
				p[i] = temp;
			}
		}
	}
}

void print(process* p, int n)
{

	double avgTAT=0, avgWT=0;
	printf("pid | at | bt | ct | tat | wt\n");
	for (int i = 0; i < n; i++) {
		p[i].tat = p[i].ct - p[i].at;
		p[i].wt = p[i].tat - p[i].bt;
		printf("%3d | %2d | %2d | %2d | %3d | %2d\n", p[i].pid, p[i].at,p[i].bt, p[i].ct, p[i].tat, p[i].wt);
		avgTAT += p[i].tat;
		avgWT += p[i].wt;
	}
	printf("ATAT:%f,AWT:%f\n",avgTAT/n,avgWT/n);
}


void fcfs(process* p, int n, int* ctp)
{
	int c = *ctp;
	for (int i = 0; i < n; i++)
	{
		if (c < p[i].at)
		{
			c = p[i].at;
		}
		c += p[i].bt;
		p[i].ct = c; 
	}

	*ctp = c; 
}
void main()
{
	int* ctp =  (int*) malloc(sizeof(int));
	*ctp = 0;
	int n1, n2;
	printf("Enter n1, n2:");
	scanf("%d%d",&n1, &n2);

	process sp[n1];
	process up[n2];
	printf("SYS\n");
	for(int i=0;i<n1;i++)
	{
		printf("Enter the data:");
		scanf("%d%d%d",&sp[i].pid,  &sp[i].at, &sp[i].bt);
		sp[i].pri=0;
	}

	printf("USR\n");
	for(int i=0;i<n2;i++)
	{
		printf("Enter the data:");
		scanf("%d%d%d",&up[i].pid,  &up[i].at, &up[i].bt);
		up[i].pri=1;
	}
	sort(sp,n1);
	sort(up, n2);

	fcfs(sp, n1, ctp);
	fcfs(up, n2, ctp);

	print(sp,n1);
	print(up,n2);
}
