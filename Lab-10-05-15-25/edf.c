#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define PCAST (struct Process *)
typedef struct Process Process;
struct Process {
	int PID;
	int bt;
	int ival;
	int rem_bt;
	int next_release;
	int deadline;
	int weight;
	bool rtr;
};
Process *get_processes(int *n) {
	printf("Enter the number of processes : ");
	scanf("%d", n);

	struct Process *arr = calloc(*n, sizeof(struct Process));
	printf("Enter the burst time and intervals : \n");
	
	for(int i = 0; i < *n; i++) {
		arr[i].PID = i + 1;
		printf("PID %d : ", i + 1);
		scanf("%d %d", &arr[i].bt, &arr[i].ival);
		arr[i].rtr = true;
	}

	return arr;
}


int
proccmp(const void *x, const void *y) {
	return (PCAST x)->ival - (PCAST y)->ival;
}

void earliest_deadline_scheduler(Process *arr, int n) {
	int max_time = arr[n-1].ival * 2;
	int time = 0;
	Process *curr = NULL, *prev = NULL;

	while(time < max_time) {

		for(int i = 0; i < n; i++) {
			if(arr[i].next_release == time) {
				arr[i].rtr = true;
				arr[i].rem_bt = arr[i].bt;
				arr[i].deadline = time + arr[i].ival;
				arr[i].next_release += arr[i].ival;
			}
		}

		curr = NULL;
		for(int i = 0; i < n; i++) {
			if(arr[i].rtr && arr[i].rem_bt > 0) {
				if(!curr || arr[i].deadline < curr->deadline) {
					curr = &arr[i];
				}
			}
		}

		if(prev != curr) {
			if (prev != NULL && prev->rem_bt > 0)
				printf("PID %d till %d\n", prev->PID, time);
			if (curr != NULL && curr->PID)
				printf("PID %d starts at %d\n", curr->PID, time);
			prev = curr;
		}

		if(!curr) {time++; continue;}

		curr->rem_bt--;
		if(curr->rem_bt == 0) {
			curr->rtr = false;
		}
		
		time++;
	}
	return;
}

int main() {
	int n;
	Process *arr = get_processes(&n);
	putchar('\n');
	earliest_deadline_scheduler(arr, n);

	free(arr);
	return 0;
}
