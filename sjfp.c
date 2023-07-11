// C program to perform the pre-emptive shortest job first scheduling algorithm

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int rmgt;
    int ct;
    int tt;
    int wt;
    int rt;
};

void calculateCompletionTime(struct Process *p, int n)
{
    int currentTime = 0;
    int completedProcesses = 0;
    int shortestJob = -1;
    int shortestJobBurst = INT_MAX;

    while (completedProcesses < n)
    {
        shortestJob = -1;
        shortestJobBurst = INT_MAX;

        // Find the process with the shortest burst time among the arrived processes
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= currentTime && p[i].rmgt > 0 && p[i].rmgt < shortestJobBurst)
            {
                shortestJob = i;
                shortestJobBurst = p[i].rmgt;
            }
        }

        if (shortestJob == -1)
        {
            currentTime++;
        }
        else
        {

            if (p[shortestJob].rmgt == p[shortestJob].bt)
            {
                p[shortestJob].rt = currentTime - p[shortestJob].at;
            }

            p[shortestJob].rmgt--;
            currentTime++;

            if (p[shortestJob].rmgt == 0)
            {
                p[shortestJob].ct = currentTime;
                completedProcesses++;
            }
        }
    }
}

int main()
{
    int n, twt = 0, ttt = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *p = (struct Process *)malloc(n * sizeof(struct Process));

    for (int i = 0; i < n; i++)
    {
        printf("Enter details for process %d:\n", i + 1);
        p[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Burst Time: ");
        scanf("%d", &p[i].bt);
        p[i].rmgt = p[i].bt;
    }

    calculateCompletionTime(p, n);
    for (int i = 0; i < n; i++)
    {
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        twt += p[i].wt;
        ttt += p[i].tt;
    }

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt, p[i].rt);
    }
    printf("Average Waiting Time : %.2f\n", (float)twt / n);
    printf("Average Turnaround Time : %.2f\n", (float)ttt / n);
    free(p);
    return 0;
}
