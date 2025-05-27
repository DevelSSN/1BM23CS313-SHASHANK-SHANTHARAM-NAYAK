#include <stdio.h>

#define MAX 100

typedef struct {
    int pid, at, bt, ct, tat, wt, is_sys;
} Process;

void sort_by_arrival(Process p[], int n) {
    for(int i=0; i<n-1; i++)
        for(int j=i+1; j<n; j++)
            if(p[i].at > p[j].at) {
                Process tmp = p[i]; p[i] = p[j]; p[j] = tmp;
            }
}

void fcfs(Process p[], int n, int *time) {
    for(int i=0; i<n; i++) {
        if(*time < p[i].at) *time = p[i].at;
        p[i].ct = *time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
        *time = p[i].ct;
    }
}

void print(Process p[], int n, const char *label) {
    printf("\n%s Processes:\nPID\tAT\tBT\tCT\tTAT\tWT\n", label);
    for(int i=0; i<n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
}

int main() {
    Process sys[MAX], user[MAX];
    int n, sys_n = 0, user_n = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        Process p;
        p.pid = i+1;
        printf("\nP%d Arrival Time: ", p.pid); scanf("%d", &p.at);
        printf("P%d Burst Time: ", p.pid); scanf("%d", &p.bt);
        printf("P%d Type (1=System, 0=User): ",p.pid); scanf("%d", &p.is_sys);

        if(p.is_sys) sys[sys_n++] = p;
        else user[user_n++] = p;
    }

    sort_by_arrival(sys, sys_n);
    sort_by_arrival(user, user_n);

    int time = 0;
    fcfs(sys, sys_n, &time);
    fcfs(user, user_n, &time);

    print(sys, sys_n, "System");
    print(user, user_n, "User");

    return 0;
}
