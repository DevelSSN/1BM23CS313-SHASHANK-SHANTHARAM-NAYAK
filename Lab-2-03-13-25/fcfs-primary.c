#include <stdio.h>
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

void sort(process* p, int n)
{
	int temp = 0;
	for(int i=0;i<n;i++)
	{
		for(int j=i;j<n;j++)
		{
			if(p[j].at<p[i].at)
			{
				temp=p[i].pid;
				p[i].pid=p[j].pid;
				p[j].pid=temp;

				temp=p[i].at;
				p[i].at=p[j].at;
				p[j].at=temp;

				temp=p[i].bt;
				p[i].bt=p[j].bt;
				p[j].bt=temp;
			}
			else if(p[j].at==p[i].at)
			{
				if(p[j].pid<p[i].pid)
				{
					temp=p[i].pid;
					p[i].pid=p[j].pid;
					p[j].pid=temp;

					temp=p[i].at;
					p[i].at=p[j].at;
					p[j].at=temp;

					temp=p[i].bt;
					p[i].bt=p[j].bt;
					p[j].bt=temp;
				}
			}
		}
	}
}

void main()
{
	int c=0;
	int n;
	printf("Enter no. of processes:");
	scanf("%d",&n);

	process p[n];

	for(int i=0;i<n;i++)
	{
		printf("Enter for process %d:",(i+1));
		scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);
	}

	sort(p,n);

	for(int i=0;i<n;i++)
	{
		if(c>=p[i].at)
			c+=p[i].bt;
		else
			c+=p[i].at+p[i].bt-p[i-1].ct;
		p[i].ct = c;
	}

	for(int i=0;i<n;i++)
	{
		p[i].tat = p[i].ct - p[i].at;
		p[i].wt = p[i].tat - p[i].bt;
	}

	printf("|\tPID\t|\tAT\t|\tBT\t|\tCT\t|\tTAT\t|\tWT\t|\n");
	printf("|\t---\t|\t---\t|\t---\t|\t---\t|\t---\t|\t---\t|\n");
	for(int i=0;i<n;i++)
		printf("|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\n",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].tat,p[i].wt);
}
